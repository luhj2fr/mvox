#include "PluginProcessor.h"
#include "PluginEditor.h"

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

    auto addFloat = [&](const juce::String& id, const juce::String& name,
                        float min, float max, float step, float skew, float def,
                        const juce::String& label)
    {
        params.push_back(std::make_unique<juce::AudioParameterFloat>(
            id, name,
            juce::NormalisableRange<float>(min, max, step, skew), def,
            juce::AudioParameterFloatAttributes().withLabel(label)));
    };

    addFloat(compThresholdId, "Comp Threshold", -60.0f, 0.0f, 0.1f, 1.0f, -20.0f, "dB");
    addFloat(compRatioId, "Comp Ratio", 1.0f, 20.0f, 0.1f, 0.5f, 4.0f, ":1");
    addFloat(compAttackId, "Comp Attack", 0.1f, 100.0f, 0.1f, 0.3f, 5.0f, "ms");
    addFloat(compReleaseId, "Comp Release", 10.0f, 500.0f, 0.1f, 0.3f, 50.0f, "ms");
    addFloat(compGainId, "Comp Gain", -24.0f, 24.0f, 0.1f, 1.0f, 0.0f, "dB");
    addFloat(compKneeId, "Comp Knee", 0.0f, 24.0f, 0.1f, 1.0f, 6.0f, "dB");
    addFloat(eqLowFreqId, "Low Freq", 20.0f, 400.0f, 1.0f, 0.3f, 80.0f, "Hz");
    addFloat(eqLowGainId, "Low Gain", -18.0f, 18.0f, 0.1f, 1.0f, 0.0f, "dB");
    addFloat(eqMidFreqId, "Mid Freq", 200.0f, 8000.0f, 1.0f, 0.3f, 1000.0f, "Hz");
    addFloat(eqMidGainId, "Mid Gain", -18.0f, 18.0f, 0.1f, 1.0f, 0.0f, "dB");
    addFloat(eqMidQId, "Mid Q", 0.1f, 10.0f, 0.01f, 0.5f, 1.0f, "Q");
    addFloat(eqHighFreqId, "High Freq", 2000.0f, 20000.0f, 1.0f, 0.3f, 8000.0f, "Hz");
    addFloat(eqHighGainId, "High Gain", -18.0f, 18.0f, 0.1f, 1.0f, 0.0f, "dB");
    addFloat(deesserThresholdId, "De-esser Threshold", -60.0f, 0.0f, 0.1f, 1.0f, -30.0f, "dB");
    addFloat(deesserFreqId, "De-esser Freq", 2000.0f, 10000.0f, 1.0f, 0.3f, 6000.0f, "Hz");
    addFloat(deesserAmountId, "De-esser Amount", 0.0f, 100.0f, 0.1f, 1.0f, 50.0f, "%");
    addFloat(saturationDriveId, "Sat Drive", 0.0f, 10.0f, 0.01f, 0.5f, 0.0f, "dB");
    addFloat(saturationMixId, "Sat Mix", 0.0f, 100.0f, 0.1f, 1.0f, 0.0f, "%");
    addFloat(saturationOutputId, "Sat Output", -18.0f, 18.0f, 0.1f, 1.0f, 0.0f, "dB");
    addFloat(airAmountId, "Air Amount", 0.0f, 100.0f, 0.1f, 1.0f, 0.0f, "%");
    addFloat(limiterThresholdId, "Limiter Threshold", -30.0f, 0.0f, 0.1f, 1.0f, -6.0f, "dB");
    addFloat(outputGainId, "Output Gain", -24.0f, 24.0f, 0.1f, 1.0f, 0.0f, "dB");
    params.push_back(std::make_unique<juce::AudioParameterBool>(bypassId, "Bypass", false));

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
    int osFactor = (int)oversampling.getOversamplingFactor();
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate * osFactor;
    spec.maximumBlockSize = samplesPerBlock * osFactor;
    spec.numChannels = getTotalNumOutputChannels();

    oversampling.initProcessing(samplesPerBlock);
    compressor.prepare(spec);
    lowFilter.prepare(spec);
    *lowFilter.coefficients = *juce::dsp::IIR::Coefficients<float>::makeLowShelf(sampleRate, 80.0f, 0.707f, 1.0f);
    midFilter.prepare(spec);
    *midFilter.coefficients = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 1000.0f, 1.0f, 1.0f);
    highFilter.prepare(spec);
    *highFilter.coefficients = *juce::dsp::IIR::Coefficients<float>::makeHighShelf(sampleRate, 8000.0f, 0.707f, 1.0f);
    deesserFilter.prepare(spec);
    *deesserFilter.coefficients = *juce::dsp::IIR::Coefficients<float>::makeHighPass(sampleRate, 6000.0f);
    deesser.prepare(spec);
    deesser.setRatio(10.0f);
    deesser.setAttack(1.0f);
    deesser.setRelease(50.0f);
    airFilter.prepare(spec);
    *airFilter.coefficients = *juce::dsp::IIR::Coefficients<float>::makeHighShelf(sampleRate, 12000.0f, 0.5f, 1.0f);
    limiter.prepare(spec);
    limiter.setRelease(10.0f);
    needsUpdate = true;
}

