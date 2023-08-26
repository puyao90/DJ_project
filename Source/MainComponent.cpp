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
    addAndMakeVisible(waveformL);
    addAndMakeVisible(waveformR);
    addAndMakeVisible(deckGUI1);
    addAndMakeVisible(deckGUI2);
    addAndMakeVisible(playlistComponent);
    
    formatManager.registerBasicFormats();
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    playerL.prepareToPlay(samplesPerBlockExpected, sampleRate);
    playerR.prepareToPlay(samplesPerBlockExpected, sampleRate);
    
    mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    mixerSource.addInputSource(&playerL, false);
    mixerSource.addInputSource(&playerR, false);
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    mixerSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    playerL.releaseResources();
    playerR.releaseResources();
    mixerSource.releaseResources();
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
                      
}

void MainComponent::resized()
{
    double rowH=getHeight()/9;
    waveformL.setBounds(0, 0,getWidth(),rowH);
    waveformR.setBounds(0, rowH,getWidth(),rowH);
    deckGUI1.setBounds(0,rowH*2,getWidth()/2,rowH*3);
    deckGUI2.setBounds(getWidth()/2,rowH*2,getWidth()/2,rowH*3);
    
    playlistComponent.setBounds(0,rowH*5,getWidth(),rowH*4);
}

std::unique_ptr<juce::FileChooser> myChooser;
