/*
  ==============================================================================

    NoteInfo.cpp
    Created: 8 Jul 2020 5:54:25pm
    Author:  James Luke

  ==============================================================================
*/

#include "NoteInfo.h"

const Identifier NoteInfo::noteTreeID ("NoteTree");
const ValueTree NoteInfo::noteTree (noteTreeID);
const Identifier NoteInfo::noteID ("NoteID");

const String NoteInfo::notes[NoteInfo::NUM_NOTES] = {
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

NoteInfo::NoteInfo()
{
    for (int i=0; i<NUM_NOTES; i++)
        noteOptions[i] = Note(i, notes[i]);
}

StringArray NoteInfo::getStringArray()
{
    StringArray options;
    for (Note note : noteOptions)
        options.add(note.localizedString);
    return options;
}
