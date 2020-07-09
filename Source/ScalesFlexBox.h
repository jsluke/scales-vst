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
#include "ControlChannelInfo.h"
#include "NoteInfo.h"
#include "ScaleInfo.h"
#include "OperationInfo.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ScalesFlexBox : public Component, public ComboBox::Listener, public ValueTree::Listener
{
public:
    //==============================================================================
    ScalesFlexBox ();
    ~ScalesFlexBox() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    FlexBox flexBox;
    OwnedArray<ComboBox> comboBoxes;
    
    enum comboBoxIndex {SCALE, NOTE, OPERATION, CONTROL_CHANNEL, MAX = CONTROL_CHANNEL};
    ControlChannelInfo controlChannelInfo;
    NoteInfo noteInfo;
    ScaleInfo scaleInfo;
    OperationInfo operationInfo;
    
    ValueTree controlChannelTree;
    ValueTree noteTree;
    ValueTree scaleTree;
    ValueTree operationTree;
    
    void comboBoxChanged(ComboBox *comboBoxThatHasChanged) override;
    void valueTreePropertyChanged(ValueTree &treeWhosePropertyHasChanged, const Identifier &property) override;
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ScalesFlexBox)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

