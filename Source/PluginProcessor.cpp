#include "PluginProcessor.h"
#include "PluginEditor.h"

// Parameter IDs
const juce::String mvoxAudioProcessor::compThresholdId = "compThreshold";
const juce::String mvoxAudioProcessor::compRatioId = "compRatio";
const juce::String mvoxAudioProcessor::compAttackId = "compAttack";
const juce::String mvoxAudioProcessor::compReleaseId = "compRelease";
const juce::String mvoxAudioProcessor::compGainId = "compGain";
const juce::String mvoxAudioProcessor::compKneeId = "compKnee";
const juce::String mvoxAudioProcessor::eqLowFreqId = "eqLowFreq";
const juce::String mvoxAudioProcessor::eqLowGainId = "eqLowGain";
const juce::String mvoxAudioProcessor::eqMidFreqId = "eqMidFreq";
const juce::String mvoxAudioProcessor::eqMidGainId = "eqMidGain";
const juce::String mvoxAudioProcessor::eqMidQId = "eqMidQ";
const juce::String mvoxAudioProcessor::eqHighFreqId = "eqHighFreq";
const juce::String mvoxAudioProcessor::eqHighGainId = "eqHighGain";
const juce::String mvoxAudioProcessor::deesserThresholdId = "deesserThreshold";
const juce::String mvoxAudioProcessor::deesserFreqId = "deesserFreq";
const juce::String mvoxAudioProcessor::deesserAmountId = "deesserAmount";
const juce::String mvoxAudioProcessor::saturationDriveId = "saturationDrive";
const juce::String mvoxAudioProcessor::saturationMixId = "saturationMix";
const juce::String mvoxAudioProcessor::saturationOutputId = "saturationOutput";
const juce::String mvoxAudioProcessor::airAmountId = "airAmount";
const juce::String mvoxAudioProcessor::limiterThresholdId = "limiterThreshold";
const juce::String mvoxAudioProcessor::outputGainId = "outputGain";
const juce::String mvoxAudioProcessor::bypassId = "bypass";

