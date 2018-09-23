#include "500SimpleSend.h"
#include "PluginProcessor.h"
#include "VstGUI.h"

AudioProcessor* JUCE_CALLTYPE createPluginFilter();

//==============================================================================
NewProjectAudioProcessor::NewProjectAudioProcessor()
{  
    mess1 = mess2 = mess3 = mess4 = mess5 = mess6 = mess7 = mess8 = mess9 = mess10 = 0.0f;
    min1 = min2 = min3 = min4 = min5 = min6 = min7 = min8 = min9 = min10 = "0";
    max1 = max2 = max3 = max4 = max5 = max6 = max7 = max8 = max9 = max10 = "127";
    steps1 = steps2 = steps3 = steps4 = steps5 = steps6 = steps7 = steps8 = steps9 = steps10 = "1";
    float message [10] = {0};
    float curMess [10] = {0};
}

NewProjectAudioProcessor::~NewProjectAudioProcessor()
{
}

//==============================================================================
const String NewProjectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int NewProjectAudioProcessor::getNumParameters()
{
    return totalNumParams;
}

float NewProjectAudioProcessor::getParameter (int index)
{
    // This method will be called by the host, probably on the audio thread, so
    // it's absolutely time-critical. Don't use critical sections or anything
    // UI-related, or anything at all that may block in any way!
    switch (index)
    {
        case mess1p:     return mess1;
        case mess2p:     return mess2;
        case mess3p:     return mess3;
        case mess4p:     return mess4;
        case mess5p:     return mess5;
        case mess6p:     return mess6;
        case mess7p:     return mess7;
        case mess8p:     return mess8;
        case mess9p:     return mess9;
        case mess10p:    return mess10;
        default:         return 0.0f;
    }
}

void NewProjectAudioProcessor::setParameter (int index, float newValue)
{
    // This method will be called by the host, probably on the audio thread, so
    // it's absolutely time-critical. Don't use critical sections or anything
    // UI-related, or anything at all that may block in any way!
    switch (index)
    {
        case mess1p:     mess1 = newValue;  break;
        case mess2p:     mess2 = newValue;  break;
        case mess3p:     mess3 = newValue;  break;
        case mess4p:     mess4 = newValue;  break;
        case mess5p:     mess5 = newValue;  break;
        case mess6p:     mess6 = newValue;  break;
        case mess7p:     mess7 = newValue;  break;
        case mess8p:     mess8 = newValue;  break;
        case mess9p:     mess9 = newValue;  break;
        case mess10p:    mess10 = newValue;  break;
        default:         break;
    }
}

const String NewProjectAudioProcessor::getParameterName (int index)
{
    switch (index)
    {
        case mess1p:     return "mess 1";
        case mess2p:     return "mess 2";
        case mess3p:     return "mess 3";
        case mess4p:     return "mess 4";
        case mess5p:     return "mess 5";
        case mess6p:     return "mess 6";
        case mess7p:     return "mess 7";
        case mess8p:     return "mess 8";
        case mess9p:     return "mess 9";
        case mess10p:    return "mess 10";
        default:         break;
    }

    return String::empty;
}

const String NewProjectAudioProcessor::getParameterText (int index)
{
    return String (getParameter (index), 2);
}

const String NewProjectAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String NewProjectAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool NewProjectAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool NewProjectAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool NewProjectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
} 

bool NewProjectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool NewProjectAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

int NewProjectAudioProcessor::getNumPrograms()
{
    return 0;
}

int NewProjectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NewProjectAudioProcessor::setCurrentProgram (int index)
{
}

