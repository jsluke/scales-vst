/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include <unordered_set>
#include <unordered_map>
//==============================================================================
/**
*/
class ScalesAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    ScalesAudioProcessor();
    ~ScalesAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ScalesAudioProcessor)
    
    //==============================================================================
    void generateNoteSets();
    bool noteIsInScale(int note);
    
    //==============================================================================
    static const int NUM_NOTES = 12;
    enum scaleType {MAJOR, MINOR, SCALE_TYPE_MAX = MINOR};
    const String notes[NUM_NOTES] = {
        "C",
        "C#",
        "D",
        "D#",
        "E",
        "F",
        "F#",
        "G",
        "G#",
        "A",
        "A#",
        "B"
    };
    bool noteSets[SCALE_TYPE_MAX+1][NUM_NOTES][NUM_NOTES] = {0};
    int currentScaleNote = 0;
    int currentScale = scaleType::MAJOR;
    int controlChannel = 1;
    int majorOctave = 3;
    int minorOctave = 4;
};
	
