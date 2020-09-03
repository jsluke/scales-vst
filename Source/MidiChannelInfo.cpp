/*
  ==============================================================================

    ControlChannelInfo.cpp
    Created: 8 Jul 2020 6:27:20pm
    Author:  James Luke

  ==============================================================================
*/

#include "MidiChannelInfo.h"

const Identifier MidiChannelInfo::controlChannelTreeID ("ControlChannelTree");
const Identifier MidiChannelInfo::controlChannelID ("ControlChannelID");

const Identifier MidiChannelInfo::routeChannelTreeID ("RouteChannelTree");
const Identifier MidiChannelInfo::routeChannelID ("RouteChannelID");

ValueTree MidiChannelInfo::getInitialControlValueTree()
{
    ValueTree tree = ValueTree(controlChannelTreeID);
    tree.setProperty(controlChannelID, 0, nullptr);
    return tree;
}

ValueTree& MidiChannelInfo::getControlValueTree()
{
    static ValueTree channelTree = getInitialControlValueTree();
    return channelTree;
}

ValueTree MidiChannelInfo::getInitialRouteValueTree()
{
    ValueTree tree = ValueTree(routeChannelTreeID);
    tree.setProperty(routeChannelID, 0, nullptr);
    return tree;
}

ValueTree& MidiChannelInfo::getRouteValueTree()
{
    static ValueTree channelTree = getInitialRouteValueTree();
    return channelTree;
}

MidiChannelInfo::MidiChannelInfo() {
    channelOptions[0] = MidiChannel(false, 0, TRANS("None"));
    // there are 16 MIDI channels per port
    for (int i=1; i <= 16; i++)
        channelOptions[i] = MidiChannel(true, i, std::to_string(i));
};

MidiChannel MidiChannelInfo::getChannel(int optionID)
{
    return channelOptions[optionID];
}

StringArray MidiChannelInfo::getStringArray()
{
    StringArray options;
    for (MidiChannel channel : channelOptions)
        options.add(channel.localizedString);
    
    return options;
}