const String NewProjectAudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void NewProjectAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void NewProjectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void NewProjectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void NewProjectAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    AudioPlayHead::CurrentPositionInfo newTime;

    float messx [] = {mess1, mess2, mess3, mess4, mess5, mess6, mess7, mess8, mess9, mess10};

    String mines [] = {min1, min2, min3, min4, min5, min6, min7, min8, min9, min10};
    String maxes [] = {max1, max2, max3, max4, max5, max6, max7, max8, max9, max10};
    String stepses [] = {steps1, steps2, steps3, steps4, steps5, steps6, steps7, steps8, steps9, steps10};

    std::string ends [] = {end1.toUTF8(), end2.toUTF8(), end3.toUTF8(), end4.toUTF8(), end5.toUTF8(), end6.toUTF8(), end7.toUTF8(), end8.toUTF8(), end9.toUTF8(), end10.toUTF8()};
    std::string s (startUrlText.toUTF8 ());
    int Port (portVal.getIntValue ());

if(!Port){
    Port = 7000;
}

for (int i = 0; i < 10; ++i)
{
    message[i] = mines[i].getFloatValue() + messx[i] * (maxes[i].getFloatValue() - mines[i].getFloatValue());
    message[i] = floor(message[i]/stepses[i].getFloatValue()) * stepses[i].getFloatValue();

    if(message[i] != curMess[i] ){
        testConnection = new osc500();
        testConnection->testOSC(i, s, ends[i], message[i], Port);
        curMess[i] = message[i];
        delete testConnection;
    }
}

}

//==============================================================================
bool NewProjectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* NewProjectAudioProcessor::createEditor()
{
     return new MainComponent (this);
}

//==============================================================================
void NewProjectAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
      XmlElement xml ("MYPLUGINSETTINGS");

    // add some attributes to it..

    xml.setAttribute ("startUrl", startUrlText);
    xml.setAttribute ("portVal", portVal);
    xml.setAttribute ("destinationVal", destinationVal);
    xml.setAttribute ("1", mess1);
    xml.setAttribute ("2", mess2);
    xml.setAttribute ("3", mess3);
    xml.setAttribute ("4", mess4);
    xml.setAttribute ("5", mess5);
    xml.setAttribute ("6", mess6);
    xml.setAttribute ("7", mess7);
    xml.setAttribute ("8", mess8);
    xml.setAttribute ("9", mess9);
    xml.setAttribute ("10", mess10);

    xml.setAttribute ("end1", end1);
    xml.setAttribute ("end2", end2);
    xml.setAttribute ("end3", end3);
    xml.setAttribute ("end4", end4);
    xml.setAttribute ("end5", end5);
    xml.setAttribute ("end6", end6);
    xml.setAttribute ("end7", end7);
    xml.setAttribute ("end8", end8);
    xml.setAttribute ("end9", end9);
    xml.setAttribute ("end10", end10);

    xml.setAttribute ("min1", min1);
    xml.setAttribute ("min2", min2);
    xml.setAttribute ("min3", min3);
    xml.setAttribute ("min4", min4);
    xml.setAttribute ("min5", min5);
    xml.setAttribute ("min6", min6);
    xml.setAttribute ("min7", min7);
    xml.setAttribute ("min8", min8);
    xml.setAttribute ("min9", min9);
    xml.setAttribute ("min10", min10);

    xml.setAttribute ("max1", max1);
    xml.setAttribute ("max2", max2);
    xml.setAttribute ("max3", max3);
    xml.setAttribute ("max4", max4);
    xml.setAttribute ("max5", max5);
    xml.setAttribute ("max6", max6);
    xml.setAttribute ("max7", max7);
    xml.setAttribute ("max8", max8);
    xml.setAttribute ("max9", max9);
    xml.setAttribute ("max10", max10);

    xml.setAttribute ("steps1", steps1);
    xml.setAttribute ("steps2", steps2);
    xml.setAttribute ("steps3", steps3);
    xml.setAttribute ("steps4", steps4);
    xml.setAttribute ("steps5", steps5);
    xml.setAttribute ("steps6", steps6);
    xml.setAttribute ("steps7", steps7);
    xml.setAttribute ("steps8", steps8);
    xml.setAttribute ("steps9", steps9);
    xml.setAttribute ("steps10", steps10);

    // then use this helper function to stuff it into the binary blob and return it..
    copyXmlToBinary (xml, destData);
}

void NewProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
       ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState != nullptr)
    {
        // make sure that it's actually our type of XML object..
        if (xmlState->hasTagName ("MYPLUGINSETTINGS"))
        {
            // ok, now pull out our parameters..
            startUrlText = xmlState->getStringAttribute ("startUrl", startUrlText);
            portVal = xmlState->getStringAttribute ("portVal", portVal);
            destinationVal = xmlState->getStringAttribute ("destinationVal", destinationVal);

            end1 = xmlState->getStringAttribute ("end1", end1);
            end2 = xmlState->getStringAttribute ("end2", end2);
            end3 = xmlState->getStringAttribute ("end3", end3);
            end4 = xmlState->getStringAttribute ("end4", end4);
            end5 = xmlState->getStringAttribute ("end5", end5);
            end6 = xmlState->getStringAttribute ("end6", end6);
            end7 = xmlState->getStringAttribute ("end7", end7);
            end8 = xmlState->getStringAttribute ("end8", end8);
            end9 = xmlState->getStringAttribute ("end9", end9);
            end10 = xmlState->getStringAttribute ("end10", end10);
            
            mess1  = xmlState->getDoubleAttribute ("1", mess1);
            mess2  = xmlState->getDoubleAttribute ("2", mess2);
            mess3  = xmlState->getDoubleAttribute ("3", mess3);
            mess4  = xmlState->getDoubleAttribute ("4", mess4);
            mess5  = xmlState->getDoubleAttribute ("5", mess5);
            mess6  = xmlState->getDoubleAttribute ("6", mess6);
            mess7  = xmlState->getDoubleAttribute ("7", mess7);
            mess8  = xmlState->getDoubleAttribute ("8", mess8);
            mess9  = xmlState->getDoubleAttribute ("9", mess9);
            mess10  = xmlState->getDoubleAttribute ("10", mess10);

            min1  = xmlState->getStringAttribute ("min1", min1);
            min2  = xmlState->getStringAttribute ("min2", min2);
            min3  = xmlState->getStringAttribute ("min3", min3);
            min4  = xmlState->getStringAttribute ("min4", min4);
            min5  = xmlState->getStringAttribute ("min5", min5);
            min6  = xmlState->getStringAttribute ("min6", min6);
            min7  = xmlState->getStringAttribute ("min7", min7);
            min8  = xmlState->getStringAttribute ("min8", min8);
            min9  = xmlState->getStringAttribute ("min9", min9);
            min10  = xmlState->getStringAttribute ("min10", min10);

            max1  = xmlState->getStringAttribute ("max1", max1);
            max2  = xmlState->getStringAttribute ("max2", max2);
            max3  = xmlState->getStringAttribute ("max3", max3);
            max4  = xmlState->getStringAttribute ("max4", max4);
            max5  = xmlState->getStringAttribute ("max5", max5);
            max6  = xmlState->getStringAttribute ("max6", max6);
            max7  = xmlState->getStringAttribute ("max7", max7);
            max8  = xmlState->getStringAttribute ("max8", max8);
            max9  = xmlState->getStringAttribute ("max9", max9);
            max10  = xmlState->getStringAttribute ("max10", max10);

            steps1  = xmlState->getStringAttribute ("steps1", steps1);
            steps2  = xmlState->getStringAttribute ("steps2", steps2);
            steps3  = xmlState->getStringAttribute ("steps3", steps3);
            steps4  = xmlState->getStringAttribute ("steps4", steps4);
            steps5  = xmlState->getStringAttribute ("steps5", steps5);
            steps6  = xmlState->getStringAttribute ("steps6", steps6);
            steps7  = xmlState->getStringAttribute ("steps7", steps7);
            steps8  = xmlState->getStringAttribute ("steps8", steps8);
            steps9  = xmlState->getStringAttribute ("steps9", steps9);
            steps10  = xmlState->getStringAttribute ("steps10", steps10);
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NewProjectAudioProcessor();
}
