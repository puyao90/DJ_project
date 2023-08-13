/*
  ==============================================================================

    DeckGUI.h
    Created: 12 Aug 2023 11:36:01am
    Author:  sphy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

//==============================================================================
/*
*/
class DeckGUI  : public juce::Component
{
public:
    DeckGUI(DJAudioPlayer* player);
    ~DeckGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::TextButton playButton{"PLAY"};
    juce::TextButton stopButton{"STOP"};
    juce::TextButton loadButton{"LOAD"};
    juce::Slider volSlider;
    juce::Slider speedSlider;
    juce::Slider posSlider;
    
    DJAudioPlayer* player;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
