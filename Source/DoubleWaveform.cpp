/*
  ==============================================================================

    doubleWaveform.cpp
    Created: 25 Aug 2023 9:15:56pm
    Author:  sphy

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DoubleWaveform.h"


//==============================================================================
DoubleWaveform::DoubleWaveform(juce::AudioFormatManager& formatManagerToUse,juce::AudioThumbnailCache& cacheToUse,juce::Colour _myColor):fileLoaded(false),audioThumb(1000,formatManagerToUse,cacheToUse),position(0),myColor(_myColor)
{
    audioThumb.addChangeListener(this);
}

DoubleWaveform::~DoubleWaveform()
{
}

void DoubleWaveform::paint (juce::Graphics& g)
{

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (myColor);
    if(fileLoaded){
        audioThumb.drawChannel(g, getLocalBounds(), 0, audioThumb.getTotalLength(), 0, 1.0f);
        g.setColour(juce::Colours::white);
        g.drawRect(position*getWidth(), 0, getWidth()/42, getHeight());
    }else{
    g.setFont (20.0f);
    g.drawText ("File not loaded...", getLocalBounds(), juce::Justification::centred, true);
    }
}

void DoubleWaveform::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void DoubleWaveform::clear() {
    audioThumb.clear();
    fileLoaded = false;
}

void DoubleWaveform::loadURL(juce::URL audioURL){
    audioThumb.clear();
    fileLoaded=audioThumb.setSource(new juce::URLInputSource(audioURL));
    if(fileLoaded){
        std::cout<<"DoubleWaveform::loadURL  loaded!"<<std::endl;
    }
    else{std::cout<<"DoubleWaveform::loadURL   not loaded!"<<std::endl;}
}

void DoubleWaveform::changeListenerCallback(juce::ChangeBroadcaster *source){
//    std::cout<<"WaveformDisplay change received!"<<std::endl;
    repaint();
}

void DoubleWaveform::setPositionRelative(double pos){
    if(pos!=position){
        position=pos;
        repaint();
    }
}
