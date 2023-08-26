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
/*
*/
class DoubleWaveform  : public juce::Component,public juce::ChangeListener
{
public:
    DoubleWaveform(juce::AudioFormatManager& formatManagerToUse,juce::AudioThumbnailCache& cacheToUse,juce::Colour myColor);
    ~DoubleWaveform() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void changeListenerCallback(juce::ChangeBroadcaster *source) override;
    
    void loadURL(juce::URL audioURL);
    
    void setPositionRelative(double pos);
    
    void clear();

private:
    bool fileLoaded;
    juce::AudioThumbnail audioThumb;
    double position;
    juce::Colour myColor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DoubleWaveform)
};
