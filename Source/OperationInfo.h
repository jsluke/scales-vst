/*
  ==============================================================================

    OperationInfo.h
    Created: 7 Jul 2020 7:34:13pm
    Author:  James Luke

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <array>

struct Operation
{
    int order;
    String localizedString;
    
    Operation() {};
    Operation(int order, String localizedString) : order(order), localizedString(localizedString) {};
};
    
class OperationInfo
{
public:
    static const Operation DROP;
    static const Identifier operationTreeID;
    static const ValueTree operationTree;
    static const Identifier operationID;
    
    OperationInfo();
    
    StringArray getStringArray();

private:
    std::array<Operation, 1> operationOptions;
};
