/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include "PluginProcessor.h"
#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_events/juce_events.h"
#include "juce_gui_basics/juce_gui_basics.h"

struct CustomRotarySlider : juce::Slider{
    CustomRotarySlider(): juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, juce::Slider::TextEntryBoxPosition::NoTextBox){
      
    }

};

struct ResponseCurveComponent: juce::Component,
juce::AudioProcessorParameter::Listener,
juce::Timer
{
    ResponseCurveComponent(SimpleEQAudioProcessor&);
    ~ResponseCurveComponent();

    
    void parameterValueChanged (int parameterIndex, float newValue) override;
    void parameterGestureChanged (int parameterIndex, bool gestureIsStarting) override{}
    void timerCallback() override;

    void paint(juce::Graphics& g) override;
private:
    SimpleEQAudioProcessor& audioProcessor;
    juce::Atomic<bool> parametersChanged {false};

    MonoChain monoChain;
};

//==============================================================================
/**
*/
class SimpleEQAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SimpleEQAudioProcessorEditor (SimpleEQAudioProcessor&);
    ~SimpleEQAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SimpleEQAudioProcessor& audioProcessor;

    CustomRotarySlider peakFreqSlider,
        peakGainSlider,
        peakQualitySlider,
        lowCutFreqSlider,
        highCutFreqSlider,
        lowCutSlopeSlider,
        highCutSlopeSlider;

    ResponseCurveComponent responseCurveComponent;
    
    
    // Juce tiene una clase para conectar los sliders a los parametros pero es muy largo
    // el nombre y aqui lo mapeamos a algo mas sencillo

    using APVTS = juce::AudioProcessorValueTreeState;
    using Attachment = APVTS::SliderAttachment;

    Attachment peakFreqSliderAttachment,
        peakGainSliderAttachment,
        peakQualitySliderAttachment,
        lowCutFreqSliderAttachment,
        highCutFreqSliderAttachment,
        lowCutSlopeSliderAttachment,
        highCutSlopeSliderAttachment;

    // Creo un vector para todos estos sliders para poder iterar sobre ellos.
    std::vector<juce::Component*> getComps();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleEQAudioProcessorEditor)
};
