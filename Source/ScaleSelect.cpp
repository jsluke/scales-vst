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

#include "ScaleSelect.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ScaleSelect::ScaleSelect ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]


    //[UserPreSize]
    initComboBox();
    initComboBox();

    noteTree = ValueTree(NoteInfo::getValueTree());
    comboBoxes[comboBoxIndex::NOTE] -> addItemList(noteInfo.getStringArray(), 1);
    comboBoxes[comboBoxIndex::NOTE] -> setLookAndFeel(&comboBoxLookAndFeel);
    
    scaleTree = ValueTree(ScaleInfo::getValueTree());
    comboBoxes[comboBoxIndex::SCALE] -> addItemList(scaleInfo.getStringArray(), 1);
    comboBoxes[comboBoxIndex::SCALE] -> setLookAndFeel(&comboBoxLookAndFeel);

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

ScaleSelect::~ScaleSelect()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ScaleSelect::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (ColorDefs::selectBG);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ScaleSelect::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    flexBox.performLayout(getLocalBounds());
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void ScaleSelect::initComboBox()
{
    flexBox.items.add(FlexItem(100, 30).withMargin(10));
    auto &flexItem = flexBox.items.getReference(flexBox.items.size() - 1);
    ComboBox* box = new ComboBox();
    comboBoxes.add(box);
    flexItem.associatedComponent = box;
    addAndMakeVisible(box);
}

void ScaleSelect::connectState(AudioProcessorValueTreeState& parameters)
{
    noteAttachment.reset(new AudioProcessorValueTreeState::ComboBoxAttachment(parameters, NoteInfo::noteParam, *comboBoxes[comboBoxIndex::NOTE]));

    scaleAttachment.reset(new AudioProcessorValueTreeState::ComboBoxAttachment(parameters, ScaleInfo::scaleParam, *comboBoxes[comboBoxIndex::SCALE]));
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ScaleSelect" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="500" initialHeight="100">
  <BACKGROUND backgroundColour="ff3e4c54"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

