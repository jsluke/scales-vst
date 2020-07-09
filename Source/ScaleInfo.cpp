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

ScaleInfo::ScaleInfo()
{
    scaleOptions[MAJOR.order] = MAJOR;
    scaleOptions[MINOR.order] = MINOR;
}

StringArray ScaleInfo::getStringArray()
{
    StringArray options;
    for (Scale scale : scaleOptions)
        options.add(scale.localizedString);
    return options;
}
