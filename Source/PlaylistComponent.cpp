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
    addAndMakeVisible(loadButton);
    tableComponent.getHeader().addColumn("", 1, 40);
    tableComponent.getHeader().addColumn("", 2, 40);
    tableComponent.getHeader().addColumn("Track title", 3, 640);
    tableComponent.getHeader().addColumn("", 4, 60);
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
    if(columnId==1){
        if(existingComponentToUpdate==nullptr){
            juce::ToggleButton* btn=new juce::ToggleButton{"L"};
            juce::String id{"L"+std::to_string(rowNumber)};
            btn->setComponentID(id);
            btn->addListener(this);
            existingComponentToUpdate=btn;
        }
    }
    if(columnId==2){
        if(existingComponentToUpdate==nullptr){
            juce::ToggleButton* btn=new juce::ToggleButton{"R"};
            juce::String id{"R"+std::to_string(rowNumber)};
            btn->setComponentID(id);
            btn->addListener(this);
            existingComponentToUpdate=btn;
        }
    }
    if(columnId==4){
        if(existingComponentToUpdate==nullptr){
            juce::TextButton* btn=new juce::TextButton{"delete"};
            juce::String id{"delete"+std::to_string(rowNumber)};
            btn->setComponentID(id);
            btn->addListener(this);
            existingComponentToUpdate=btn;
        }
    }
    return existingComponentToUpdate;
}

void PlaylistComponent::buttonClicked (juce::Button* button){
    if(button==&loadButton){
        auto fileChooserFlags =juce::FileBrowserComponent::canSelectFiles|juce::FileBrowserComponent::openMode;
        fChooser.launchAsync(fileChooserFlags, [this](const juce::FileChooser& chooser)
            {
            juce::Array<juce::File> files = chooser.getResults();
            for (const auto& file : files){
                selectedFiles.push_back(file);
                trackTitles.push_back(file.getFileName().toStdString()); }
            tableComponent.updateContent();
            });
    }else{
        juce::String buttonID = button->getComponentID();
               if (buttonID.startsWith("delete"))
               {
                   int rowNumber = buttonID.substring(6).getIntValue(); // Remove "delete" prefix
                   trackTitles.erase(trackTitles.begin() + rowNumber);
                   tableComponent.updateContent();
               }
             if (buttonID.startsWith("L"))
        {

        }
    }
}


