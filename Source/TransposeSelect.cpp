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
    flexBox.items.add(FlexItem(100, 30).withMargin(10));
    auto &flexItemToggle = flexBox.items.getReference(flexBox.items.size() - 1);
    ToggleButton* toggle = new ToggleButton();
    components.add(toggle);
    flexItemToggle.associatedComponent = toggle;
    addAndMakeVisible(toggle);

    flexBox.items.add(FlexItem(100, 30).withMargin(10));
    auto &flexItemBox = flexBox.items.getReference(flexBox.items.size() - 1);
    ComboBox* box = new ComboBox();
    components.add(box);
    flexItemBox.associatedComponent = box;
    addAndMakeVisible(box);

    // TODO: ugly casting, refactor
    ((ToggleButton*)components[componentIndex::ONOFF_TOGGLE]) -> setToggleState(false, NotificationType::dontSendNotification);
    ((ToggleButton*)components[componentIndex::ONOFF_TOGGLE]) -> setButtonText("Enable Transpose");

    ((ComboBox*)components[componentIndex::NOTE]) -> addItemList(noteInfo.getStringArray(), 1);
    ((ComboBox*)components[componentIndex::NOTE]) -> setSelectedId(1);
    ((ComboBox*)components[componentIndex::NOTE]) -> addListener(this);

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
    //[/Destructor]
}

//==============================================================================
void TransposeSelect::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff3e4c54));

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
void TransposeSelect::comboBoxChanged(ComboBox *comboBoxThatHasChanged)
{

};

void TransposeSelect::buttonClicked(Button *buttonThatWasClicked)
{

};

void TransposeSelect::buttonStateChanged(Button *buttonThatHasChanged)
{

};
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TransposeSelect" componentName=""
                 parentClasses="public Component, public ComboBox::Listener, public Button::Listener"
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

