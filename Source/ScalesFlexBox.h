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

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
#include "MidiChannelInfo.h"
#include "NoteInfo.h"
#include "ScaleInfo.h"
#include "OperationInfo.h"
#include "ScaleSelect.h"
#include "OperationSelect.h"
#include "ControlSelect.h"
#include "TransposeSelect.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ScalesFlexBox  : public Component
{
public:
    //==============================================================================
    ScalesFlexBox ();
    ~ScalesFlexBox() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void connectState(AudioProcessorValueTreeState& parameters);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    FlexBox flexBox;
    TransposeSelect* transposeSelect;
    ScaleSelect* scaleSelect;
    OperationSelect* operationSelect;
    ControlSelect* controlSelect;
    enum panelIndex {SCALE, TRANSPOSE, OPERATION, CONTROL};
    OwnedArray<Component> panels;
    OwnedArray<Label> labels;
    
    
    std::unique_ptr<Drawable> svgWhiskFront;
    std::unique_ptr<Drawable> svgWhiskBack;
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ScalesFlexBox)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

