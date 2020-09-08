/*
  ==============================================================================

    NoteInfo.h
    Created: 7 Jul 2020 2:42:51pm
    Author:  James Luke

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <array>

struct Note
{
    int order;
    String localizedString;
    
    Note() {};
    Note(int order, String localizedString) : order(order), localizedString(localizedString) {};
};

// TODO: move this elsewhere?
struct NoteOnData
{
    int channel;
    int note;
    
    NoteOnData() {};
    NoteOnData(int channel, int note) : channel(channel), note(note) {};
    NoteOnData(MidiMessage msg)
    {
        channel = msg.getChannel();
        note = msg.getNoteNumber();
    }
    
    bool operator==(const NoteOnData& other) const
    {
        return channel == other.channel && note == other.note;
    }
    
    bool operator>(const NoteOnData& other) const
    {
        return channel < other.channel || (channel == other.channel && note < other.note);
    }
};

class NoteInfo
{
public:
    static const int NUM_NOTES = 12;
    static const NoteOnData NO_NOTE;
    static const Identifier noteID;
    
    static ValueTree& getValueTree();
    
    static int getOctave(int note);
    static int getNoteInOctave(int note);
    
    NoteInfo();
    
    StringArray getStringArray();

private:
    static const Identifier noteTreeID;
    static const String notes[NUM_NOTES];
    
    static ValueTree getInitialValueTree();
    
    std::array<Note, NUM_NOTES> noteOptions;
};





