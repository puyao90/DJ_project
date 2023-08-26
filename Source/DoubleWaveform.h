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
class DoubleWaveform  : public juce::Component
{
public:
    DoubleWaveform(DJAudioPlayer* player,juce::AudioFormatManager& formatManagerToUse,juce::AudioThumbnailCache& cacheToUse);
    ~DoubleWaveform() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void loadURL(juce::URL audioURL);

private:
    DJAudioPlayer* player;
    bool fileLoaded;
    juce::AudioThumbnail audioThumb;
    double position;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DoubleWaveform)
};
