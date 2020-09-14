/*
  ==============================================================================

    OperationInfo.cpp
    Created: 8 Jul 2020 6:27:00pm
    Author:  James Luke

  ==============================================================================
*/

#include "OperationInfo.h"

const Operation OperationInfo::DROP = Operation(0, TRANS("Drop"));
const Operation OperationInfo::UP = Operation(1, TRANS("Up"));
const Operation OperationInfo::DOWN = Operation(2, TRANS("Down"));
const Operation OperationInfo::RAND = Operation(3, TRANS("Random"));
const Operation OperationInfo::ROUTE = Operation(4, TRANS("Route"));

const Identifier OperationInfo::operationTreeID ("OperationTree");
const Identifier OperationInfo::operationID ("OperationID");

const String OperationInfo::operationParam = "OperationParam";
const String OperationInfo::operationParamText = TRANS("Transform Operation");
const int OperationInfo::operationParamDefault = 0;

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
    operationOptions[UP.order] = UP;
    operationOptions[DOWN.order] = DOWN;
    operationOptions[RAND.order] = RAND;
    operationOptions[ROUTE.order] = ROUTE;
}

StringArray OperationInfo::getStringArray()
{
    StringArray options;
    options.add(DROP.localizedString);
    options.add(UP.localizedString);
    options.add(DOWN.localizedString);
    options.add(RAND.localizedString);
    options.add(ROUTE.localizedString);
    return options;
}
