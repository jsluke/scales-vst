/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "ScalesFlexBox.h"

//==============================================================================
/**
*/
class ScalesAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    ScalesAudioProcessorEditor (ScalesAudioProcessor&);
    ~ScalesAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ScalesAudioProcessor& processor;
    ScalesFlexBox flexBox;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ScalesAudioProcessorEditor)
};
