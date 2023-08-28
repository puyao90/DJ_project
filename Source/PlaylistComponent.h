/*
  ==============================================================================

    PlaylistComponent.h
    Created: 19 Aug 2023 8:40:42pm
    Author:  sphy

  ==============================================================================
*/

#pragma once
#include "DeckGUI.h"
#include <JuceHeader.h>
#include "RowComponent.h"
//==============================================================================
/*
 This class represents the playlist component.

 The PlaylistComponent class is a graphical component that displays a table with
 rows of data. It implements the TableListBoxModel and Button::Listener interfaces.
 
 Because the table contains JUCE components such as TextButton and ToggleButton, this
 function is crucial for creating and updating these components within the cells.

*/
class PlaylistComponent  : public juce::Component,
                           public juce::TableListBoxModel,
                           public juce::Button::Listener
{
public:
    PlaylistComponent(DeckGUI* _leftGui, DeckGUI* _rightGui);
    ~PlaylistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    int getNumRows() override;
    //Paints the content of a cell in the table.
    void paintRowBackground (juce::Graphics &, int rowNumber, int width, int height, bool rowIsSelected) override;
    //Creates or updates a component for a specific cell.
    void paintCell (juce::Graphics &, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    
    //This function is called when a cell in the table needs to be refreshed or updated. It creates a new or reuses an existing component to display the content of the specified cell.
    juce::Component* refreshComponentForCell (int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate) override;
    
    void buttonClicked (juce::Button* button) override;

private:
    juce::TextButton loadButton{"Load to Playlist"};
    juce::TableListBox tableComponent;
    std::vector<RowComponent> rows;
    DeckGUI* leftGui;
    DeckGUI* rightGui;
    juce::FileChooser fileChooser{"Select a file..."};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
