/*
  ==============================================================================

    TransposeInfo.cpp
    Created: 19 Aug 2020 7:08:50pm
    Author:  James Luke

  ==============================================================================
*/

#include "TransposeInfo.h"

const Identifier TransposeInfo::transTreeID ("TransposeTree");
const Identifier TransposeInfo::isEnabledID ("isTransposeEnabledID");
const Identifier TransposeInfo::transNoteID ("TransposeNoteID");

const String TransposeInfo::isEnabledParam = "IsEnabledTransposeParam";
const String TransposeInfo::isEnabledParamText = TRANS("Enable Transpose");
const bool   TransposeInfo::isEnabledParamDefault = false;

const String TransposeInfo::noteParam = "TransposeNoteParam";
const String TransposeInfo::noteParamText = TRANS("Transpose From Note");
const int    TransposeInfo::noteParamDefault = 0;

ValueTree TransposeInfo::getInitialValueTree()
{
    ValueTree tree = ValueTree(transTreeID);
    tree.setProperty(isEnabledID, false, nullptr);
    tree.setProperty(transNoteID, 0, nullptr);
    return tree;
}

ValueTree& TransposeInfo::getValueTree()
{
    static ValueTree channelTree = getInitialValueTree();
    return channelTree;
}

int TransposeInfo::getTransposeAmount(int transposeNote, int scaleNote)
{
    int up;
    int down;

    if (transposeNote > scaleNote)
    {
        up = 12 - transposeNote + scaleNote;
        down = scaleNote - transposeNote;
    }
    else {
        up = scaleNote - transposeNote;
        down = -12 - transposeNote + scaleNote;
    }

    // use smallest distance
    return abs(up) <= abs(down) ? up : down;
}
