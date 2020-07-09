/*
  ==============================================================================

    ControlChannelInfo.cpp
    Created: 8 Jul 2020 6:27:20pm
    Author:  James Luke

  ==============================================================================
*/

#include "ControlChannelInfo.h"

ControlChannelInfo::ControlChannelInfo() {
    channelOptions[0] = ControlChannel(false, 0, TRANS("None"));
    // there are 16 MIDI channels per port
    for (int i=1; i <= 16; i++)
        channelOptions[i] = ControlChannel(true, i, std::to_string(i));
};

ControlChannel ControlChannelInfo::getChannel(int optionID)
{
    return channelOptions[optionID];
}

StringArray ControlChannelInfo::getStringArray()
{
    StringArray options;
    for (ControlChannel channel : channelOptions)
        options.add(channel.localizedString);
    
    return options;
}
