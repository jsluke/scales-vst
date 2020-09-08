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

#include "NoteInfo.h"
#include "ScaleInfo.h"
#include "MidiChannelInfo.h"
#include "OperationInfo.h"
#include "TransposeInfo.h"
//==============================================================================
/**
*/
class ScalesAudioProcessor  : public AudioProcessor, public ValueTree::Listener
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
    void valueTreePropertyChanged(ValueTree &treeWhosePropertyHasChanged, const Identifier &property) override;
    void addOutputNote(MidiBuffer &output, int sampleNum, MidiMessage &msg, int channelToSet, int noteToSet);
    void setNoteMap(MidiMessage msg, NoteOnData toSet);
    bool shouldSkipNoteOff(MidiMessage msg, NoteOnData toSet);
    NoteOnData newToSet(MidiMessage msg, int channelToSet, int noteToSet);
    int transpose(int noteNumber);
    
    //==============================================================================
    int currentScaleNote;
    int currentScale;
    int controlChannel;
    int operation;
    int routeChannel;
    int majorOctave = 3;
    int minorOctave = 4;
    
    int transposeNote;
    bool transposeEnabled;
    
    // [midi channels][note values]
     NoteOnData noteOnMap[16][128];
    //std::unordered_map<NoteOnData, NoteOnData> noteOnMap;
    
    ValueTree controlChannelTree;
    ValueTree noteTree;
    ValueTree scaleTree;
    ValueTree operationTree;
    ValueTree transposeTree;
    ValueTree routeTree;
    
    ScaleInfo scaleInfo;
    
    Random random;
};
	
