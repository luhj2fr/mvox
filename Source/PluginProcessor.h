#pragma once

#include <JuceHeader.h>

class mvoxAudioProcessor : public juce::AudioProcessor,
                            public juce::AudioProcessorValueTreeState::Listener
{
public:
    mvoxAudioProcessor();
    ~mvoxAudioProcessor() override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override { return "mvox"; }

    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;

    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override {}
    const juce::String getProgramName(int) override { return {}; }
    void changeProgramName(int, const juce::String&) override {}

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState apvts;

    static const juce::String compThresholdId;
    static const juce::String compRatioId;
    static const juce::String compAttackId;
    static const juce::String compReleaseId;
    static const juce::String compGainId;
    static const juce::String compKneeId;

    static const juce::String eqLowFreqId;
    static const juce::String eqLowGainId;
    static const juce::String eqMidFreqId;
    static const juce::String eqMidGainId;
    static const juce::String eqMidQId;
    static const juce::String eqHighFreqId;
    static const juce::String eqHighGainId;

    static const juce::String deesserThresholdId;
    static const juce::String deesserFreqId;
    static const juce::String deesserAmountId;

    static const juce::String saturationDriveId;
    static const juce::String saturationMixId;
    static const juce::String saturationOutputId;
    
    static const juce::String airAmountId;
    static const juce::String limiterThresholdId;
    static const juce::String outputGainId;
    static const juce::String bypassId;

    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

private:
    void parameterChanged(const juce::String& parameterID, float newValue) override;

    juce::dsp::Compressor<float> compressor;
    juce::dsp::IIR::Filter<float> lowFilter;
    juce::dsp::IIR::Filter<float> midFilter;
    juce::dsp::IIR::Filter<float> highFilter;
    juce::dsp::Oversampling<float> oversampling;
    
    juce::dsp::Compressor<float> deesser;
    juce::dsp::IIR::Filter<float> deesserFilter;
    
    juce::dsp::Limiter<float> limiter;
    juce::dsp::IIR::Filter<float> airFilter;

    double currentSampleRate = 44100.0;
    bool needsUpdate = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(mvoxAudioProcessor)
};
