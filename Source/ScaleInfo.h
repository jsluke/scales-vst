/*
  ==============================================================================

    ScaleInfo.h
    Created: 7 Jul 2020 7:18:27pm
    Author:  James Luke

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>

#include "NoteInfo.h"

struct Scale
{
    int order;
    String localizedString;
    
    Scale() {};
    Scale(int order, String localizedString) : order(order), localizedString(localizedString) {};
};
    
class ScaleInfo
{
public:
    static const Scale MAJOR;
    static const Scale MINOR;
    static const Scale MINOR_H;
    static const Scale DORIAN;
    static const Scale BLUES_MIN;
    static const Scale BLUES_MAJ;
    static const Scale WHOLE;
    static const Scale MIN_PENT;
    static const Scale MAJ_PENT;
    static const Scale SUPER_L;
    
    static const String scaleParam;
    static const String scaleParamText;
    static const int    scaleParamDefault;
    
    static StringArray getStringArray();
    
    ScaleInfo();
    
    bool isNoteInScale(int scaleID, int scaleNote, int note);
    int getNoteUp(int scaleID, int scaleNote, int note, bool getNoteDownNotFound);
    int getNoteDown(int scaleID, int scaleNote, int note, bool getNoteUpNotFound);
    
private:
    static std::vector<Scale> getScales();
    
    std::vector<Scale> scaleOptions;
    //essentially bool[index to scale type][index to scale][index to "is this note within the scale?"]
    std::vector<std::array<std::array<bool,NoteInfo::NUM_NOTES>,NoteInfo::NUM_NOTES>> noteSets;
    
    void initializeNoteSets();
};
