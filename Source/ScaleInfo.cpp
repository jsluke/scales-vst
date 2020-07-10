/*
  ==============================================================================

    ScaleInfo.cpp
    Created: 8 Jul 2020 6:26:45pm
    Author:  James Luke

  ==============================================================================
*/

#include "ScaleInfo.h"

const Scale ScaleInfo::MAJOR = Scale(0, TRANS("Major"));
const Scale ScaleInfo::MINOR = Scale(1, TRANS("Minor"));

const Identifier ScaleInfo::scaleTreeID ("ScaleTree");
const ValueTree ScaleInfo::scaleTree (scaleTreeID);
const Identifier ScaleInfo::scaleID ("ScaleID");

ScaleInfo::ScaleInfo()
{
    scaleOptions[MAJOR.order] = MAJOR;
    scaleOptions[MINOR.order] = MINOR;
    initializeNoteSets();
}

StringArray ScaleInfo::getStringArray()
{
    StringArray options;
    for (Scale scale : scaleOptions)
        options.add(scale.localizedString);
    return options;
}

Scale ScaleInfo::getInitialValue()
{
    return scaleOptions[0];
}

bool ScaleInfo::isNoteInScale(Scale scale, int scaleNote, int note)
{
    // TODO: catch out of range
    return noteSets[scale.order][scaleNote][note];
}

void ScaleInfo::initializeNoteSets()
{
    // initialize major scale
    for (int i=0; i<NoteInfo::NUM_NOTES; i++)
    {
        noteSets[MAJOR.order][i][i] = true;
        noteSets[MAJOR.order][i][(i+2) % NoteInfo::NUM_NOTES] = true;
        noteSets[MAJOR.order][i][(i+4) % NoteInfo::NUM_NOTES] = true;
        noteSets[MAJOR.order][i][(i+5) % NoteInfo::NUM_NOTES] = true;
        noteSets[MAJOR.order][i][(i+7) % NoteInfo::NUM_NOTES] = true;
        noteSets[MAJOR.order][i][(i+9) % NoteInfo::NUM_NOTES] = true;
        noteSets[MAJOR.order][i][(i+11) % NoteInfo::NUM_NOTES] = true;
    }
    
    // initialize minor scale
    for (int i=0; i<NoteInfo::NUM_NOTES; i++)
    {
        noteSets[MINOR.order][i][i] = true;
        noteSets[MINOR.order][i][(i+2) % NoteInfo::NUM_NOTES] = true;
        noteSets[MINOR.order][i][(i+3) % NoteInfo::NUM_NOTES] = true;
        noteSets[MINOR.order][i][(i+5) % NoteInfo::NUM_NOTES] = true;
        noteSets[MINOR.order][i][(i+7) % NoteInfo::NUM_NOTES] = true;
        noteSets[MINOR.order][i][(i+8) % NoteInfo::NUM_NOTES] = true;
        noteSets[MINOR.order][i][(i+10) % NoteInfo::NUM_NOTES] = true;
    }
}
