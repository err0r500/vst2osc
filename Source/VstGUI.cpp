#include "PluginProcessor.h"
#include "VstGUI.h"
#include "500SimpleSend.h"

Controller::Controller (int identifier, Slider::Listener* mainListener, TextEditor::Listener* mainTextListener)
  : boxLabel(0), contSlider(0), contLabel(0), finalUrl(0), minVal(0), maxVal(0), stepsVal(0)
{ 
  addAndMakeVisible(boxLabel = new Label (String::empty, String(identifier+1)));
  boxLabel->setFont(Font (20.0000f));
  boxLabel->setJustificationType(36);

  addAndMakeVisible(contSlider = new Slider(String(identifier+1))); 
  contSlider->setSliderStyle(Rotary);
  contSlider->setTextBoxStyle(NoTextBox, true, 0, 0);

  contSlider->setRange (0, 127, 1);
  contSlider->addListener(this); 
  contSlider->addListener(mainListener); 

  addAndMakeVisible(contLabel = new Label());
  
  addAndMakeVisible(finalUrl = new TextEditor()); 
  finalUrl->setTextToShowWhenEmpty("end of pattern", Colours::lightskyblue);
  finalUrl->addListener(this);
  finalUrl->addListener(mainTextListener); 
  finalUrl->setWantsKeyboardFocus (true);
  
  addAndMakeVisible (minVal = new TextEditor ());
  minVal->setTextToShowWhenEmpty("min", Colours::lightskyblue);
  minVal->setInputRestrictions(5,"0123456789.");
  minVal->addListener(this);
  minVal->addListener(mainTextListener); 

  addAndMakeVisible (maxVal = new TextEditor ());
  maxVal->setTextToShowWhenEmpty("max", Colours::lightskyblue);
  maxVal->setInputRestrictions(5,"0123456789.");
  maxVal->addListener(this);
  maxVal->addListener(mainTextListener); 

  addAndMakeVisible (stepsVal = new TextEditor ());
  stepsVal->setTextToShowWhenEmpty("steps", Colours::lightskyblue);
  stepsVal->setInputRestrictions(5,"0123456789.");
  stepsVal->addListener(this);
  stepsVal->addListener(mainTextListener); 
}

Controller::~Controller ()
{
  deleteAndZero (stepsVal);
  deleteAndZero (maxVal);
  deleteAndZero (minVal);
  deleteAndZero (finalUrl);
  deleteAndZero (contSlider);
  deleteAndZero (contLabel);
  deleteAndZero (boxLabel);
}

void Controller::sliderValueChanged(Slider* slider){
  contLabel->setText(contSlider->getTextFromValue(contSlider->getValue()), false);
};

void Controller::textEditorTextChanged(TextEditor& editor){
  if(&editor != finalUrl){
      contSlider->setRange(
        minVal->getText().getDoubleValue(), 
        maxVal->getText().getDoubleValue(), 
        stepsVal->getText().getDoubleValue()
      );
    }
};


void Controller::paint (Graphics& g)
{ 
  g.setColour(Colours::white);
  g.fillRoundedRectangle(0.0, 0.0, 280.0, 42.0, 4.0);
}

void Controller::resized()
{
  boxLabel->setBounds (-2, 0, 25, 40);
  contSlider->setBounds (20, 2, 40, 40);
  finalUrl->setBounds (62, 1, 209, 19);

  contLabel->setBounds (62, 21, 50, 19);
  minVal->setBounds (115, 21, 50, 19);
  maxVal->setBounds (168, 21, 50, 19);
  stepsVal->setBounds (221, 21, 50, 19);
}





















