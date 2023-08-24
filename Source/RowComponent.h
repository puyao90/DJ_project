/*
  ==============================================================================

    RowComponent.h
    Created: 24 Aug 2023 11:57:49am
    Author:  sphy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

struct RowComponent
{
    bool options[2]; // Index 0: left, Index 1: right
    juce::String title;
    juce::File file;
    
    RowComponent(bool left, bool right, const std::string& title, const juce::File& file)
        : title(title), file(file)
    {
        options[0] = left;
        options[1] = right;
    }
    
    
    bool left() const
    {
        return options[0];
    }
    
    bool& left()
    {
        return options[0];
    }
    
    bool right() const
    {
        return options[1];
    }
    
    bool& right()
    {
        return options[1];
    }
};