juce::AudioProcessorValueTreeState::ParameterLayout mvoxAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // Compressor parameters
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        compThresholdId, "Comp Threshold",
        juce::NormalisableRange<float>(-60.0f, 0.0f, 0.1f, 1.0f), -20.0f,
        juce::AudioParameterFloatAttributes().withLabel("dB")));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        compRatioId, "Comp Ratio",
        juce::NormalisableRange<float>(1.0f, 20.0f, 0.1f, 0.5f), 4.0f,
        juce::AudioParameterFloatAttributes().withLabel(":1")));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        compAttackId, "Comp Attack",
        juce::NormalisableRange<float>(0.1f, 100.0f, 0.1f, 0.3f), 5.0f,
        juce::AudioParameterFloatAttributes().withLabel("ms")));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        compReleaseId, "Comp Release",
        juce::NormalisableRange<float>(10.0f, 500.0f, 0.1f, 0.3f), 50.0f,
        juce::AudioParameterFloatAttributes().withLabel("ms")));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        compGainId, "Comp Gain",
        juce::NormalisableRange<float>(-24.0f, 24.0f, 0.1f, 1.0f), 0.0f,
        juce::AudioParameterFloatAttributes().withLabel("dB")));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        compKneeId, "Comp Knee",
        juce::NormalisableRange<float>(0.0f, 24.0f, 0.1f, 1.0f), 6.0f,
        juce::AudioParameterFloatAttributes().withLabel("dB")));

    // EQ Parameters
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        eqLowFreqId, "Low Freq",
        juce::NormalisableRange<float>(20.0f, 400.0f, 1.0f, 0.3f), 80.0f,
        juce::AudioParameterFloatAttributes().withLabel("Hz")));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        eqLowGainId, "Low Gain",
        juce::NormalisableRange<float>(-18.0f, 18.0f, 0.1f, 1.0f), 0.0f,
        juce::AudioParameterFloatAttributes().withLabel("dB")));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        eqMidFreqId, "Mid Freq",
        juce::NormalisableRange<float>(200.0f, 8000.0f, 1.0f, 0.3f), 1000.0f,
        juce::AudioParameterFloatAttributes().withLabel("Hz")));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        eqMidGainId, "Mid Gain",
        juce::NormalisableRange<float>(-18.0f, 18.0f, 0.1f, 1.0f), 0.0f,
        juce::AudioParameterFloatAttributes().withLabel("dB")));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        eqMidQId, "Mid Q",
        juce::NormalisableRange<float>(0.1f, 10.0f, 0.01f, 0.5f), 1.0f,
        juce::AudioParameterFloatAttributes().withLabel("Q")));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        eqHighFreqId, "High Freq",
        juce::NormalisableRange<float>(2000.0f, 20000.0f, 1.0f, 0.3f), 8000.0f,
        juce::AudioParameterFloatAttributes().withLabel("Hz")));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        eqHighGainId, "High Gain",
        juce::NormalisableRange<float>(-18.0f, 18.0f, 0.1f, 1.0f), 0.0f,
        juce::AudioParameterFloatAttributes().withLabel("dB")));

    // De-esser
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        deesserThresholdId, "De-esser Threshold",
        juce::NormalisableRange<float>(-60.0f, 0.0f, 0.1f, 1.0f), -30.0f,
        juce::AudioParameterFloatAttributes().withLabel("dB")));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        deesserFreqId, "De-esser Freq",
        juce::NormalisableRange<float>(2000.0f, 10000.0f, 1.0f, 0.3f), 6000.0f,
        juce::AudioParameterFloatAttributes().withLabel("Hz")));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        deesserAmountId, "De-esser Amount",
        juce::NormalisableRange<float>(0.0f, 100.0f, 0.1f, 1.0f), 50.0f,
        juce::AudioParameterFloatAttributes().withLabel("%")));

    // Saturation
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        saturationDriveId, "Sat Drive",
        juce::NormalisableRange<float>(0.0f, 10.0f, 0.01f, 0.5f), 0.0f,
        juce::AudioParameterFloatAttributes().withLabel("dB")));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        saturationMixId, "Sat Mix",
        juce::NormalisableRange<float>(0.0f, 100.0f, 0.1f, 1.0f), 0.0f,
        juce::AudioParameterFloatAttributes().withLabel("%")));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        saturationOutputId, "Sat Output",
        juce::NormalisableRange<float>(-18.0f, 18.0f, 0.1f, 1.0f), 0.0f,
        juce::AudioParameterFloatAttributes().withLabel("dB")));

    // Air
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        airAmountId, "Air Amount",
        juce::NormalisableRange<float>(0.0f, 100.0f, 0.1f, 1.0f), 0.0f,
        juce::AudioParameterFloatAttributes().withLabel("%")));

    // Limiter
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        limiterThresholdId, "Limiter Threshold",
        juce::NormalisableRange<float>(-30.0f, 0.0f, 0.1f, 1.0f), -6.0f,
        juce::AudioParameterFloatAttributes().withLabel("dB")));

    // Output
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        outputGainId, "Output Gain",
        juce::NormalisableRange<float>(-24.0f, 24.0f, 0.1f, 1.0f), 0.0f,
        juce::AudioParameterFloatAttributes().withLabel("dB")));

    // Bypass
    params.push_back(std::make_unique<juce::AudioParameterBool>(
        bypassId, "Bypass", false));

    return { params.begin(), params.end() };
}

