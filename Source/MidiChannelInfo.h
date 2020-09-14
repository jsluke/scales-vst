/*
  ==============================================================================

    MidiChannelInfo.h
    Created: 6 Jul 2020 5:23:07pm
    Author:  James Luke

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <array>

struct MidiChannel
{
    bool isChannel;
    int channelID;
    String localizedString;
    MidiChannel() {};
    MidiChannel(bool isChannel, int channelID, String localizedString) :
        isChannel(isChannel), channelID(channelID), localizedString(localizedString) {}
};

class MidiChannelInfo
{
    
public:
    static const Identifier controlChannelID;
    static ValueTree& getControlValueTree();
    
    static const String controlChannelParam;
    static const String controlChannelParamText;
    static const int    controlChannelParamDefault;
    
    static const Identifier routeChannelID;
    static ValueTree& getRouteValueTree();
    
    static const String routeChannelParam;
    static const String routeChannelParamText;
    static const int    routeChannelParamDefault;
    
    static StringArray getStringArray();
    
    MidiChannelInfo();
    
    MidiChannel getChannel(int optionID);

private:
    static const Identifier controlChannelTreeID;
    static ValueTree getInitialControlValueTree();
    
    static const Identifier routeChannelTreeID;
    static ValueTree getInitialRouteValueTree();
    
    std::array<MidiChannel, 17> channelOptions;
};