void mvoxAudioProcessor::releaseResources()
{
    oversampling.reset();
}

void mvoxAudioProcessor::parameterChanged(const juce::String&, float)
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
    if (*apvts.getRawParameterValue(bypassId) > 0.5f)
        return;
    if (needsUpdate)
    {
        compressor.setThreshold(*apvts.getRawParameterValue(compThresholdId));
        compressor.setRatio(*apvts.getRawParameterValue(compRatioId));
        compressor.setAttack(*apvts.getRawParameterValue(compAttackId));
        compressor.setRelease(*apvts.getRawParameterValue(compReleaseId));
        float lowFreq = *apvts.getRawParameterValue(eqLowFreqId);
        float lowGain = *apvts.getRawParameterValue(eqLowGainId);
        *lowFilter.coefficients = *juce::dsp::IIR::Coefficients<float>::makeLowShelf(currentSampleRate, lowFreq, 0.707f, juce::Decibels::decibelsToGain(lowGain));
        float midFreq = *apvts.getRawParameterValue(eqMidFreqId);
        float midGain = *apvts.getRawParameterValue(eqMidGainId);
        float midQ = *apvts.getRawParameterValue(eqMidQId);
        *midFilter.coefficients = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(currentSampleRate, midFreq, midQ, juce::Decibels::decibelsToGain(midGain));
        float highFreq = *apvts.getRawParameterValue(eqHighFreqId);
        float highGain = *apvts.getRawParameterValue(eqHighGainId);
        *highFilter.coefficients = *juce::dsp::IIR::Coefficients<float>::makeHighShelf(currentSampleRate, highFreq, 0.707f, juce::Decibels::decibelsToGain(highGain));
        float deessFreq = *apvts.getRawParameterValue(deesserFreqId);
        *deesserFilter.coefficients = *juce::dsp::IIR::Coefficients<float>::makeHighPass(currentSampleRate, deessFreq);
        deesser.setThreshold(*apvts.getRawParameterValue(deesserThresholdId));
        float airAmount = *apvts.getRawParameterValue(airAmountId);
        float airGain = juce::Decibels::decibelsToGain(airAmount * 0.12f);
        *airFilter.coefficients = *juce::dsp::IIR::Coefficients<float>::makeHighShelf(currentSampleRate, 12000.0f, 0.5f, airGain);
        limiter.setThreshold(*apvts.getRawParameterValue(limiterThresholdId));
        needsUpdate = false;
    }

    auto&& osBlock = oversampling.processSamplesUp(buffer);
    juce::dsp::AudioBlock<float> block(osBlock);
    juce::dsp::ProcessContextReplacing<float> context(block);
    compressor.process(context);
    lowFilter.process(context);
    midFilter.process(context);
    highFilter.process(context);

    {
        juce::dsp::AudioBlock<float> copy = block;
        juce::dsp::ProcessContextReplacing<float> ctx(copy);
        deesserFilter.process(ctx);
        float deessAmount = *apvts.getRawParameterValue(deesserAmountId) / 100.0f;
        for (size_t ch = 0; ch < block.getNumChannels(); ++ch)
        {
            auto* d = block.getChannelPointer(ch);
            auto* f = copy.getChannelPointer(ch);
            for (size_t s = 0; s < block.getNumSamples(); ++s)
            {
                float fl = std::abs(f[s]);
                float r = 1.0f - (fl * deessAmount * 0.5f);
                d[s] *= juce::jlimit(0.2f, 1.0f, r);
            }
        }
    }

    {
        float drive = *apvts.getRawParameterValue(saturationDriveId);
        if (drive > 0.01f)
        {
            float satMix = *apvts.getRawParameterValue(saturationMixId) / 100.0f;
            float satOut = *apvts.getRawParameterValue(saturationOutputId);
            float satGain = juce::Decibels::decibelsToGain(satOut);
            for (size_t ch = 0; ch < block.getNumChannels(); ++ch)
            {
                auto* d = block.getChannelPointer(ch);
                for (size_t s = 0; s < block.getNumSamples(); ++s)
                {
                    float dry = d[s];
                    float wet = std::tanh(dry * (1.0f + drive * 0.5f));
                    d[s] = (dry * (1.0f - satMix) + wet * satMix) * satGain;
                }
            }
        }
    }

    airFilter.process(context);
    limiter.process(context);
    float compGain = *apvts.getRawParameterValue(compGainId);
    float outGain = *apvts.getRawParameterValue(outputGainId);
    block.multiplyBy(juce::Decibels::decibelsToGain(compGain + outGain));
    juce::dsp::AudioBlock<float> downBlock(buffer);
    oversampling.processSamplesDown(downBlock);
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
