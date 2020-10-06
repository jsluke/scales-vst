/*
  ==============================================================================

    NoteInfo.cpp
    Created: 8 Jul 2020 5:54:25pm
    Author:  James Luke

  ==============================================================================
*/

#include "NoteInfo.h"

const NoteOnData NoteInfo::NO_NOTE = NoteOnData(-1, -1);

const String NoteInfo::noteParam = "ScaleNoteParam";
const String NoteInfo::noteParamText = TRANS("Scale Note");
const int NoteInfo::noteParamDefault = 0;

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
    for (int i=0; i<NUM_NOTES; i++)
        options.add(notes[i]);
    return options;
}

int NoteInfo::getOctave(int note)
{
    return note / NUM_NOTES;
}

int NoteInfo::getNoteInOctave(int note)
{
    return note % NUM_NOTES;
}
