/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"


struct CustomRotarySlider : juce::Slider
{
	CustomRotarySlider() : juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, 
                                        juce::Slider::TextEntryBoxPosition::NoTextBox)
	{

	}
};
//==============================================================================
/**
*/
class SimpleEQAudioProcessorEditor : public juce::AudioProcessorEditor,  // << ADD COMMA HERE
    juce::AudioProcessorParameter::Listener,
    juce::Timer
{
public:
    SimpleEQAudioProcessorEditor (SimpleEQAudioProcessor&);
    ~SimpleEQAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

	void parameterValueChanged(int parameterIndex, float newValue) override;
    
    /* indicates that a parameter change gesture has started  */

	void parameterGestureChanged(int parameterIndex, bool gestureIsStarting) override{ }

    void timerCallback() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SimpleEQAudioProcessor& audioProcessor;

    juce::Atomic<bool> parametersChanged{ false };  // Added space after <bool>

    CustomRotarySlider peakFreqSlider,
                      peakGainSlider,
                      peakQualitySlider,
                      lowCutFreqSlider,
                      highCutFreqSlider,
                      lowCutSlopeSlider,
                       highCutSlopeSlider;

    using APVTS = juce::AudioProcessorValueTreeState;
	using Attachment = APVTS::SliderAttachment;

	Attachment peakFreqSliderAttachment,
		       peakGainSliderAttachment,
		       peakQualitySliderAttachment,
		       lowCutFreqSliderAttachment,
		       highCutFreqSliderAttachment,
		       lowCutSlopeSliderAttachment,
		       highCutSlopeSliderAttachment;

    std::vector<juce::Component*> getComs();

	MonoChain monoChain;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SimpleEQAudioProcessorEditor);
};
