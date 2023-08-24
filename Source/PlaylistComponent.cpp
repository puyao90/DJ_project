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
PlaylistComponent::PlaylistComponent(DeckGUI* _leftGui, DeckGUI* _rightGui):
    leftGui(_leftGui),rightGui(_rightGui),selectedLeftRowIdx(-1),selectedRightRowIdx(-1)
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
        } else {
            juce::ToggleButton* toggleButton = dynamic_cast<juce::ToggleButton*>(existingComponentToUpdate);
            if (rowNumber != selectedLeftRowIdx){
                {
                    toggleButton->setToggleState(false, juce::NotificationType::sendNotification);
                }
            } else {
                toggleButton->setToggleState(true, juce::NotificationType::sendNotification);
            }
        }
    }
    if(columnId==2){
        if(existingComponentToUpdate==nullptr){
            juce::ToggleButton* btn=new juce::ToggleButton{"R"};
            juce::String id{"R"+std::to_string(rowNumber)};
            btn->setComponentID(id);
            btn->addListener(this);
            existingComponentToUpdate=btn;
        }else{
            juce::ToggleButton* toggleButton = dynamic_cast<juce::ToggleButton*>(existingComponentToUpdate);
            if (rowNumber != selectedRightRowIdx){
                {
                    toggleButton->setToggleState(false, juce::NotificationType::sendNotification);
                }
            }else {
                toggleButton->setToggleState(true, juce::NotificationType::sendNotification);
            }
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
        auto fileChooserFlags =juce::FileBrowserComponent::canSelectFiles|juce::FileBrowserComponent::openMode|juce::FileBrowserComponent::canSelectMultipleItems;
        fileChooser.launchAsync(fileChooserFlags, [this](const juce::FileChooser& chooser)
            {
            juce::Array<juce::File> files = chooser.getResults();
            for (const auto& file : files){
                loadedFiles.push_back(file);
                trackTitles.push_back(file.getFileName().toStdString()); }
            tableComponent.updateContent();
            });
    }else{
        juce::String buttonID = button->getComponentID();
            if (buttonID.startsWith("delete"))
               {
                   int rowNumber = buttonID.substring(6).getIntValue(); // Remove "delete" prefix
                   trackTitles.erase(trackTitles.begin() + rowNumber);
                   if(selectedLeftRowIdx == rowNumber){
                       selectedLeftRowIdx = -1;
                       leftGui -> clearWaveDisplay();

                   }
                   if (selectedRightRowIdx == rowNumber) {
                       selectedRightRowIdx = -1;
                       rightGui -> clearWaveDisplay();
                   }
                   if(rowNumber < selectedLeftRowIdx){
                       selectedLeftRowIdx -= 1;
                   }
                   if(rowNumber < selectedRightRowIdx){
                       selectedRightRowIdx -= 1;
                   }
                   tableComponent.updateContent();
               }
            if (buttonID.startsWith("L")){
                if (button -> getToggleState())
                {
                    selectedLeftRowIdx = buttonID.substring(1).getIntValue();
                    tableComponent.updateContent();
                    leftGui -> addToMyGui(loadedFiles[selectedLeftRowIdx]);
                }else{
                    leftGui -> clearWaveDisplay();
                }}
            if (buttonID.startsWith("R")){
                if (button -> getToggleState()){
                selectedRightRowIdx = buttonID.substring(1).getIntValue();
                tableComponent.updateContent();
                rightGui -> addToMyGui(loadedFiles[selectedRightRowIdx]);
                }else{
                rightGui -> clearWaveDisplay();
                }
            }
    }
}


