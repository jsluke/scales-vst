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

class NoteInfo
{
public:
    static const int NUM_NOTES = 12;
    static const Identifier noteTreeID;
    static const ValueTree noteTree;
    static const Identifier noteID;
    
    static int getOctave(int note);
    static int getNoteInOctave(int note);
    
    NoteInfo();
    
    StringArray getStringArray();

private:
    static const String notes[NUM_NOTES];
    std::array<Note, NUM_NOTES> noteOptions;
};





