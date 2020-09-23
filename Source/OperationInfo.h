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
    String description;
    
    Operation() {};
    Operation(int order, String localizedString, String description) : order(order), localizedString(localizedString), description(description) {};
};
    
class OperationInfo
{
public:
    static const Operation DROP;
    static const Operation UP;
    static const Operation DOWN;
    static const Operation RAND;
    static const Operation ROUTE;
    static const Operation NONE;
    static const Identifier operationID;
    
    static const String operationParam;
    static const String operationParamText;
    static const int    operationParamDefault;
    
    static ValueTree& getValueTree();
    static StringArray getStringArray();
    
    OperationInfo();
    String getDescripton(int index);

private:
    static const Identifier operationTreeID;
    
    static ValueTree getInitialValueTree();
    
    std::array<Operation, 6> operationOptions;
};
