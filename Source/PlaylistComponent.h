/*
  ==============================================================================

    PlaylistComponent.h
    Created: 19 Aug 2023 8:40:42pm
    Author:  sphy

  ==============================================================================
*/

#pragma once
#include "DJAudioPlayer.h"
#include <JuceHeader.h>

//==============================================================================
/*
*/
class PlaylistComponent  : public juce::Component,
                           public juce::TableListBoxModel,
                           public juce::Button::Listener
{
public:
    PlaylistComponent(DJAudioPlayer* _leftPlayer, DJAudioPlayer* _rightPlayer);
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
    std::vector<std::string> trackTitles;
    std::vector<juce::File> selectedFiles;
    DJAudioPlayer* leftPlayer;
    DJAudioPlayer* rightPlayer;
    juce::FileChooser fChooser{"Select a file..."};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
