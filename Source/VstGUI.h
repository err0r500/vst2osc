#ifndef __PLUGINEDITOR_H_1FBDBAFA__
#define __PLUGINEDITOR_H_1FBDBAFA__

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "500SimpleSend.h"

class Controller  : public Slider, 
                    public SliderListener, 
                    public TextEditor::Listener,
                    public osc500
{
public:
    Controller (int identifier, Slider::Listener* mainListener, TextEditor::Listener* mainTextListener);
    ~Controller();
    void paint (Graphics& g);
    void resized();
    void sliderValueChanged(Slider* slider);
    void textEditorTextChanged(TextEditor& editor); 

    TextEditor* finalUrl, *minVal, *maxVal, *stepsVal; 
    Slider* contSlider;
    osc500* oscConnection; 

private:
    Label* boxLabel, *contLabel;    
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Controller);
};













class MainComponent  :  public AudioProcessorEditor, 
                        public Timer, 
                        public TextEditor::Listener,
                        public SliderListener

{
public:
    MainComponent (NewProjectAudioProcessor* ownerFilter);
    ~MainComponent();
    void timerCallback();
    void paint (Graphics& mygraph);
    void resized();
    void sliderValueChanged (Slider* slider2);
    void textEditorTextChanged(TextEditor& editor2);  
    
private:
    std::vector<Controller*> controllerBox;
    Label* titre, *siteURL;
    TextEditor *portText, *destinationText, *startUrl;
    
    AudioPlayHead::CurrentPositionInfo lastDisplayedPosition;

    NewProjectAudioProcessor* getProcessor() const
    {
        return static_cast <NewProjectAudioProcessor*> (getAudioProcessor());
    };
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent);
};




#endif  // __PLUGINEDITOR_H_1FBDBAFA__
















