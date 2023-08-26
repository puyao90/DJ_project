#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "PlaylistComponent.h"
#include "DoubleWaveform.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent

{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;
    
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    juce::AudioFormatManager formatManager;
    juce::AudioThumbnailCache thumbCache{100};
    

    DJAudioPlayer playerL{formatManager};
    DJAudioPlayer playerR{formatManager};
    
    DoubleWaveform waveformL{&playerL,formatManager,thumbCache};
    DoubleWaveform waveformR{&playerR,formatManager,thumbCache};
    
    DeckGUI deckGUI1{&playerL,formatManager,thumbCache,&waveformL};
    DeckGUI deckGUI2{&playerR,formatManager,thumbCache,&waveformR};
    
    
    juce::MixerAudioSource mixerSource;
    
    PlaylistComponent playlistComponent{&deckGUI1, &deckGUI2};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
