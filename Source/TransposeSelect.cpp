/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.7

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "TransposeSelect.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
TransposeSelect::TransposeSelect ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]


    //[UserPreSize]
    auto onXml = XmlDocument::parse(BinaryData::on_v2_svg);
    svgOn = Drawable::createFromSVG(*onXml);

    auto offXml = XmlDocument::parse(BinaryData::off_v2_svg);
    svgOff = Drawable::createFromSVG(*offXml);

    noteText = noteInfo.getStringArray();

    flexBox.items.add(FlexItem(100, 30).withMargin(10).withMaxHeight(30));
    auto &flexItemToggle = flexBox.items.getReference(flexBox.items.size() - 1);
    DrawableButton* toggle = new DrawableButton("button name", DrawableButton::ButtonStyle::ImageFitted);
    drawableButtons.add(toggle);
    flexItemToggle.associatedComponent = toggle;
    addAndMakeVisible(toggle);

    flexBox.items.add(FlexItem(100, 30).withMargin(10).withMaxHeight(30));
    auto &flexItemBox = flexBox.items.getReference(flexBox.items.size() - 1);
    ComboBox* box = new ComboBox();
    comboBoxes.add(box);
    flexItemBox.associatedComponent = box;
    addAndMakeVisible(box);

    flexBox.items.add(FlexItem(200, 30).withMargin(10));
    auto &flexItemAmt = flexBox.items.getReference(flexBox.items.size() - 1);
    Label* amt = new Label();
    labels.add(amt);
    flexItemAmt.associatedComponent = amt;
    addAndMakeVisible(amt);

    drawableButtons[toggleIndex::ONOFF_TOGGLE] -> setImages(svgOff.get(), nullptr, nullptr, nullptr, svgOn.get());
    drawableButtons[toggleIndex::ONOFF_TOGGLE] -> setColour(DrawableButton::ColourIds::backgroundColourId, Colours::transparentBlack);
    drawableButtons[toggleIndex::ONOFF_TOGGLE] -> setColour(DrawableButton::ColourIds::backgroundOnColourId, Colours::transparentBlack);
    drawableButtons[toggleIndex::ONOFF_TOGGLE] -> setClickingTogglesState(true);
    comboBoxes[comboIndex::NOTE] -> addItemList(noteInfo.getStringArray(), 1);
    comboBoxes[comboIndex::NOTE] -> setLookAndFeel(&comboBoxLookAndFeel);
    labels[labelIndex::TRANSPOSE_AMT] -> setText("", NotificationType::dontSendNotification);
    labels[labelIndex::TRANSPOSE_AMT] -> setFont(Font().boldened());

    flexBox.alignContent = FlexBox::AlignContent::flexStart;
    flexBox.flexDirection = FlexBox::Direction::row;
    flexBox.justifyContent = FlexBox::JustifyContent::flexStart;
    flexBox.alignItems = FlexBox::AlignItems::flexStart;
    flexBox.flexWrap = FlexBox::Wrap::wrap;
    //[/UserPreSize]

    setSize (500, 100);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

TransposeSelect::~TransposeSelect()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    apvts -> removeParameterListener(TransposeInfo::isEnabledParam, this);
    apvts -> removeParameterListener(TransposeInfo::noteParam, this);
    apvts -> removeParameterListener(NoteInfo::noteParam, this);
    //[/Destructor]
}

//==============================================================================
void TransposeSelect::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (ColorDefs::selectBG);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TransposeSelect::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    flexBox.performLayout(getLocalBounds());
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void TransposeSelect::connectState(AudioProcessorValueTreeState& parameters)
{
    onoffAttachment.reset(new AudioProcessorValueTreeState::ButtonAttachment(parameters, TransposeInfo::isEnabledParam, *drawableButtons[toggleIndex::ONOFF_TOGGLE]));
    noteAttachment.reset(new AudioProcessorValueTreeState::ComboBoxAttachment(parameters, TransposeInfo::noteParam, *comboBoxes[comboIndex::NOTE]));

    apvts = &parameters;
    apvts -> addParameterListener(TransposeInfo::isEnabledParam, this);
    apvts -> addParameterListener(TransposeInfo::noteParam, this);
    apvts -> addParameterListener(NoteInfo::noteParam, this);

    AudioParameterChoice* transposeNoteChoice = (AudioParameterChoice*)(apvts->getParameter(TransposeInfo::noteParam));
    AudioParameterChoice* scaleNoteChoice = (AudioParameterChoice*)(apvts->getParameter(NoteInfo::noteParam));
    int transposeNote = transposeNoteChoice->getIndex();
    int scaleNote = scaleNoteChoice->getIndex();
    labels[labelIndex::TRANSPOSE_AMT] -> setText(getTransposeAmountString(transposeNote, scaleNote), dontSendNotification);

    AudioParameterBool* transposeEnabledChoice = (AudioParameterBool*)(apvts->getParameter(TransposeInfo::isEnabledParam));
    if (transposeEnabledChoice->get()) {
        labels[labelIndex::TRANSPOSE_AMT] -> setVisible(true);
    }
    else {
        labels[labelIndex::TRANSPOSE_AMT] -> setVisible(false);
    }
}

void TransposeSelect::parameterChanged(const String &parameterID, float newValue)
{
    // TODO - make sure string lengths are disparate to make str compares faster?
    if (parameterID == TransposeInfo::isEnabledParam)
    {
        if (newValue == 0.0f) {
            labels[labelIndex::TRANSPOSE_AMT] -> setVisible(false);
        }
        else {
            labels[labelIndex::TRANSPOSE_AMT] -> setVisible(true);
        }
    }
    else if (parameterID == TransposeInfo::noteParam)
    {
        AudioParameterChoice* scaleNoteChoice = (AudioParameterChoice*)(apvts->getParameter(NoteInfo::noteParam));

        int transposeNote = roundToInt(newValue);
        int scaleNote = scaleNoteChoice->getIndex();
        labels[labelIndex::TRANSPOSE_AMT] -> setText(getTransposeAmountString(transposeNote, scaleNote), dontSendNotification);
    }
    else if (parameterID == NoteInfo::noteParam)
    {
        AudioParameterChoice* transposeNoteChoice = (AudioParameterChoice*)(apvts->getParameter(TransposeInfo::noteParam));

        int transposeNote = transposeNoteChoice -> getIndex();
        int scaleNote = roundToInt(newValue);
        labels[labelIndex::TRANSPOSE_AMT] -> setText(getTransposeAmountString(transposeNote, scaleNote), dontSendNotification);
    }
}

String TransposeSelect::getTransposeAmountString(int transposeNote, int scaleNote)
{
    int transposeAmount = TransposeInfo::getTransposeAmount(transposeNote, scaleNote);

    String result = noteText[transposeNote];
    result += String(CharPointer_UTF8 (" \u2192 ")); // right arrow unicode
    result += noteText[scaleNote];
    result += transposeAmount < 0 ? " (" : " (+";
    result += transposeAmount;
    result += ")";
    return result;
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TransposeSelect" componentName=""
                 parentClasses="public Component, public AudioProcessorValueTreeState::Listener"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="500"
                 initialHeight="100">
  <BACKGROUND backgroundColour="ff3e4c54"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

