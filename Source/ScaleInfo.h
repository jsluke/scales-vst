/*
  ==============================================================================

    ScaleInfo.h
    Created: 7 Jul 2020 7:18:27pm
    Author:  James Luke

  ==============================================================================
*/

#pragma once

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
    const Scale MAJOR = Scale(0, TRANS("Major"));
    const Scale MINOR = Scale(1, TRANS("Minor"));
    
    ScaleInfo()
    {
        scaleOptions[MAJOR.order] = MAJOR;
        scaleOptions[MINOR.order] = MINOR;
    }
    
    StringArray getStringArray()
    {
        StringArray options;
        for (Scale scale : scaleOptions)
            options.add(scale.localizedString);
        return options;
    }
    
private:
    std::array<Scale, 2> scaleOptions;
};
