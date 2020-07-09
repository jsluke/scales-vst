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
    Identifier noteTree;
    Identifier noteID;
    
    
    NoteInfo()
    {
        noteTree = Identifier("NoteTree");
        noteID = Identifier("NoteID");
        for (int i=0; i<NUM_NOTES; i++)
            noteOptions[i] = Note(i, notes[i]);
    }
    
    StringArray getStringArray()
    {
        StringArray options;
        for (Note note : noteOptions)
            options.add(note.localizedString);
        return options;
    }

private:
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
    
    std::array<Note, NUM_NOTES> noteOptions;
};