MainComponent::MainComponent (NewProjectAudioProcessor* ownerFilter)
    : AudioProcessorEditor (ownerFilter), controllerBox(0), 
    portText(0), destinationText(0), startUrl(0), titre(0), siteURL(0)
{
  for(int i=0;i<10;i++){
    controllerBox.push_back(new Controller(i, this, this));
    addAndMakeVisible(controllerBox[i]);
    controllerBox[i]->setWantsKeyboardFocus (true);
  }

  addAndMakeVisible(destinationText = new TextEditor()); 
  destinationText->setTextToShowWhenEmpty("destination IP", Colours::lightskyblue);
  destinationText->setInputRestrictions(15,"0123456789.");
  destinationText->addListener(this);
  destinationText->setText(ownerFilter->destinationVal);
  
  addAndMakeVisible(portText = new TextEditor()); 
  portText->setTextToShowWhenEmpty("port", Colours::lightskyblue);
  portText->setInputRestrictions(5,"0123456789");
  portText->addListener(this);
  portText->setText(ownerFilter->portVal);

  addAndMakeVisible(startUrl = new TextEditor()); 
  startUrl->setTextToShowWhenEmpty("main pattern", Colours::lightskyblue);
  startUrl->addListener(this);
  startUrl->setText(ownerFilter->startUrlText);

  addAndMakeVisible(titre = new Label(String::empty, "VST to OSC \nby Err0r_500")); 
  titre->setFont(Font (20.0));
  titre->setColour(Label::textColourId, Colours::white);
  titre->setJustificationType(2);

  addAndMakeVisible(siteURL = new Label(String::empty, "http://peter1island.com")); 
  siteURL->setFont(Font (15.0));
  siteURL->setColour(Label::textColourId, Colours::white);
  siteURL->setJustificationType(2);

    String endText [] = {ownerFilter->end1, ownerFilter->end2, ownerFilter->end3,
  ownerFilter->end4, ownerFilter->end5, ownerFilter->end6,
  ownerFilter->end7, ownerFilter->end8, ownerFilter->end9,
  ownerFilter->end10};

 String minText [] = {ownerFilter->min1, ownerFilter->min2, ownerFilter->min3,
    ownerFilter->min4, ownerFilter->min5, ownerFilter->min6,
    ownerFilter->min7, ownerFilter->min8, ownerFilter->min9,
    ownerFilter->min10};

String maxText [] = {ownerFilter->max1, ownerFilter->max2, ownerFilter->max3,
    ownerFilter->max4, ownerFilter->max5, ownerFilter->max6,
    ownerFilter->max7, ownerFilter->max8, ownerFilter->max9,
    ownerFilter->max10};   

String stepsText [] = {ownerFilter->steps1, ownerFilter->steps2, ownerFilter->steps3,
    ownerFilter->steps4, ownerFilter->steps5, ownerFilter->steps6,
    ownerFilter->steps7, ownerFilter->steps8, ownerFilter->steps9,
    ownerFilter->steps10}; 

for (int i = 0; i < 10; ++i)
{
  controllerBox[i]->finalUrl->setText(endText[i]);
  
  if(minText[i] != "0"){
    controllerBox[i]->minVal->setText(minText[i]);
  }
  if(maxText[i] != "127"){
    controllerBox[i]->maxVal->setText(maxText[i]);
  }
  if(stepsText[i] != "1"){
    controllerBox[i]->stepsVal->setText(stepsText[i]);
  }
}

  setSize (600, 300);
  startTimer (20);
}

MainComponent::~MainComponent()
{
  for(int i=0; i<10; i++){
  deleteAndZero(controllerBox[i]);
  }

  deleteAndZero(titre); 
  deleteAndZero(siteURL);
  deleteAndZero(portText);
  deleteAndZero(destinationText);
  deleteAndZero(startUrl);
  
}

void MainComponent::paint (Graphics& mygraph)
{
  mygraph.fillAll (Colour::Colour(rand() % 100, rand() % 100, rand() % 100));
}

void MainComponent::resized()
{
  destinationText->setBounds (10, 15, 100, 25);
  portText->setBounds (240, 15, 50, 25);
  startUrl->setBounds (10, 45, 280, 25);
  titre->setBounds (300, 5, 290, 65);
  siteURL->setBounds (300, 45, 290, 25);
  
  for(unsigned int i=0; i<controllerBox.size(); i++){ 
    if(i<5){controllerBox[i]->setBounds (10, 44*i + 80, 280, 43);}
    else{controllerBox[i]->setBounds (310, 44*i - 140, 280, 43);}
  }
}

