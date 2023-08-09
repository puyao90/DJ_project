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
        // Specify the number of input and output channels that we want to open
        setAudioChannels (0, 2);
    }
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    
    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    volSlider.addListener(this);
    speedSlider.addListener(this);
    
    volSlider.setRange(0.0, 1.0);

}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

//    phase=0.0;
//    dphase=0.0001;
    
    formatManager.registerBasicFormats();
    transportSource.prepareToPlay(samplesPerBlockExpected,sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected,sampleRate);
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{// Your audio-processing code goes here!
    
//    auto *leftChan=bufferToFill.buffer->getWritePointer(0,bufferToFill.startSample);
//    auto *rightChan=bufferToFill.buffer->getWritePointer(0,bufferToFill.startSample);
//    for(auto i=0;i<bufferToFill.numSamples;++i){
//        double sample=rand.nextDouble()*0.25;
//        double sample=fmod(phase,0.2);
//        double sample=sin(phase)*0.1;
//        leftChan[i]=sample;
//        rightChan[i]=sample;
//        phase+=dphase;
//    }
    
    resampleSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    transportSource.releaseResources();
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
//    g.setFont (20.0f);
//    g.drawText ("Hello from London", getLocalBounds(),
//                 juce::Justification::centred, true);
                      
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    double rowH=getHeight()/5;
    playButton.setBounds(0,0,getWidth(),rowH);
    stopButton.setBounds(0,rowH,getWidth(),rowH);
    volSlider.setBounds(0,rowH*2,getWidth(),rowH);
    speedSlider.setBounds(0,rowH*3,getWidth(),rowH);
    loadButton.setBounds(0,rowH*4,getWidth(),rowH);
}

std::unique_ptr<juce::FileChooser> myChooser;


void MainComponent::buttonClicked(juce::Button *button){
    if(button==&playButton){
        transportSource.start();
    }
    if(button==&stopButton){
        transportSource.stop();
    }
    if(button==&loadButton){
        auto fileChooserFlags =juce::FileBrowserComponent::canSelectFiles;
        fChooser.launchAsync(fileChooserFlags, [this](const juce::FileChooser& chooser)
            {
                juce::File chosenFile = chooser.getResult();
                loadURL(juce::URL{chosenFile});
            });
    }
    
}

void MainComponent::sliderValueChanged (juce::Slider *slider){
    if(slider==&volSlider){
//        std::cout<<"volSlider moved"<<slider->getValue()<<std::endl;
//        dphase=volSlider.getValue()*0.01;
        transportSource.setGain(slider->getValue());
    }
    if(slider==&speedSlider){
        resampleSource.setResamplingRatio(slider->getValue());
    }
}

void MainComponent::loadURL(juce::URL audioURL){
    auto *reader=formatManager.createReaderFor(audioURL.createInputStream(false));
    if(reader !=nullptr){
        std::unique_ptr<juce::AudioFormatReaderSource> newSource (new juce::AudioFormatReaderSource(reader,true));
        transportSource.setSource(newSource.get(),0,nullptr,reader->sampleRate);
        readerSource.reset(newSource.release());
    }
}
