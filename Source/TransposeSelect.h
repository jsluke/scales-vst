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
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TransposeSelect  : public Component,
                         public ComboBox::Listener,
                         public Button::Listener
{
public:
    //==============================================================================
    TransposeSelect ();
    ~TransposeSelect() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    FlexBox flexBox;
    OwnedArray<ComboBox> comboBoxes;
    enum comboIndex {NOTE};
    OwnedArray<ToggleButton> toggleButtons;
    enum toggleIndex {ONOFF_TOGGLE};

    NoteInfo noteInfo;
    ValueTree transposeTree;

    void comboBoxChanged(ComboBox *comboBoxThatHasChanged) override;
    void buttonClicked(Button *buttonThatWasClicked) override;
    void buttonStateChanged(Button *buttonThatHasChanged) override;
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TransposeSelect)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

