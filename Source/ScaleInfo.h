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
    
    static const Identifier scaleTreeID;
    static const ValueTree scaleTree;
    static const Identifier scaleID;
    
    ScaleInfo();
    
    StringArray getStringArray();
    
private:
    std::array<Scale, 2> scaleOptions;
};
