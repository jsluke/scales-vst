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
    else if (treeWhosePropertyHasChanged == controlChannelTree && property == MidiChannelInfo::controlChannelID)
    {
         controlChannel = controlChannelTree[MidiChannelInfo::controlChannelID];
    }
    else if (treeWhosePropertyHasChanged == scaleTree && property == ScaleInfo::scaleID)
    {
         currentScale = scaleTree[ScaleInfo::scaleID];
    }
    else if (treeWhosePropertyHasChanged == operationTree && property == OperationInfo::operationID)
    {
         operation = operationTree[OperationInfo::operationID];
    }
    else if (treeWhosePropertyHasChanged == transposeTree)
    {
        if (property == TransposeInfo::isEnabledID)
            transposeEnabled = transposeTree[TransposeInfo::isEnabledID];
        
        else if (property == TransposeInfo::transNoteID)
            transposeNote = transposeTree[TransposeInfo::transNoteID];
    }
    else if (treeWhosePropertyHasChanged == routeTree && property == MidiChannelInfo::routeChannelID)
    {
        routeChannel = routeTree[MidiChannelInfo::routeChannelID];
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
    controlChannelTree = ValueTree(MidiChannelInfo::getControlValueTree());
    controlChannelTree.addListener(this);
    operationTree = ValueTree(OperationInfo::getValueTree());
    operationTree.addListener(this);
    scaleTree = ValueTree(ScaleInfo::getValueTree());
    scaleTree.addListener(this);
    transposeTree = ValueTree(TransposeInfo::getValueTree());
    transposeTree.addListener(this);
    routeTree = ValueTree(MidiChannelInfo::getRouteValueTree());
    routeTree.addListener(this);
    
    currentScaleNote = noteTree[NoteInfo::noteID];
    currentScale = scaleTree[ScaleInfo::scaleID];
    controlChannel = controlChannelTree[MidiChannelInfo::controlChannelID];
    operation = operationTree[OperationInfo::operationID];
    
    for (int x=0; x<16; x++)
    {
        for (int y=0; y<128; y++)
        {
            noteOnMap[x][y] = NoteInfo::NO_NOTE;
        }
    }
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
    int noteToUse = transposeEnabled ? transposeNote : currentScaleNote;

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
            // prevent infinite note on scenario caused by control channel
            else if (msg.isNoteOff())
            {
                output.addEvent(msg, sampleNum);
            }
        }
        else if (!msg.isNoteOnOrOff())
        {
            output.addEvent(msg, sampleNum);
        } else if (scaleInfo.isNoteInScale(currentScale, noteToUse, msg.getNoteNumber())) {
            addOutputNote(output, sampleNum, msg, msg.getChannel(), msg.getNoteNumber());
        } else {
            // TODO: refactor
            if (operation == OperationInfo::DROP.order)
            {
                if (msg.isNoteOn())
                    continue;

                addOutputNote(output, sampleNum, msg, msg.getChannel(), msg.getNoteNumber());
            }
            else if (operation == OperationInfo::UP.order)
            {
                int toSet = scaleInfo.getNoteUp(currentScale, noteToUse, msg.getNoteNumber(), true);
                addOutputNote(output, sampleNum, msg, msg.getChannel(), toSet);
            }
            else if (operation == OperationInfo::DOWN.order)
            {
                int toSet = scaleInfo.getNoteDown(currentScale, noteToUse, msg.getNoteNumber(), true);
                addOutputNote(output, sampleNum, msg, msg.getChannel(), toSet);
            }
            else if (operation == OperationInfo::RAND.order)
            {
                int toSet;
                if (random.nextBool())
                    toSet = scaleInfo.getNoteDown(currentScale, noteToUse, msg.getNoteNumber(), true);
                else
                    toSet = scaleInfo.getNoteUp(currentScale, noteToUse, msg.getNoteNumber(), true);
                
                addOutputNote(output, sampleNum, msg, msg.getChannel(), toSet);
            }
            if (operation == OperationInfo::ROUTE.order)
            {
                if (routeChannel > 0)
                    addOutputNote(output, sampleNum, msg, routeChannel, msg.getNoteNumber());
            }
        }
    }

    midiMessages.swapWith(output);
}

void ScalesAudioProcessor::addOutputNote(MidiBuffer &output, int sampleNum, MidiMessage &msg, int channelToSet, int noteToSet)
{
    noteToSet = transpose(noteToSet);
    NoteOnData toSet = newToSet(msg, channelToSet, noteToSet);
    setNoteMap(msg, toSet);

    if (shouldSkipNoteOff(msg, toSet))
        return;

    msg.setChannel(toSet.channel);
    msg.setNoteNumber(toSet.note);
    output.addEvent(msg, sampleNum);
}

void ScalesAudioProcessor::setNoteMap(MidiMessage msg, NoteOnData toSet)
{
    const NoteOnData msgData = NoteOnData(msg);
    
    if (msg.isNoteOn())
        noteOnMap[msgData.channel][msgData.note] = toSet;
    else if (msg.isNoteOff())
        noteOnMap[msgData.channel][msgData.note] = NoteInfo::NO_NOTE;
}

bool ScalesAudioProcessor::shouldSkipNoteOff(MidiMessage msg, NoteOnData toSet)
{
    if (!msg.isNoteOff())
        return false;
    
    for (int x=0; x<16; x++)
    {
        for (int y=0; y<128; y++)
        {
            if (noteOnMap[x][y] == toSet)
                return true;
        }
    }
    
    return false;
}

// check if note OFF value needs to be transposed due to change of operation setting.
// prevents note staying on indefinitely
NoteOnData ScalesAudioProcessor::newToSet(MidiMessage msg, int channelToSet, int noteToSet)
{
    const NoteOnData msgData = NoteOnData(msg);
    const NoteOnData toSet = NoteOnData(channelToSet, noteToSet);
    
    if (msg.isNoteOff() && !(noteOnMap[msgData.channel][msgData.note] == toSet))
        return noteOnMap[msgData.channel][msgData.note];
    return toSet;
}

int ScalesAudioProcessor::transpose(int noteNumber)
{
    if (!transposeEnabled)
        return noteNumber;
    
    return noteNumber + abs(transposeNote - currentScaleNote);
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
