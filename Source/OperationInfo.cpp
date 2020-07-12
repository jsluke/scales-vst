/*
  ==============================================================================

    OperationInfo.cpp
    Created: 8 Jul 2020 6:27:00pm
    Author:  James Luke

  ==============================================================================
*/

#include "OperationInfo.h"

const Operation OperationInfo::DROP = Operation(0, TRANS("Drop"));

const Identifier OperationInfo::operationTreeID ("OperationTree");
const Identifier OperationInfo::operationID ("OperationID");

ValueTree OperationInfo::getInitialValueTree()
{
    ValueTree tree = ValueTree(operationTreeID);
    tree.setProperty(operationID, 0, nullptr);
    return tree;
}

ValueTree& OperationInfo::getValueTree()
{
    static ValueTree operationTree = getInitialValueTree();
    return operationTree;
}


OperationInfo::OperationInfo()
{
    operationOptions[DROP.order] = DROP;
}

StringArray OperationInfo::getStringArray()
{
    StringArray options;
    for (Operation operation : operationOptions)
        options.add(operation.localizedString);
    return options;
}
