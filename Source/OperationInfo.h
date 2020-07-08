/*
  ==============================================================================

    OperationInfo.h
    Created: 7 Jul 2020 7:34:13pm
    Author:  James Luke

  ==============================================================================
*/

#pragma once

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
    const Operation DROP = Operation(0, TRANS("Drop"));
    
    OperationInfo()
    {
        operationOptions[DROP.order] = DROP;
    }
    
    StringArray getStringArray()
    {
        StringArray options;
        for (Operation operation : operationOptions)
            options.add(operation.localizedString);
        return options;
    }
    
private:
    std::array<Operation, 1> operationOptions;
};
