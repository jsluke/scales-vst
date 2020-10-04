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
#include "NoteInfo.h"
#include "ScaleInfo.h"
#include "ColorDefs.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ScaleSelect  : public Component
{
public:
    //==============================================================================
    ScaleSelect ();
    ~ScaleSelect() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void connectState(AudioProcessorValueTreeState& parameters);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    ComboLAF comboBoxLookAndFeel;
    
    FlexBox flexBox;
    OwnedArray<ComboBox> comboBoxes;

    enum comboBoxIndex {NOTE, SCALE};

    NoteInfo noteInfo;
    ScaleInfo scaleInfo;

    ValueTree noteTree;
    ValueTree scaleTree;

    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> noteAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> scaleAttachment;

    void initComboBox();
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ScaleSelect)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

