/*
  ==============================================================================

    RowComponent.h
    Created: 24 Aug 2023 11:57:49am
    Author:  sphy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

/*
 This struct represents a row of data for the tableComponent in PlaylistComponent.

 The RowComponent struct stores information about a row, including the options
 for left and right, title, and file associated with the row.
 */

struct RowComponent
{
    bool options[2]; // An array to store left and right options. Index 0: left, Index 1: right
    juce::String title; //The title associated with the row.
    juce::File file; //The file associated with the row.
    
    RowComponent(bool left, bool right, const std::string& title, const juce::File& file)
        : title(title), file(file)
    {
        options[0] = left;
        options[1] = right;
    }
    
    
    bool left() const //Get the left option for the row.
    {
        return options[0];
    }
    
    bool& left()
    {
        return options[0];
    }
    
    bool right() const //Get the right option for the row.
    {
        return options[1];
    }
    
    bool& right()
    {
        return options[1];
    }
};
