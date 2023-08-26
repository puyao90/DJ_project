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
#include "DoubleWaveform.h"

//==============================================================================
/*
*/
class DeckGUI  : public juce::Component,
                public juce::Button::Listener,
                public juce::Slider::Listener,
                public juce::FileDragAndDropTarget,
                public juce::Timer
                
{
    

public:
    DeckGUI(DJAudioPlayer* player,
            juce::AudioFormatManager& formatManagerToUse,
            juce::AudioThumbnailCache& cacheToUse,
            DoubleWaveform* doubleWaveform);
    ~DeckGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void buttonClicked(juce::Button *) override;
    void sliderValueChanged (juce::Slider *slider) override;
    
    bool isInterestedInFileDrag(const juce::StringArray &files) override;
    void filesDropped(const juce::StringArray &files, int x, int y) override;
    void loadToMyGui();
    void addToMyGui(juce::File chosenFile);
    void timerCallback() override;
    void clearWaveDisplay();
    

private:
    juce::TextButton playButton{"PLAY"};
    juce::TextButton stopButton{"STOP"};
    juce::Slider volSlider;
    juce::Slider speedSlider;
    juce::Slider posSlider;
    juce::Label volLabel;
    juce::Label speedLabel;
    juce::Label posLabel;
    
    juce::FileChooser fChooser{"Select a file..."};
    DJAudioPlayer* player;
    DoubleWaveform* doubleWaveform;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