mvoxAudioProcessor::mvoxAudioProcessor()
    : AudioProcessor(BusesProperties()
                       .withInput("Input", juce::AudioChannelSet::stereo(), true)
                       .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
      apvts(*this, nullptr, "Parameters", createParameterLayout()),
      oversampling(2, 2, juce::dsp::Oversampling<float>::filterHalfBandPolyphaseIIR)
{
    apvts.addParameterListener(compThresholdId, this);
    apvts.addParameterListener(compRatioId, this);
    apvts.addParameterListener(compAttackId, this);
    apvts.addParameterListener(compReleaseId, this);
    apvts.addParameterListener(compKneeId, this);
    apvts.addParameterListener(deesserThresholdId, this);
    apvts.addParameterListener(deesserFreqId, this);
}

mvoxAudioProcessor::~mvoxAudioProcessor()
{
    apvts.removeParameterListener(compThresholdId, this);
    apvts.removeParameterListener(compRatioId, this);
    apvts.removeParameterListener(compAttackId, this);
    apvts.removeParameterListener(compReleaseId, this);
    apvts.removeParameterListener(compKneeId, this);
    apvts.removeParameterListener(deesserThresholdId, this);
    apvts.removeParameterListener(deesserFreqId, this);
}

void mvoxAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    currentSampleRate = sampleRate;
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate * (int)oversampling.getOversamplingFactor();
    spec.maximumBlockSize = samplesPerBlock * (int)oversampling.getOversamplingFactor();
    spec.numChannels = getTotalNumOutputChannels();

    oversampling.initProcessing(samplesPerBlock);
    
    // Compressor
    compressor.prepare(spec);
    compressor.setMode(juce::dsp::Compressor<float>::Mode::RMS);
    
    // EQ Filters
    auto coeffs = juce::dsp::IIR::Coefficients<float>::makeLowShelf(sampleRate, 80.0f, 0.707f, 1.0f);
    lowFilter.prepare(spec);
    *lowFilter.coefficients = *coeffs;
    
    coeffs = juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 1000.0f, 1.0f, 1.0f);
    midFilter.prepare(spec);
    *midFilter.coefficients = *coeffs;
    
    coeffs = juce::dsp::IIR::Coefficients<float>::makeHighShelf(sampleRate, 8000.0f, 0.707f, 1.0f);
    highFilter.prepare(spec);
    *highFilter.coefficients = *coeffs;
    
    // De-esser
    deesserFilter.prepare(spec);
    deesserFilter.coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(sampleRate, 6000.0f);
    deesser.prepare(spec);
    deesser.setMode(juce::dsp::Compressor<float>::Mode::RMS);
    deesser.setRatio(10.0f);
    deesser.setAttack(1.0f);
    deesser.setRelease(50.0f);
    
    // Saturation
    saturator.prepare(spec);
    
    // Air filter
    airFilter.prepare(spec);
    coeffs = juce::dsp::IIR::Coefficients<float>::makeHighShelf(sampleRate, 12000.0f, 0.5f, 1.0f);
    *airFilter.coefficients = *coeffs;
    
    // Limiter
    limiter.prepare(spec);
    limiter.setRelease(10.0f);
    
    needsUpdate = true;
}

void mvoxAudioProcessor::releaseResources()
{
    oversampling.reset();
}

void mvoxAudioProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    needsUpdate = true;
}

void mvoxAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());
    
    bool bypassed = *apvts.getRawParameterValue(bypassId) > 0.5f;
    
    if (bypassed)
        return;
    
    // Update parameters if needed
    if (needsUpdate)
    {
        compressor.setThreshold(*apvts.getRawParameterValue(compThresholdId));
        compressor.setRatio(*apvts.getRawParameterValue(compRatioId));
        compressor.setAttack(*apvts.getRawParameterValue(compAttackId));
        compressor.setRelease(*apvts.getRawParameterValue(compReleaseId));
        compressor.setKnee(*apvts.getRawParameterValue(compKneeId));
        
        float lowFreq = *apvts.getRawParameterValue(eqLowFreqId);
        float lowGain = *apvts.getRawParameterValue(eqLowGainId);
        *lowFilter.coefficients = *juce::dsp::IIR::Coefficients<float>::makeLowShelf(
            currentSampleRate, lowFreq, 0.707f, juce::Decibels::decibelsToGain(lowGain));
        
        float midFreq = *apvts.getRawParameterValue(eqMidFreqId);
        float midGain = *apvts.getRawParameterValue(eqMidGainId);
        float midQ = *apvts.getRawParameterValue(eqMidQId);
        *midFilter.coefficients = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(
            currentSampleRate, midFreq, midQ, juce::Decibels::decibelsToGain(midGain));
        
        float highFreq = *apvts.getRawParameterValue(eqHighFreqId);
        float highGain = *apvts.getRawParameterValue(eqHighGainId);
        *highFilter.coefficients = *juce::dsp::IIR::Coefficients<float>::makeHighShelf(
            currentSampleRate, highFreq, 0.707f, juce::Decibels::decibelsToGain(highGain));
        
        float deessFreq = *apvts.getRawParameterValue(deesserFreqId);
        *deesserFilter.coefficients = *juce::dsp::IIR::Coefficients<float>::makeHighPass(
            currentSampleRate, deessFreq);
        deesser.setThreshold(*apvts.getRawParameterValue(deesserThresholdId));
        
        float airAmount = *apvts.getRawParameterValue(airAmountId);
        float airGain = juce::Decibels::decibelsToGain(airAmount * 0.12f);
        *airFilter.coefficients = *juce::dsp::IIR::Coefficients<float>::makeHighShelf(
            currentSampleRate, 12000.0f, 0.5f, airGain);
        
        limiter.setThreshold(*apvts.getRawParameterValue(limiterThresholdId));
        
        needsUpdate = false;
    }
    
    // Process through oversampling
    auto oversampledBlock = oversampling.processSamplesUp(buffer);
    
    juce::dsp::AudioBlock<float> block(oversampledBlock);
    juce::dsp::ProcessContextReplacing<float> context(block);
    
    // 1. Compressor
    compressor.process(context);
    
    // 2. EQ
    lowFilter.process(context);
    midFilter.process(context);
    highFilter.process(context);
    
    // 3. De-esser
    {
        juce::AudioBuffer<float> filteredBuffer(oversampledBlock);
        juce::dsp::AudioBlock<float> filteredBlock(filteredBuffer);
        juce::dsp::ProcessContextReplacing<float> filteredContext(filteredBlock);
        deesserFilter.process(filteredContext);
        
        float deessAmount = *apvts.getRawParameterValue(deesserAmountId) / 100.0f;
        for (int ch = 0; ch < oversampledBlock.getNumChannels(); ++ch)
        {
            auto* channelData = oversampledBlock.getWritePointer(ch);
            auto* filteredData = filteredBuffer.getReadPointer(ch);
            for (int s = 0; s < oversampledBlock.getNumSamples(); ++s)
            {
                float filteredLevel = std::abs(filteredData[s]);
                float reduction = 1.0f - (filteredLevel * deessAmount * 0.5f);
                reduction = juce::jlimit(0.2f, 1.0f, reduction);
                channelData[s] *= reduction;
            }
        }
    }
    
    // 4. Saturation
    {
        float drive = *apvts.getRawParameterValue(saturationDriveId);
        if (drive > 0.01f)
        {
            float satMix = *apvts.getRawParameterValue(saturationMixId) / 100.0f;
            float satOut = *apvts.getRawParameterValue(saturationOutputId);
            float satGain = juce::Decibels::decibelsToGain(satOut);
            
            for (int ch = 0; ch < oversampledBlock.getNumChannels(); ++ch)
            {
                auto* channelData = oversampledBlock.getWritePointer(ch);
                for (int s = 0; s < oversampledBlock.getNumSamples(); ++s)
                {
                    float dry = channelData[s];
                    float wet = std::tanh(dry * (1.0f + drive * 0.5f));
                    channelData[s] = (dry * (1.0f - satMix) + wet * satMix) * satGain;
                }
            }
        }
    }
    
    // 5. Air
    airFilter.process(context);
    
    // 6. Limiter
    limiter.process(context);
    
    // Apply makeup + output gain
    float compGain = *apvts.getRawParameterValue(compGainId);
    float outGain = *apvts.getRawParameterValue(outputGainId);
    float totalGain = juce::Decibels::decibelsToGain(compGain + outGain);
    block.multiplyBy(totalGain);
    
    // Downsample
    oversampling.processSamplesDown(buffer);
}

juce::AudioProcessorEditor* mvoxAudioProcessor::createEditor()
{
    return new mvoxAudioEditor(*this);
}

bool mvoxAudioProcessor::hasEditor() const
{
    return true;
}

void mvoxAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void mvoxAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
    if (xml != nullptr)
        apvts.replaceState(juce::ValueTree::fromXml(*xml));
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new mvoxAudioProcessor();
}