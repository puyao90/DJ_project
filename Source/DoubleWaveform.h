/*
  ==============================================================================

    doubleWaveform.h
    Created: 25 Aug 2023 9:15:56pm
    Author:  sphy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

//==============================================================================
/**
 This class represents a double waveform display component.

 The DoubleWaveform class is a visual component that displays two audio waveforms,
 it's used to visualize the playerL and playerR audio content. It is designed to work with an
 AudioFormatManager and an AudioThumbnailCache to load and display audio waveforms.
*/
class DoubleWaveform  : public juce::Component,public juce::ChangeListener
{
public:
    //Constructs a DoubleWaveform component.
    DoubleWaveform(juce::AudioFormatManager& formatManagerToUse,juce::AudioThumbnailCache& cacheToUse,juce::Colour myColor);
    //Destructor. This function is called when the component needs to be repainted.
    ~DoubleWaveform() override;

    //This function is called when the component needs to be repainted.
    void paint (juce::Graphics&) override;
    //This function is called when the component is resized.
    void resized() override;
    
    
    //This function is called when the audio source changes.
    void changeListenerCallback(juce::ChangeBroadcaster *source) override;
    
    //Load an audio file from the specified URL.
    void loadURL(juce::URL audioURL);
    
    
    //Set the position of the playhead relative to its total duration.
    void setPositionRelative(double pos);
    
    //Clear the waveform display and reset the stat
    void clear();

private:
    bool fileLoaded;//Indicates whether an audio file is loaded.
    juce::AudioThumbnail audioThumb;//The audio thumbnail used for displaying waveforms.
    double position; //The position of the playhead relative to its total duration.
    juce::Colour myColor;//The color used for drawing the waveforms.
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DoubleWaveform)
};
