/*
  ==============================================================================

    WaveformDisplay.h
    Created: 15 Aug 2023 11:22:24am
    Author:  sphy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveformDisplay  : public juce::Component,public juce::ChangeListener
{
public:
    WaveformDisplay(juce::AudioFormatManager& formatManagerToUse,juce::AudioThumbnailCache& cacheToUse);
    ~WaveformDisplay() override;

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
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
