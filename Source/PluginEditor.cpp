/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ScalesAudioProcessorEditor::ScalesAudioProcessorEditor (ScalesAudioProcessor& p, AudioProcessorValueTreeState& parameters)
    : AudioProcessorEditor (&p), processor (p), parameters (parameters)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    flexBox.connectState(parameters);
    addAndMakeVisible(flexBox);
    setSize (510, 440);
}

ScalesAudioProcessorEditor::~ScalesAudioProcessorEditor()
{
}

//==============================================================================
void ScalesAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void ScalesAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    flexBox.resized();
}
