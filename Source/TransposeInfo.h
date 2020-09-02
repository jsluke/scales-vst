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
    static const Identifier isEnabledID;
    static const Identifier transNoteID;
    
    static ValueTree& getValueTree();
    
    TransposeInfo();

private:
    static const Identifier transTreeID;
    
    static ValueTree getInitialValueTree();
};
