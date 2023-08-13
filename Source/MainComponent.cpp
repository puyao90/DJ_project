#include "MainComponent.h"

//==============================================================================

MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        setAudioChannels (0, 2);
    }
    addAndMakeVisible(deckGUI1);
    addAndMakeVisible(deckGUI2);
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    player1.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    player1.releaseResources();
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
                      
}

void MainComponent::resized()
{
    deckGUI1.setBounds(0,0,getWidth()/2,getHeight());
    deckGUI2.setBounds(getWidth()/2,0,getWidth()/2,getHeight());
}

std::unique_ptr<juce::FileChooser> myChooser;


void MainComponent::buttonClicked(juce::Button* button){
//    if(button==&playButton){
//        player1.start();
//    }
//    if(button==&stopButton){
//        player1.stop();
//    }
//    if(button==&loadButton){
//        auto fileChooserFlags =juce::FileBrowserComponent::canSelectFiles;
//        fChooser.launchAsync(fileChooserFlags, [this](const juce::FileChooser& chooser)
//            {
//                juce::File chosenFile = chooser.getResult();
//                player1.loadURL(juce::URL{chosenFile});
//            });
//    }
}

void MainComponent::sliderValueChanged (juce::Slider* slider){
//    if(slider==&volSlider){
//        player1.setGain(slider->getValue());
//    }
//    if(slider==&speedSlider){
//        player1.setSpeed(slider->getValue());
//    }
//    if(slider==&posSlider){
//        player1.setPositionRelative(slider->getValue());
//    }
}
