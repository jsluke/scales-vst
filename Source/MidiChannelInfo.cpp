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

const String MidiChannelInfo::controlChannelParam = "ControlChannelParam";
const String MidiChannelInfo::controlChannelParamText = TRANS("MIDI Control Channel");
const int    MidiChannelInfo::controlChannelParamDefault = 0;

const Identifier MidiChannelInfo::routeChannelTreeID ("RouteChannelTree");
const Identifier MidiChannelInfo::routeChannelID ("RouteChannelID");

const String MidiChannelInfo::routeChannelParam = "RouteChannelParam";
const String MidiChannelInfo::routeChannelParamText = TRANS("Route Option MIDI Channel");
const int    MidiChannelInfo::routeChannelParamDefault = 0;

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
    options.add(TRANS("None"));
    
    // there are 16 MIDI channels per port
    for (int i=1; i <= 16; i++)
        options.add(std::to_string(i));
    
    return options;
}
