/*
  ==============================================================================

    TransposeInfo.h
    Created: 19 Aug 2020 7:08:50pm
    Author:  James Luke

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class TransposeInfo
{
    
public:
    static const Identifier isEnabledID; //TODO: remove
    static const String isEnabledParam;
    static const String isEnabledParamText;
    static const bool   isEnabledParamDefault;
    
    static const Identifier transNoteID; //TODO: remove
    static const String noteParam;
    static const String noteParamText;
    static const int    noteParamDefault;
    
    static ValueTree& getValueTree();
    
    static int getTransposeAmount(int transposeNote, int scaleNote);
    
    TransposeInfo();

private:
    static const Identifier transTreeID;
    
    static ValueTree getInitialValueTree();
};
