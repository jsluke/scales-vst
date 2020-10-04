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
#include "TransposeInfo.h"
#include "ColorDefs.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TransposeSelect  : public Component,
                         public AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    TransposeSelect ();
    ~TransposeSelect() override;

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

    enum comboIndex {NOTE};
    OwnedArray<ComboBox> comboBoxes;

    enum toggleIndex {ONOFF_TOGGLE};
    OwnedArray<DrawableButton> drawableButtons;

    enum labelIndex {TRANSPOSE_AMT};
    OwnedArray<Label> labels;

    std::unique_ptr<Drawable> svgOn;
    std::unique_ptr<Drawable> svgOff;

    std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> onoffAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> noteAttachment;

    NoteInfo noteInfo;
    StringArray noteText;
    ValueTree transposeTree;

    AudioProcessorValueTreeState* apvts;
    void parameterChanged(const String &parameterID, float newValue) override;
    String getTransposeAmountString(int transposeNote, int scaleNote);
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TransposeSelect)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

