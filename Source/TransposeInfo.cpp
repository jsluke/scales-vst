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
