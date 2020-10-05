/*
  ==============================================================================

    ScaleInfo.cpp
    Created: 8 Jul 2020 6:26:45pm
    Author:  James Luke

  ==============================================================================
*/

#include "ScaleInfo.h"

const Scale ScaleInfo::MAJOR     = Scale(0, TRANS("Major"));
const Scale ScaleInfo::MINOR     = Scale(1, TRANS("Minor"));
const Scale ScaleInfo::MINOR_H   = Scale(2, TRANS("Harmonic Minor"));
const Scale ScaleInfo::DORIAN    = Scale(3, TRANS("Dorian"));
const Scale ScaleInfo::BLUES_MIN = Scale(4, TRANS("Blues Minor"));
const Scale ScaleInfo::BLUES_MAJ = Scale(5, TRANS("Blues Major"));
const Scale ScaleInfo::WHOLE     = Scale(6, TRANS("Whole Tone"));
const Scale ScaleInfo::MIN_PENT  = Scale(7, TRANS("Minor Pentatonic"));
const Scale ScaleInfo::MAJ_PENT  = Scale(8, TRANS("Major Pentatonic"));
const Scale ScaleInfo::SUPER_L   = Scale(9, TRANS("Super Locrian"));

const String ScaleInfo::scaleParam = "ScaleParam";
const String ScaleInfo::scaleParamText = TRANS("Scale Type");
const int ScaleInfo::scaleParamDefault = 0;

ScaleInfo::ScaleInfo()
{
    scaleOptions = getScales();
    initializeNoteSets();
}

std::vector<Scale> ScaleInfo::getScales()
{
    std::vector<Scale> val;
    val.push_back(MAJOR);
    val.push_back(MINOR);
    val.push_back(MINOR_H);
    val.push_back(DORIAN);
    val.push_back(BLUES_MIN);
    val.push_back(BLUES_MAJ);
    val.push_back(WHOLE);
    val.push_back(MIN_PENT);
    val.push_back(MAJ_PENT);
    val.push_back(SUPER_L);
    
    return val;
}

StringArray ScaleInfo::getStringArray()
{
    StringArray options;
    for (Scale scale : getScales())
    {
        options.add(scale.localizedString);
    }
    return options;
}

bool ScaleInfo::isNoteInScale(int scaleID, int scaleNote, int note)
{
    // TODO: catch out of range
    return noteSets[scaleID][scaleNote][NoteInfo::getNoteInOctave(note)];
}

int ScaleInfo::getNoteUp(int scaleID, int scaleNote, int note, bool getNoteDownNotFound)
{
    int findNote = note;
    do {
        if (isNoteInScale(scaleID, scaleNote, findNote))
            return findNote;
        findNote++;
    } while (findNote <= 127);
    
    if (getNoteDownNotFound)
        return getNoteDown(scaleID, scaleNote, note, false);
    else
        return -1; // TODO: throw except?
}

int ScaleInfo::getNoteDown(int scaleID, int scaleNote, int note, bool getNoteUpNotFound)
{
    int findNote = note;
    do {
        if (isNoteInScale(scaleID, scaleNote, findNote))
            return findNote;
        findNote--;
    } while (findNote >= 0);
    
    if (getNoteUpNotFound)
        return getNoteUp(scaleID, scaleNote, note, false);
    else
        return -1; // TODO: throw except?
}

