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

#include "ScalesFlexBox.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ScalesFlexBox::ScalesFlexBox ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]


    //[UserPreSize]
    for (int i = 0; i <= comboBoxIndex::MAX; i++)
    {
        flexBox.items.add(FlexItem(100, 30).withMargin(10));
        auto &flexItem = flexBox.items.getReference(flexBox.items.size() - 1);
        auto *comboBox = new ComboBox();
        comboBoxes.add(comboBox);
        flexItem.associatedComponent = comboBox;
        addAndMakeVisible(comboBox);
    }
    
    // TODO: how to make sure GUI and processor are initialized w/ same value? Prob define in Info
    
    comboBoxes[comboBoxIndex::SCALE] -> addItemList(scaleInfo.getStringArray(), 1);
    comboBoxes[comboBoxIndex::SCALE] -> setSelectedId(1);
    comboBoxes[comboBoxIndex::SCALE] -> addListener(this);
    scaleTree = ValueTree(ScaleInfo::scaleTree);
    scaleTree.addListener(this);
    
    comboBoxes[comboBoxIndex::NOTE] -> addItemList(noteInfo.getStringArray(), 1);
    comboBoxes[comboBoxIndex::NOTE] -> setSelectedId(1);
    comboBoxes[comboBoxIndex::NOTE] -> addListener(this);
    noteTree = ValueTree(NoteInfo::noteTree);
    noteTree.addListener(this);
    
    comboBoxes[comboBoxIndex::OPERATION] -> addItemList(operationInfo.getStringArray(), 1);
    comboBoxes[comboBoxIndex::OPERATION] -> setSelectedId(1);
    comboBoxes[comboBoxIndex::OPERATION] -> addListener(this);
    operationTree = ValueTree(OperationInfo::operationTree);
    operationTree.addListener(this);
    
    comboBoxes[comboBoxIndex::CONTROL_CHANNEL] -> addItemList(controlChannelInfo.getStringArray(), 1);
    comboBoxes[comboBoxIndex::CONTROL_CHANNEL] -> setSelectedId(1);
    comboBoxes[comboBoxIndex::CONTROL_CHANNEL] -> addListener(this);
    channelTree = ValueTree(ControlChannelInfo::channelTree);
    channelTree.addListener(this);

    flexBox.alignContent = FlexBox::AlignContent::flexStart;
    flexBox.flexDirection = FlexBox::Direction::row;
    flexBox.justifyContent = FlexBox::JustifyContent::flexStart;
    flexBox.alignItems = FlexBox::AlignItems::flexStart;
    flexBox.flexWrap = FlexBox::Wrap::wrap;
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

ScalesFlexBox::~ScalesFlexBox()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    
    //[/Destructor]
}

//==============================================================================
void ScalesFlexBox::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ScalesFlexBox::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    flexBox.performLayout(getLocalBounds());
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void ScalesFlexBox::comboBoxChanged(ComboBox *comboBoxThatHasChanged)
{
    // TODO: need to clean up getSelectedId() - 1 nonsense. How to make sure the IDs mean the same thing?
    
    if (comboBoxThatHasChanged == comboBoxes[comboBoxIndex::NOTE])
        noteTree.setProperty(NoteInfo::noteID, comboBoxThatHasChanged -> getSelectedId() - 1, nullptr);
    else if (comboBoxThatHasChanged == comboBoxes[comboBoxIndex::OPERATION])
        operationTree.setProperty(OperationInfo::operationID, comboBoxThatHasChanged -> getSelectedId() - 1, nullptr);
    else if (comboBoxThatHasChanged == comboBoxes[comboBoxIndex::SCALE])
        scaleTree.setProperty(ScaleInfo::scaleID, comboBoxThatHasChanged -> getSelectedId() - 1, nullptr);
    else if (comboBoxThatHasChanged == comboBoxes[comboBoxIndex::CONTROL_CHANNEL])
        scaleTree.setProperty(ControlChannelInfo::channelID, comboBoxThatHasChanged -> getSelectedId() - 1, nullptr);
}

void ScalesFlexBox::valueTreePropertyChanged(ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
//    if (treeWhosePropertyHasChanged == noteTree)
//        comboBoxes[comboBoxIndex::SCALE] -> setSelectedId(1);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ScalesFlexBox" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