void MainComponent::timerCallback()
{
  NewProjectAudioProcessor* ourProcessor = getProcessor();
  AudioPlayHead::CurrentPositionInfo newPos (ourProcessor->lastPosInfo);

 if (lastDisplayedPosition != newPos){
     for (int i = 0; i < 10; ++i)
    {
        controllerBox[i]->contSlider->setValue (ourProcessor->message[i]);
    }
  }
}


void MainComponent::sliderValueChanged (Slider* slider2)
{ 
        // It's vital to use setParameterNotifyingHost to change any parameters that are automatable
        // by the host, rather than just modifying them directly, otherwise the host won't know
        // that they've changed.
  int dest [] = {NewProjectAudioProcessor::mess1p, NewProjectAudioProcessor::mess2p, NewProjectAudioProcessor::mess3p,
                NewProjectAudioProcessor::mess4p, NewProjectAudioProcessor::mess5p, NewProjectAudioProcessor::mess6p,
                NewProjectAudioProcessor::mess7p, NewProjectAudioProcessor::mess8p, NewProjectAudioProcessor::mess9p,
                NewProjectAudioProcessor::mess10p};

  for (int i = 0; i < 10; ++i)
  {
    if (slider2 == controllerBox[i]->contSlider){
       getProcessor()->setParameterNotifyingHost (dest[i],
        (float) (controllerBox[i]->contSlider->getValue() - controllerBox[i]->contSlider->getMinimum()) / 
        (controllerBox[i]->contSlider->getMaximum() - controllerBox[i]->contSlider->getMinimum()));
    break;
    }
  };
}

void MainComponent::textEditorTextChanged(TextEditor& editor2)
{ 

NewProjectAudioProcessor* ourProcessor = getProcessor();

  if (&editor2 == startUrl){
    getProcessor()->startUrlText = startUrl->getText();
    params::setBegOfMess(startUrl->getText());

    for(int i=0; i<10; i++){ 
    params::setEndOfMess(i, controllerBox[i]->finalUrl->getText());
    }
  }
    
  else if(&editor2 == portText){
    getProcessor()->portVal = portText->getText();
    std::string porttemp = portText->getText().toUTF8 ();
    params::setPort(atoi(porttemp.c_str()));
  }
  else if(&editor2 == destinationText){
    getProcessor()->destinationVal = destinationText->getText();
    params::setDest(destinationText->getText());
  }

  else{
    String *ends [] = {&ourProcessor->end1, &ourProcessor->end2, &ourProcessor->end3,
  &ourProcessor->end4, &ourProcessor->end5, &ourProcessor->end6,
  &ourProcessor->end7, &ourProcessor->end8, &ourProcessor->end9,
  &ourProcessor->end10};

    String *mines [] = {&ourProcessor->min1, &ourProcessor->min2, &ourProcessor->min3,
  &ourProcessor->min4, &ourProcessor->min5, &ourProcessor->min6,
  &ourProcessor->min7, &ourProcessor->min8, &ourProcessor->min9,
  &ourProcessor->min10};

    String *maxes [] = {&ourProcessor->max1, &ourProcessor->max2, &ourProcessor->max3,
  &ourProcessor->max4, &ourProcessor->max5, &ourProcessor->max6,
  &ourProcessor->max7, &ourProcessor->max8, &ourProcessor->max9,
  &ourProcessor->max10};


    String *stepses [] = {&ourProcessor->steps1, &ourProcessor->steps2, &ourProcessor->steps3,
  &ourProcessor->steps4, &ourProcessor->steps5, &ourProcessor->steps6,
  &ourProcessor->steps7, &ourProcessor->steps8, &ourProcessor->steps9,
  &ourProcessor->steps10};

      for (int i = 0; i < 10; ++i)
    {
      if(&editor2 == controllerBox[i]->finalUrl){
      *ends[i] = controllerBox[i]->finalUrl->getText();
       params::setEndOfMess(i, controllerBox[i]->finalUrl->getText());
      }
      if(&editor2 == controllerBox[i]->minVal){
      *mines[i] = controllerBox[i]->minVal->getText();
      }
       if(&editor2 == controllerBox[i]->maxVal){
      *maxes[i] = controllerBox[i]->maxVal->getText();
      }

      if(&editor2 == controllerBox[i]->stepsVal){
      *stepses[i] = controllerBox[i]->stepsVal->getText();
      }

    }
  }
}