void ScaleInfo::initializeNoteSets()
{
    for (int i=0; i<scaleOptions.size(); i++)
        noteSets.push_back(std::array<std::array<bool,NoteInfo::NUM_NOTES>,NoteInfo::NUM_NOTES>());
    
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
    
    // initialize harmonic minor scale
    for (int i=0; i<NoteInfo::NUM_NOTES; i++)
    {
        noteSets[MINOR_H.order][i][i] = true;
        noteSets[MINOR_H.order][i][(i+2) % NoteInfo::NUM_NOTES] = true;
        noteSets[MINOR_H.order][i][(i+3) % NoteInfo::NUM_NOTES] = true;
        noteSets[MINOR_H.order][i][(i+5) % NoteInfo::NUM_NOTES] = true;
        noteSets[MINOR_H.order][i][(i+7) % NoteInfo::NUM_NOTES] = true;
        noteSets[MINOR_H.order][i][(i+8) % NoteInfo::NUM_NOTES] = true;
        noteSets[MINOR_H.order][i][(i+11) % NoteInfo::NUM_NOTES] = true;
    }
    
    // initialize dorian scale
    for (int i=0; i<NoteInfo::NUM_NOTES; i++)
    {
        noteSets[DORIAN.order][i][i] = true;
        noteSets[DORIAN.order][i][(i+2) % NoteInfo::NUM_NOTES] = true;
        noteSets[DORIAN.order][i][(i+3) % NoteInfo::NUM_NOTES] = true;
        noteSets[DORIAN.order][i][(i+5) % NoteInfo::NUM_NOTES] = true;
        noteSets[DORIAN.order][i][(i+7) % NoteInfo::NUM_NOTES] = true;
        noteSets[DORIAN.order][i][(i+9) % NoteInfo::NUM_NOTES] = true;
        noteSets[DORIAN.order][i][(i+10) % NoteInfo::NUM_NOTES] = true;
    }
    
    // initialize blues minor scale
    for (int i=0; i<NoteInfo::NUM_NOTES; i++)
    {
        noteSets[BLUES_MIN.order][i][i] = true;
        noteSets[BLUES_MIN.order][i][(i+3) % NoteInfo::NUM_NOTES] = true;
        noteSets[BLUES_MIN.order][i][(i+5) % NoteInfo::NUM_NOTES] = true;
        noteSets[BLUES_MIN.order][i][(i+6) % NoteInfo::NUM_NOTES] = true;
        noteSets[BLUES_MIN.order][i][(i+7) % NoteInfo::NUM_NOTES] = true;
        noteSets[BLUES_MIN.order][i][(i+10) % NoteInfo::NUM_NOTES] = true;
    }
    
    // initialize blues major scale
    for (int i=0; i<NoteInfo::NUM_NOTES; i++)
    {
        noteSets[BLUES_MAJ.order][i][i] = true;
        noteSets[BLUES_MAJ.order][i][(i+2) % NoteInfo::NUM_NOTES] = true;
        noteSets[BLUES_MAJ.order][i][(i+3) % NoteInfo::NUM_NOTES] = true;
        noteSets[BLUES_MAJ.order][i][(i+4) % NoteInfo::NUM_NOTES] = true;
        noteSets[BLUES_MAJ.order][i][(i+7) % NoteInfo::NUM_NOTES] = true;
        noteSets[BLUES_MAJ.order][i][(i+9) % NoteInfo::NUM_NOTES] = true;
    }
    
    // initialize whole tone scale
    for (int i=0; i<NoteInfo::NUM_NOTES; i++)
    {
        noteSets[BLUES_MAJ.order][i][i] = true;
        noteSets[BLUES_MAJ.order][i][(i+2) % NoteInfo::NUM_NOTES] = true;
        noteSets[BLUES_MAJ.order][i][(i+4) % NoteInfo::NUM_NOTES] = true;
        noteSets[BLUES_MAJ.order][i][(i+6) % NoteInfo::NUM_NOTES] = true;
        noteSets[BLUES_MAJ.order][i][(i+8) % NoteInfo::NUM_NOTES] = true;
        noteSets[BLUES_MAJ.order][i][(i+10) % NoteInfo::NUM_NOTES] = true;
    }
    
    // initialize minor pentatonic scale
    for (int i=0; i<NoteInfo::NUM_NOTES; i++)
    {
        noteSets[MIN_PENT.order][i][i] = true;
        noteSets[MIN_PENT.order][i][(i+3) % NoteInfo::NUM_NOTES] = true;
        noteSets[MIN_PENT.order][i][(i+5) % NoteInfo::NUM_NOTES] = true;
        noteSets[MIN_PENT.order][i][(i+7) % NoteInfo::NUM_NOTES] = true;
        noteSets[MIN_PENT.order][i][(i+10) % NoteInfo::NUM_NOTES] = true;
    }
    
    // initialize minor pentatonic scale
    for (int i=0; i<NoteInfo::NUM_NOTES; i++)
    {
        noteSets[MAJ_PENT.order][i][i] = true;
        noteSets[MAJ_PENT.order][i][(i+2) % NoteInfo::NUM_NOTES] = true;
        noteSets[MAJ_PENT.order][i][(i+4) % NoteInfo::NUM_NOTES] = true;
        noteSets[MAJ_PENT.order][i][(i+7) % NoteInfo::NUM_NOTES] = true;
        noteSets[MAJ_PENT.order][i][(i+9) % NoteInfo::NUM_NOTES] = true;
    }
    
    // initialize super locrian scale
    for (int i=0; i<NoteInfo::NUM_NOTES; i++)
    {
        noteSets[SUPER_L.order][i][i] = true;
        noteSets[SUPER_L.order][i][(i+1) % NoteInfo::NUM_NOTES] = true;
        noteSets[SUPER_L.order][i][(i+3) % NoteInfo::NUM_NOTES] = true;
        noteSets[SUPER_L.order][i][(i+4) % NoteInfo::NUM_NOTES] = true;
        noteSets[SUPER_L.order][i][(i+6) % NoteInfo::NUM_NOTES] = true;
        noteSets[SUPER_L.order][i][(i+8) % NoteInfo::NUM_NOTES] = true;
        noteSets[SUPER_L.order][i][(i+10) % NoteInfo::NUM_NOTES] = true;
    }
}
