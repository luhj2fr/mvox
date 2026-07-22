#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UIComponents.h"

class mvoxAudioEditor : public juce::AudioProcessorEditor
{
public:
    mvoxAudioEditor(mvoxAudioProcessor&);
    ~mvoxAudioEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    mvoxAudioProcessor& processor;
    
    // Branding
    juce::Label titleLabel;
    juce::Label subtitleLabel;
    juce::Label brandLabel;
    
    // Bypass toggle
    mvox::MvoxToggle bypassToggle;
    
    // Compressor section
    std::unique_ptr<mvox::MvoxPanel> compPanel;
    std::unique_ptr<mvox::MvoxKnob> compThreshold;
    std::unique_ptr<mvox::MvoxKnob> compRatio;
    std::unique_ptr<mvox::MvoxKnob> compAttack;
    std::unique_ptr<mvox::MvoxKnob> compRelease;
    std::unique_ptr<mvox::MvoxKnob> compGain;
    std::unique_ptr<mvox::MvoxKnob> compKnee;
    
    // EQ section
    std::unique_ptr<mvox::MvoxPanel> eqPanel;
    std::unique_ptr<mvox::MvoxKnob> eqLowFreq;
    std::unique_ptr<mvox::MvoxKnob> eqLowGain;
    std::unique_ptr<mvox::MvoxKnob> eqMidFreq;
    std::unique_ptr<mvox::MvoxKnob> eqMidGain;
    std::unique_ptr<mvox::MvoxKnob> eqMidQ;
    std::unique_ptr<mvox::MvoxKnob> eqHighFreq;
    std::unique_ptr<mvox::MvoxKnob> eqHighGain;
    
    // De-esser section
    std::unique_ptr<mvox::MvoxPanel> deesserPanel;
    std::unique_ptr<mvox::MvoxKnob> deesserThreshold;
    std::unique_ptr<mvox::MvoxKnob> deesserFreq;
    std::unique_ptr<mvox::MvoxKnob> deesserAmount;
    
    // Saturation section
    std::unique_ptr<mvox::MvoxPanel> satPanel;
    std::unique_ptr<mvox::MvoxKnob> satDrive;
    std::unique_ptr<mvox::MvoxKnob> satMix;
    std::unique_ptr<mvox::MvoxKnob> satOutput;
    
    // Air section
    std::unique_ptr<mvox::MvoxPanel> airPanel;
    std::unique_ptr<mvox::MvoxKnob> airAmount;
    
    // Limiter section
    std::unique_ptr<mvox::MvoxPanel> limiterPanel;
    std::unique_ptr<mvox::MvoxKnob> limiterThreshold;
    
    // Output section
    std::unique_ptr<mvox::MvoxPanel> outputPanel;
    std::unique_ptr<mvox::MvoxKnob> outputGain;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(mvoxAudioEditor)
};