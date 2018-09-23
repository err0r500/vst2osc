#ifndef __PLUGINPROCESSOR_H_A27E659__
#define __PLUGINPROCESSOR_H_A27E659__

#include "../JuceLibraryCode/JuceHeader.h"
#include "500SimpleSend.h"

class NewProjectAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    NewProjectAudioProcessor();
    ~NewProjectAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();

    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);

    //==============================================================================
    AudioProcessorEditor* createEditor();
    bool hasEditor() const;

    //==============================================================================
    const String getName() const;

    int getNumParameters();

    float getParameter (int index);
    void setParameter (int index, float newValue);

    const String getParameterName (int index);
    const String getParameterText (int index);

    const String getInputChannelName (int channelIndex) const;
    const String getOutputChannelName (int channelIndex) const;
    bool isInputChannelStereoPair (int index) const;
    bool isOutputChannelStereoPair (int index) const;

    bool acceptsMidi() const;
    bool producesMidi() const;
    bool silenceInProducesSilenceOut() const;

    //==============================================================================
    int getNumPrograms();
    int getCurrentProgram();
    void setCurrentProgram (int index);
    const String getProgramName (int index);
    void changeProgramName (int index, const String& newName);

    //==============================================================================
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);

    AudioPlayHead::CurrentPositionInfo lastPosInfo;
    
    enum Parameters
    {
        mess1p = 0,
        mess2p,  
        mess3p,
        mess4p,
        mess5p,
        mess6p,
        mess7p,  
        mess8p,
        mess9p,
        mess10p,
 
        totalNumParams 
    };

    float   mess1, mess2, mess3, mess4, mess5, mess6, mess7, mess8, mess9, mess10;
    float   curMess [10];
    float   message [10];
    std::string  ends [10];

    String  startUrlText, portVal, destinationVal, 
    end1, end2, end3, end4, end5, end6, end7, end8, end9, end10,
    min1, min2, min3, min4, min5, min6, min7, min8, min9, min10,
    max1, max2, max3, max4, max5, max6, max7, max8, max9, max10,
    steps1, steps2, steps3, steps4, steps5, steps6, steps7, steps8, steps9, steps10;

    osc500* testConnection; 

private:
   // JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewProjectAudioProcessor);
};

#endif  // __PLUGINPROCESSOR_H_A27E659__
