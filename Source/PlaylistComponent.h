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
    void paintRowBackground (juce::Graphics &, int rowNumber, int width, int height, bool rowIsSelected) override;
    void paintCell (juce::Graphics &, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    juce::Component* refreshComponentForCell (int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate) override;
    
    void buttonClicked (juce::Button* button) override;

private:
    juce::TextButton loadButton{"Load to Playlist"};
    juce::TableListBox tableComponent;
    std::vector<RowComponent> rows;
    DeckGUI* leftGui;
    DeckGUI* rightGui;
    int selectedLeftRowIdx;
    int selectedRightRowIdx;
    bool freeze;
    juce::FileChooser fileChooser{"Select a file..."};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
