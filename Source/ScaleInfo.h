/*
  ==============================================================================

    ScaleInfo.h
    Created: 7 Jul 2020 7:18:27pm
    Author:  James Luke

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <array>

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
    
    static const Identifier scaleID;
    
    static ValueTree& getValueTree();
    
    ScaleInfo();
    
    StringArray getStringArray();
    bool isNoteInScale(int scaleID, int scaleNote, int note);
    int getNoteUp(int scaleID, int scaleNote, int note, bool getNoteDownNotFound);
    int getNoteDown(int scaleID, int scaleNote, int note, bool getNoteUpNotFound);
    
private:
    static const Identifier scaleTreeID;
    static ValueTree getInitialValueTree();
    
    std::array<Scale, 2> scaleOptions;
    bool noteSets[2][NoteInfo::NUM_NOTES][NoteInfo::NUM_NOTES] = {0};
    
    void initializeNoteSets();
};
