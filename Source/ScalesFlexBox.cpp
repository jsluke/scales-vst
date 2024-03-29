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
    auto topPanelMargin = FlexItem::Margin(30, 5, 5, 5);
    auto panelMargin = FlexItem::Margin(40, 5, 5, 5);
    
    auto scaleXml = XmlDocument::parse(BinaryData::whisk_svg);
    svgWhiskFront = Drawable::createFromSVG(*scaleXml);
    svgWhiskFront -> replaceColour(Colours::black, Colour(0xfff7e1d7));

    svgWhiskBack = Drawable::createFromSVG(*scaleXml);
    svgWhiskBack -> replaceColour(Colours::black, Colour(0xffedafb8));
    
    flexBox.items.add(FlexItem(500, 50).withMargin(topPanelMargin));
    auto &flexItemScale = flexBox.items.getReference(flexBox.items.size() - 1);
    scaleSelect = new ScaleSelect();
    panels.add(scaleSelect);
    flexItemScale.associatedComponent = scaleSelect;
    addAndMakeVisible(scaleSelect);
    
    Label* lScale = new Label();
    lScale -> setText(TRANS("Output Scale"), NotificationType::dontSendNotification);
    lScale -> setColour(Label::ColourIds::backgroundColourId, ColorDefs::selectBG);
    lScale -> attachToComponent(scaleSelect, false);
    labels.add(lScale);

    flexBox.items.add(FlexItem(500, 50).withMargin(panelMargin));
    auto &flexItemTranspose = flexBox.items.getReference(flexBox.items.size() - 1);
    transposeSelect = new TransposeSelect();
    panels.add(transposeSelect);
    flexItemTranspose.associatedComponent = transposeSelect;
    addAndMakeVisible(transposeSelect);
    
    Label* lTrans = new Label();
    lTrans -> setText(TRANS("Transpose Notes"), NotificationType::dontSendNotification);
    lTrans -> setColour(Label::ColourIds::backgroundColourId, ColorDefs::selectBG);
    lTrans -> attachToComponent(transposeSelect, false);
    labels.add(lTrans);

    flexBox.items.add(FlexItem(500, 50).withMargin(panelMargin));
    auto &flexItemOp = flexBox.items.getReference(flexBox.items.size() - 1);
    operationSelect = new OperationSelect();
    panels.add(operationSelect);
    flexItemOp.associatedComponent = operationSelect;
    addAndMakeVisible(operationSelect);
    
    Label* lOp = new Label();
    lOp -> setText(TRANS("Operation for Notes Out of Scale"), NotificationType::dontSendNotification);
    lOp -> setColour(Label::ColourIds::backgroundColourId, ColorDefs::selectBG);
    lOp -> attachToComponent(operationSelect, false);
    labels.add(lOp);

    flexBox.items.add(FlexItem(500, 50).withMargin(panelMargin));
    auto &flexItemControl = flexBox.items.getReference(flexBox.items.size() - 1);
    controlSelect = new ControlSelect();
    panels.add(controlSelect);
    flexItemControl.associatedComponent = controlSelect;
    addAndMakeVisible(controlSelect);
    
    Label* lCon = new Label();
    lCon -> setText(TRANS("MIDI Channel to Control Output Scale Settings"), NotificationType::dontSendNotification);
    lCon -> setColour(Label::ColourIds::backgroundColourId, ColorDefs::selectBG);
    lCon -> attachToComponent(controlSelect, false);
    labels.add(lCon);

    flexBox.alignContent = FlexBox::AlignContent::flexStart;
    flexBox.flexDirection = FlexBox::Direction::column;
    flexBox.justifyContent = FlexBox::JustifyContent::flexStart;
    flexBox.alignItems = FlexBox::AlignItems::flexStart;
    flexBox.flexWrap = FlexBox::Wrap::wrap;
    //[/UserPreSize]

    setSize (510, 370);


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

    g.fillAll (ColorDefs::windowBG);

    //[UserPaint] Add your own custom painting code here..
    auto bounds = this -> getBounds().withTrimmedTop(18).withTrimmedBottom(5);
    svgWhiskBack -> drawWithin(g, bounds.withTrimmedLeft(5).toFloat(), RectanglePlacement::xMid + RectanglePlacement::yTop, 1.0f);
    svgWhiskFront -> drawWithin(g, bounds.withTrimmedRight(5).toFloat(), RectanglePlacement::xMid + RectanglePlacement::yTop, 1.0f);
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
void ScalesFlexBox::connectState(AudioProcessorValueTreeState& parameters)
{
    scaleSelect -> connectState(parameters);
    operationSelect -> connectState(parameters);
    controlSelect -> connectState(parameters);
    transposeSelect -> connectState(parameters);
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
                 fixedSize="0" initialWidth="510" initialHeight="440">
  <BACKGROUND backgroundColour="ff323e44"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

