/*
  ==============================================================================

    ControlChannelInfo.h
    Created: 6 Jul 2020 5:23:07pm
    Author:  James Luke

  ==============================================================================
*/

#pragma once

#include <array>

class ControlChannelInfo {
    
public:
    ControlChannelInfo() {};
    
    static const int NONE = 0;
    
    static int isOptionChannel(int option) {
        return option != NONE;
    }
    
//    const std::array<String, 17> allOptions = {
//        TRANS("None"),"1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16"
//    };
    
    const StringArray allOptions = {
        TRANS("None"),"1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16"
    };
};
