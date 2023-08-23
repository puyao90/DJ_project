/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 19 Aug 2023 8:40:42pm
    Author:  sphy

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"

//==============================================================================
PlaylistComponent::PlaylistComponent()
{
//    trackTitles.push_back("Track 1");
//    trackTitles.push_back("Track 2");
//    trackTitles.push_back("Track 3");
//    trackTitles.push_back("Track 4");
//    trackTitles.push_back("Track 5");
//    trackTitles.push_back("Track 6");
    
    addAndMakeVisible(loadButton);
    
    tableComponent.getHeader().addColumn("Track title", 1, 400);
    tableComponent.getHeader().addColumn("", 2, 200);
    tableComponent.setModel(this);
    
    addAndMakeVisible(tableComponent);
    loadButton.addListener(this);
}

PlaylistComponent::~PlaylistComponent()
{tableComponent.setModel(nullptr);
}

void PlaylistComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("PlaylistComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void PlaylistComponent::resized()
{
    loadButton.setBounds(getWidth()-120,0,120,30);
    tableComponent.setBounds(0, 30, getWidth(), getHeight()-30);
}

int PlaylistComponent::getNumRows(){
    return trackTitles.size();
}

void PlaylistComponent::paintRowBackground (juce::Graphics & g, int rowNumber, int width, int height, bool rowIsSelected){
    if(rowIsSelected){
        g.fillAll(juce::Colours::orange);
    }else{
        g.fillAll(juce::Colours::darkgrey);
    }
}

void PlaylistComponent::paintCell (juce::Graphics & g, int rowNumber, int columnId, int width, int height, bool rowIsSelected){
    g.drawText(trackTitles[rowNumber], 2, 0, width-4, height, juce::Justification::centredLeft);
}

juce::Component* PlaylistComponent::refreshComponentForCell (int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate){
    if(columnId==2){
        if(existingComponentToUpdate==nullptr){
            juce::TextButton* btn=new juce::TextButton{"play"};
            juce::String id{std::to_string(rowNumber)};
            btn->setComponentID(id);
            btn->addListener(this);
            existingComponentToUpdate=btn;
        }
    }
    return existingComponentToUpdate;
}

void PlaylistComponent::buttonClicked (juce::Button* button){
    if(button==&loadButton){
        auto fileChooserFlags =juce::FileBrowserComponent::canSelectFiles;
        fChooser.launchAsync(fileChooserFlags, [this](const juce::FileChooser& chooser)
            {
                juce::File chosenFile = chooser.getResult();
//            player->loadURL(juce::URL{chosenFile});
//            waveformdisplay.loadURL(juce::URL{chosenFile});
            });
    }
    int rowNumber = button->getComponentID().getIntValue();
        std::cout << "PlaylistComponent::buttonClicked:" << trackTitles[rowNumber] << std::endl;
}


