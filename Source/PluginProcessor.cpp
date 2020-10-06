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
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
     parameters (*this, nullptr, Identifier("ScalesParams"),
                   {
                        std::make_unique<AudioParameterChoice> (NoteInfo::noteParam,
                                                                NoteInfo::noteParamText,
                                                                NoteInfo::getStringArray(),
                                                                NoteInfo::noteParamDefault),
                        std::make_unique<AudioParameterChoice> (ScaleInfo::scaleParam,
                                                                ScaleInfo::scaleParamText,
                                                                ScaleInfo::getStringArray(),
                                                                ScaleInfo::scaleParamDefault),
                        std::make_unique<AudioParameterBool> (TransposeInfo::isEnabledParam,
                                                              TransposeInfo::isEnabledParamText,
                                                              TransposeInfo::isEnabledParamDefault),
                        std::make_unique<AudioParameterChoice> (TransposeInfo::noteParam,
                                                                TransposeInfo::noteParamText,
                                                                NoteInfo::getStringArray(),
                                                                TransposeInfo::noteParamDefault),
                        std::make_unique<AudioParameterChoice> (OperationInfo::operationParam,
                                                                OperationInfo::operationParamText,
                                                                OperationInfo::getStringArray(),
                                                                OperationInfo::operationParamDefault),
                        std::make_unique<AudioParameterChoice> (MidiChannelInfo::routeChannelParam,
                                                                MidiChannelInfo::routeChannelParamText,
                                                                MidiChannelInfo::getStringArray(),
                                                                MidiChannelInfo::routeChannelParamDefault),
                        std::make_unique<AudioParameterChoice> (MidiChannelInfo::controlChannelParam,
                                                                MidiChannelInfo::controlChannelParamText,
                                                                MidiChannelInfo::getStringArray(),
                                                                MidiChannelInfo::controlChannelParamDefault)
                                                 
                   })
{
    scaleNoteParam = (AudioParameterChoice*)parameters.getParameter(NoteInfo::noteParam);
    scaleTypeParam = (AudioParameterChoice*)parameters.getParameter(ScaleInfo::scaleParam);
    controlChannelParam = (AudioParameterChoice*)parameters.getParameter(MidiChannelInfo::controlChannelParam);
    operationParam = (AudioParameterChoice*)parameters.getParameter(OperationInfo::operationParam);
    routeChannelParam = (AudioParameterChoice*)parameters.getParameter(MidiChannelInfo::routeChannelParam);
    transposeNoteParam = (AudioParameterChoice*)parameters.getParameter(TransposeInfo::noteParam);
    transposeEnabledParam = (AudioParameterBool*)parameters.getParameter(TransposeInfo::isEnabledParam);
}

ScalesAudioProcessor::~ScalesAudioProcessor()
{
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
    
    MidiBuffer output;
    
    currentScaleNote = scaleNoteParam->getIndex();
    currentScale = scaleTypeParam->getIndex();
    controlChannel = controlChannelParam->getIndex();
    operation = operationParam->getIndex();
    routeChannel = routeChannelParam->getIndex();
    transposeNote = transposeNoteParam->getIndex();
    transposeEnabled = transposeEnabledParam->get();
    int noteToUse = transposeEnabled ? transposeNote : currentScaleNote;


    for (const MidiMessageMetadata metadata : midiMessages)
    {
        MidiMessage msg = metadata.getMessage();
        if (msg.getChannel() == controlChannel)
        {
            if (msg.isNoteOn())
            {
                int octave = NoteInfo::getOctave(msg.getNoteNumber());
                if (octave < scaleInfo.getScaleOptionsSize())
                {
                    *scaleTypeParam = octave;
                    *scaleNoteParam = NoteInfo::getNoteInOctave(msg.getNoteNumber());
                }
            }
            // prevent infinite note on scenario caused by control channel
            else if (msg.isNoteOff())
            {
                output.addEvent(msg, metadata.samplePosition);
            }
        }
        else if (!msg.isNoteOnOrOff())
        {
            output.addEvent(msg, metadata.samplePosition);
        } else if (operation == OperationInfo::NONE.order || scaleInfo.isNoteInScale(currentScale, noteToUse, msg.getNoteNumber())) {
            addOutputNote(output, metadata.samplePosition, msg, msg.getChannel(), msg.getNoteNumber());
        } else {
            // TODO: refactor
            if (operation == OperationInfo::DROP.order)
            {
                if (msg.isNoteOn())
                    continue;

                addOutputNote(output, metadata.samplePosition, msg, msg.getChannel(), msg.getNoteNumber());
            }
            else if (operation == OperationInfo::UP.order)
            {
                int toSet = scaleInfo.getNoteUp(currentScale, noteToUse, msg.getNoteNumber(), true);
                addOutputNote(output, metadata.samplePosition, msg, msg.getChannel(), toSet);
            }
            else if (operation == OperationInfo::DOWN.order)
            {
                int toSet = scaleInfo.getNoteDown(currentScale, noteToUse, msg.getNoteNumber(), true);
                addOutputNote(output, metadata.samplePosition, msg, msg.getChannel(), toSet);
            }
            else if (operation == OperationInfo::RAND.order)
            {
                int toSet;
                if (random.nextBool())
                    toSet = scaleInfo.getNoteDown(currentScale, noteToUse, msg.getNoteNumber(), true);
                else
                    toSet = scaleInfo.getNoteUp(currentScale, noteToUse, msg.getNoteNumber(), true);
                
                addOutputNote(output, metadata.samplePosition, msg, msg.getChannel(), toSet);
            }
            if (operation == OperationInfo::ROUTE.order)
            {
                if (routeChannel > 0)
                    addOutputNote(output, metadata.samplePosition, msg, routeChannel, msg.getNoteNumber());
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

void ScalesAudioProcessor::setNoteMap(const MidiMessage &msg, const NoteOnData &toSet)
{
    const NoteOnData msgData = NoteOnData(msg);
    
    if (msg.isNoteOn())
        noteOnMap[msgData.channel][msgData.note] = toSet;
    else if (msg.isNoteOff())
        noteOnMap[msgData.channel][msgData.note] = NoteInfo::NO_NOTE;
}

bool ScalesAudioProcessor::shouldSkipNoteOff(const MidiMessage &msg, const NoteOnData &toSet)
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
NoteOnData ScalesAudioProcessor::newToSet(const MidiMessage &msg, int channelToSet, int noteToSet)
{
    const NoteOnData msgData = NoteOnData(msg);
    const NoteOnData toSet = NoteOnData(channelToSet, noteToSet);
    
    if (msg.isNoteOff() && !(noteOnMap[msgData.channel][msgData.note] == toSet))
        return noteOnMap[msgData.channel][msgData.note];
    return toSet;
}

int ScalesAudioProcessor::transpose(int noteNumber)
{
    if (!transposeEnabled || transposeNote == currentScaleNote)
        return noteNumber;
    
    return noteNumber + TransposeInfo::getTransposeAmount(transposeNote, currentScaleNote);
}

//==============================================================================
bool ScalesAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ScalesAudioProcessor::createEditor()
{
    return new ScalesAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void ScalesAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void ScalesAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (parameters.state.getType()))
            parameters.replaceState (juce::ValueTree::fromXml (*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ScalesAudioProcessor();
}
