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
const ValueTree OperationInfo::operationTree (operationTreeID);
const Identifier OperationInfo::operationID ("OperationID");

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
