/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ScalesAudioProcessor::ScalesAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

ScalesAudioProcessor::~ScalesAudioProcessor()
{
}

//==============================================================================
void ScalesAudioProcessor::valueTreePropertyChanged(ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
    if (treeWhosePropertyHasChanged == noteTree && property == NoteInfo::noteID)
    {
            currentScaleNote = noteTree[NoteInfo::noteID];
    }
    else if (treeWhosePropertyHasChanged == channelTree && property == ControlChannelInfo::channelID)
    {
             controlChannel = channelTree[ControlChannelInfo::channelID];
    }
    else if (treeWhosePropertyHasChanged == scaleTree && property == ScaleInfo::scaleID)
    {
             currentScale = scaleTree[ScaleInfo::scaleID];
    }
    else if (treeWhosePropertyHasChanged == operationTree && property == OperationInfo::operationID)
    {
             operation = operationTree[OperationInfo::operationID];
    }
    
}

//==============================================================================
const String ScalesAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ScalesAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ScalesAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ScalesAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ScalesAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ScalesAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ScalesAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ScalesAudioProcessor::setCurrentProgram (int index)
{
}

const String ScalesAudioProcessor::getProgramName (int index)
{
    return {};
}

void ScalesAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void ScalesAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    noteTree = ValueTree(NoteInfo::getValueTree());
    noteTree.addListener(this);
    channelTree = ValueTree(ControlChannelInfo::getValueTree());
    channelTree.addListener(this);
    operationTree = ValueTree(OperationInfo::getValueTree());
    operationTree.addListener(this);
    scaleTree = ValueTree(ScaleInfo::getValueTree());
    scaleTree.addListener(this);
    
    currentScaleNote = noteTree[NoteInfo::noteID];
    currentScale = scaleTree[ScaleInfo::scaleID];
    controlChannel = channelTree[ControlChannelInfo::channelID];
    operation = operationTree[OperationInfo::operationID];
    
    for(int i=0; i<NoteInfo::NUM_NOTES; i++)
        noteOnMap[i] = -1;
    
}

void ScalesAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ScalesAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void ScalesAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
//    for (int channel = 0; channel < totalNumInputChannels; ++channel)
//    {
//        auto* channelData = buffer.getWritePointer (channel);
//
//        // ..do something to the data...
//    }
    
    MidiMessage msg;
    int sampleNum;
    MidiBuffer output;

    for (MidiBuffer::Iterator it(midiMessages); it.getNextEvent(msg, sampleNum);)
    {
        if (msg.getChannel() == controlChannel)
        {
            if (msg.isNoteOn())
            {
                // TODO: edit value trees for scale and note
                switch (NoteInfo::getOctave(msg.getNoteNumber()))
                {
                    case 3:
                        currentScale = ScaleInfo::MAJOR.order;
                        scaleTree.setProperty(ScaleInfo::scaleID, ScaleInfo::MAJOR.order, nullptr);
                        currentScaleNote = NoteInfo::getNoteInOctave(msg.getNoteNumber());
                        noteTree.setProperty(NoteInfo::noteID, currentScaleNote, nullptr);
                        break;

                    case 4:
                        currentScale = ScaleInfo::MINOR.order;
                        scaleTree.setProperty(ScaleInfo::scaleID, ScaleInfo::MINOR.order, nullptr);
                        currentScaleNote = NoteInfo::getNoteInOctave(msg.getNoteNumber());
                        noteTree.setProperty(NoteInfo::noteID, currentScaleNote, nullptr);
                        break;

                    default:
                        break;
                }
            }
        }
        else if (!msg.isNoteOnOrOff())
        {
            output.addEvent(msg, sampleNum);
        } else if (scaleInfo.isNoteInScale(currentScale, currentScaleNote, msg.getNoteNumber())) {
            setNoteMap(msg, msg.getNoteNumber());
            
            if (shouldSkipNoteOff(msg, msg.getNoteNumber()))
                continue;
            
            output.addEvent(msg, sampleNum);
        } else {
            // TODO: refactor
            if (operation == OperationInfo::DROP.order)
            {
                if (msg.isNoteOn())
                    continue;

                int toSet = msg.getNoteNumber();
                toSet = newToSet(msg, toSet);
                setNoteMap(msg, toSet);
                
                if (shouldSkipNoteOff(msg, toSet))
                    continue;
                
                msg.setNoteNumber(toSet);
                output.addEvent(msg, sampleNum);
            }
            else if (operation == OperationInfo::UP.order)
            {
                int toSet = scaleInfo.getNoteUp(currentScale, currentScaleNote, msg.getNoteNumber(), true);
                toSet = newToSet(msg, toSet);
                setNoteMap(msg, toSet);
                
                if (shouldSkipNoteOff(msg, toSet))
                    continue;
                
                msg.setNoteNumber(toSet);
                output.addEvent(msg, sampleNum);
            }
            else if (operation == OperationInfo::DOWN.order)
            {
                int toSet = scaleInfo.getNoteDown(currentScale, currentScaleNote, msg.getNoteNumber(), true);
                toSet = newToSet(msg, toSet);
                setNoteMap(msg, toSet);
                
                if (shouldSkipNoteOff(msg, toSet))
                    continue;
                
                msg.setNoteNumber(toSet);
                output.addEvent(msg, sampleNum);
            }
        }
    }

    midiMessages.swapWith(output);
}

void ScalesAudioProcessor::setNoteMap(MidiMessage msg, int toSet)
{
    if (msg.isNoteOn())
        noteOnMap[msg.getNoteNumber()] = toSet;
    else if (msg.isNoteOff())
        noteOnMap[msg.getNoteNumber()] = -1;
}

bool ScalesAudioProcessor::shouldSkipNoteOff(MidiMessage msg, int toSet)
{
    if (!msg.isNoteOff())
        return false;
    
    for (int i=0; i<128; i++)
    {
        if (noteOnMap[i] == toSet)
            return true;
    }
    
    return false;
}

// check if note OFF value needs to be transposed due to change of operation setting.
// prevents note staying on indefinitely
int ScalesAudioProcessor::newToSet(MidiMessage msg, int toSet)
{
    if (msg.isNoteOff() && noteOnMap[msg.getNoteNumber()] != toSet)
        return noteOnMap[msg.getNoteNumber()];
    return toSet;
}

//==============================================================================
bool ScalesAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ScalesAudioProcessor::createEditor()
{
    return new ScalesAudioProcessorEditor (*this);
}

//==============================================================================
void ScalesAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ScalesAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ScalesAudioProcessor();
}
