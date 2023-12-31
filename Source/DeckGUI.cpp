/*
  ==============================================================================

    DeckGUI.cpp
    Created: 12 Aug 2023 11:36:01am
    Author:  sphy

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player,
                 juce::AudioFormatManager& formatManagerToUse,
                 juce::AudioThumbnailCache& cacheToUse)
:player(_player),waveformdisplay(formatManagerToUse,cacheToUse)
{
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);
    
    volLabel.setText("Vol",juce::NotificationType::dontSendNotification);
    speedLabel.setText("Spe",juce::NotificationType::dontSendNotification);
    posLabel.setText("Pos",juce::NotificationType::dontSendNotification);
    addAndMakeVisible(volLabel);
    addAndMakeVisible(speedLabel);
    addAndMakeVisible(posLabel);
    
    addAndMakeVisible(waveformdisplay);
    
    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    
    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);
    
    volSlider.setRange(0.0,1.0);
    speedSlider.setRange(0.0,100.0);
    posSlider.setRange(0.0,1.0);
    
    startTimer(500);
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
}

void DeckGUI::resized()
{
    double rowH=getHeight()/8;
    int labelWidth = 30;
    int sliderWidth=getWidth()-labelWidth;
    playButton.setBounds(0,0,getWidth(),rowH);
    stopButton.setBounds(0,rowH,getWidth(),rowH);
    volLabel.setBounds(0, rowH * 2, labelWidth, rowH);
    volSlider.setBounds(labelWidth,rowH*2,sliderWidth,rowH);
    speedLabel.setBounds(0, rowH * 3, labelWidth, rowH);
    speedSlider.setBounds(labelWidth,rowH*3,sliderWidth,rowH);
    posLabel.setBounds(0, rowH * 4, labelWidth, rowH);
    posSlider.setBounds(labelWidth,rowH*4,sliderWidth,rowH);
    waveformdisplay.setBounds(0,rowH*5,getWidth(),rowH*2);
    loadButton.setBounds(0,rowH*7,getWidth(),rowH);
}

void DeckGUI::buttonClicked(juce::Button* button){
    if(button==&playButton){
        player->start();
    }
    if(button==&stopButton){
        player->stop();
    }
    if(button==&loadButton){
        auto fileChooserFlags =juce::FileBrowserComponent::canSelectFiles;
        fChooser.launchAsync(fileChooserFlags, [this](const juce::FileChooser& chooser)
            {
                juce::File chosenFile = chooser.getResult();
            player->loadURL(juce::URL{chosenFile});
            waveformdisplay.loadURL(juce::URL{chosenFile});
            });
    }
}

void DeckGUI::sliderValueChanged (juce::Slider* slider){
    if(slider==&volSlider){
        player->setGain(slider->getValue());
    }
    if(slider==&speedSlider){
        player->setSpeed(slider->getValue());
    }
    if(slider==&posSlider){
        player->setPositionRelative(slider->getValue());
    }
}

bool DeckGUI::isInterestedInFileDrag(const juce::StringArray &files){
    std::cout<<"DeckGUI::isInterestedInFileDrag"<<std::endl;
    return true;
}

void DeckGUI::filesDropped(const juce::StringArray &files, int x, int y){
    std::cout<<"DeckGUI::filesDropped"<<std::endl;
    if(files.size()==1){
        player->loadURL(juce::URL{juce::File{files[0]}});
    }
}

void DeckGUI::timerCallback(){
    waveformdisplay.setPositionRelative(player->getPositionRelative());
}
