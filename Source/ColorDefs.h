/*
  ==============================================================================

    ColorDefs.h
    Created: 2 Oct 2020 8:48:47pm
    Author:  James Luke

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ComboLAF : public LookAndFeel_V4
{
public:
    ComboLAF()
    {
        setColour(ComboBox::ColourIds::backgroundColourId, Colour (0xffb0c4b1));
        setColour(ComboBox::ColourIds::textColourId, Colours::black);
        setColour(ComboBox::ColourIds::arrowColourId, Colour (0xff4a5759));
        setColour(ComboBox::ColourIds::outlineColourId, Colour (0xff4a5759));
        
        setColour(PopupMenu::ColourIds::backgroundColourId, Colour (0xffb0c4b1));
        setColour(PopupMenu::ColourIds::highlightedBackgroundColourId, Colour (0xfff7e1d7));
        setColour(PopupMenu::ColourIds::textColourId, Colour (0xff4a5759));
        setColour(PopupMenu::ColourIds::highlightedTextColourId, Colours::black);
    }
};



class ColorDefs
{
public:
    static const Colour windowBG;
    static const Colour selectBG;
};
