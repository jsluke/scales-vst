/*
  ==============================================================================

    ControlChannelInfo.h
    Created: 6 Jul 2020 5:23:07pm
    Author:  James Luke

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <array>

struct ControlChannel
{
    bool isChannel;
    int channelID;
    String localizedString;
    ControlChannel() {};
    ControlChannel(bool isChannel, int channelID, String localizedString) :
        isChannel(isChannel), channelID(channelID), localizedString(localizedString) {}
};

class ControlChannelInfo
{
    
public:
    ControlChannelInfo();
    
    ControlChannel getChannel(int optionID);
    StringArray getStringArray();

private:
    std::array<ControlChannel, 17> channelOptions;
};
