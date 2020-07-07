/*
  ==============================================================================

    ControlChannelInfo.h
    Created: 6 Jul 2020 5:23:07pm
    Author:  James Luke

  ==============================================================================
*/

#pragma once

#include <array>

struct ControlChannel {
    bool isChannel;
    int channelID;
    String localizedString;
    ControlChannel() {};
    ControlChannel(bool isChannel, int channelID, String localizedString) :
        isChannel(isChannel), channelID(channelID), localizedString(localizedString) {}
};

class ControlChannelInfo {
    
public:
    ControlChannelInfo() {
        channelOptions[0] = ControlChannel(false, 0, TRANS("None"));
        // there are 16 MIDI channels per port
        for (int i=1; i <= 16; i++)
            channelOptions[i] = ControlChannel(true, i, std::to_string(i));
    };
    
    ControlChannel getChannel(int optionID)
    {
        return channelOptions[optionID];
    }
    
    StringArray getStringArray()
    {
        StringArray options;
        for (ControlChannel channel : channelOptions)
            options.add(channel.localizedString);
        
        return options;
    }

    
private:
    std::array<ControlChannel, 17> channelOptions;
};
