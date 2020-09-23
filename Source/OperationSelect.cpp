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

#include "OperationSelect.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
OperationSelect::OperationSelect ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]


    //[UserPreSize]
    flexBox.items.add(FlexItem(100, 30).withMargin(10));
    auto &operationflexItem = flexBox.items.getReference(flexBox.items.size() - 1);
    ComboBox* operationBox = new ComboBox();
    comboBoxes.add(operationBox);
    operationflexItem.associatedComponent = operationBox;
    addAndMakeVisible(operationBox);

    comboBoxes[comboBoxIndex::OPERATION] -> addItemList(operationInfo.getStringArray(), 1);
    comboBoxes[comboBoxIndex::OPERATION] -> addListener(this);


    flexBox.items.add(FlexItem(100, 30).withMargin(10));
    auto &routeFlexItem = flexBox.items.getReference(flexBox.items.size() - 1);
    ComboBox* routeBox = new ComboBox();
    comboBoxes.add(routeBox);
    routeFlexItem.associatedComponent = routeBox;
    addChildComponent(routeBox);

    comboBoxes[comboBoxIndex::ROUTE] -> addItemList(midiChannelInfo.getStringArray(), 1);
    
    flexBox.items.add(FlexItem(250, 40).withMargin(5));
    auto &flexItemDesc = flexBox.items.getReference(flexBox.items.size() - 1);
    Label* desc = new Label();
    labels.add(desc);
    flexItemDesc.associatedComponent = desc;
    addAndMakeVisible(desc);

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

OperationSelect::~OperationSelect()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void OperationSelect::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff3e4c54));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void OperationSelect::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    flexBox.performLayout(getLocalBounds());
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void OperationSelect::comboBoxChanged(ComboBox *comboBoxThatHasChanged)
{
    // TODO: need to clean up getSelectedId() - 1 nonsense. How to make sure the IDs mean the same thing?

    if (comboBoxThatHasChanged == comboBoxes[comboBoxIndex::OPERATION])
    {
        if (comboBoxes[comboBoxIndex::OPERATION] -> getSelectedId() == OperationInfo::ROUTE.order + 1)
            updateVisibleComboBoxAsync(comboBoxes[comboBoxIndex::ROUTE], true);
        else
            updateVisibleComboBoxAsync(comboBoxes[comboBoxIndex::ROUTE], false);
        
        updateLabelTextAsync(labels[labelIndex::DESCRIPTION], operationInfo.getDescripton(comboBoxes[comboBoxIndex::OPERATION] -> getSelectedId() - 1));
    }
}

void OperationSelect::updateVisibleComboBoxAsync(ComboBox* box, bool isVisible)
{
    MessageManager::callAsync( [=]() {
        box -> setVisible(isVisible);
    });
}

void OperationSelect::updateLabelTextAsync(Label* label, const String &newText)
{
    MessageManager::callAsync( [=]() {
        label -> setText(newText, dontSendNotification);
    });
}

void OperationSelect::connectState(AudioProcessorValueTreeState& parameters)
{
    operationAttachment.reset(new AudioProcessorValueTreeState::ComboBoxAttachment(parameters, OperationInfo::operationParam, *comboBoxes[comboBoxIndex::OPERATION]));

    routeAttachment.reset(new AudioProcessorValueTreeState::ComboBoxAttachment(parameters, MidiChannelInfo::routeChannelParam, *comboBoxes[comboBoxIndex::ROUTE]));
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="OperationSelect" componentName=""
                 parentClasses="public Component, public ComboBox::Listener" constructorParams=""
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="500" initialHeight="100">
  <BACKGROUND backgroundColour="ff3e4c54"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

