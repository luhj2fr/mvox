#include "PluginEditor.h"

//==============================================================================
mvoxAudioEditor::mvoxAudioEditor(mvoxAudioProcessor& p)
    : AudioProcessorEditor(&p), processor(p),
      bypassToggle("Bypass", p.apvts, mvoxAudioProcessor::bypassId)
{
    setSize(820, 580);
    setResizable(false, false);
    
    getLookAndFeel().setColour(juce::ResizableWindow::backgroundColourId, mvox::Colors::bgDark);
    
    // Branding labels
    titleLabel.setText("mvox", juce::dontSendNotification);
    titleLabel.setFont(juce::Font(28.0f, juce::Font::bold));
    titleLabel.setColour(juce::Label::textColourId, mvox::Colors::textBright);
    titleLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(titleLabel);
    
    subtitleLabel.setText("Vocal Processor", juce::dontSendNotification);
    subtitleLabel.setFont(juce::Font(11.0f, juce::Font::plain));
    subtitleLabel.setColour(juce::Label::textColourId, mvox::Colors::textSecondary);
    subtitleLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(subtitleLabel);
    
    brandLabel.setText("prodbymdotty", juce::dontSendNotification);
    brandLabel.setFont(juce::Font(9.0f, juce::Font::italic));
    brandLabel.setColour(juce::Label::textColourId, mvox::Colors::textDim);
    brandLabel.setJustificationType(juce::Justification::centredRight);
    addAndMakeVisible(brandLabel);
    
    addAndMakeVisible(bypassToggle);
    
    //==========================================================================
    // Compressor Section
    //==========================================================================
    compPanel = std::make_unique<mvox::MvoxPanel>("COMPRESSOR", mvox::Colors::accentPurple);
    
    compThreshold = std::make_unique<mvox::MvoxKnob>("Threshold", p.apvts, p.compThresholdId, mvox::Colors::accentPurple);
    compThreshold->setDisplaySuffix(" dB");
    compThreshold->setDecimalPlaces(1);
    compPanel->addComponent(compThreshold.get());
    
    compRatio = std::make_unique<mvox::MvoxKnob>("Ratio", p.apvts, p.compRatioId, mvox::Colors::accentPurple);
    compRatio->setDisplaySuffix(":1");
    compPanel->addComponent(compRatio.get());
    
    compAttack = std::make_unique<mvox::MvoxKnob>("Attack", p.apvts, p.compAttackId, mvox::Colors::accentPurple);
    compAttack->setDisplaySuffix(" ms");
    compPanel->addComponent(compAttack.get());
    
    compRelease = std::make_unique<mvox::MvoxKnob>("Release", p.apvts, p.compReleaseId, mvox::Colors::accentPurple);
    compRelease->setDisplaySuffix(" ms");
    compPanel->addComponent(compRelease.get());
    
    compGain = std::make_unique<mvox::MvoxKnob>("Makeup", p.apvts, p.compGainId, mvox::Colors::accentPurple);
    compGain->setDisplaySuffix(" dB");
    compPanel->addComponent(compGain.get());
    
    compKnee = std::make_unique<mvox::MvoxKnob>("Knee", p.apvts, p.compKneeId, mvox::Colors::accentPurple);
    compKnee->setDisplaySuffix(" dB");
    compPanel->addComponent(compKnee.get());
    
    addAndMakeVisible(compPanel.get());
    
    //==========================================================================
    // EQ Section
    //==========================================================================
    eqPanel = std::make_unique<mvox::MvoxPanel>("EQUALIZER", mvox::Colors::accentTeal);
    
    eqLowFreq = std::make_unique<mvox::MvoxKnob>("Low Freq", p.apvts, p.eqLowFreqId, mvox::Colors::accentTeal);
    eqLowFreq->setDisplaySuffix(" Hz");
    eqPanel->addComponent(eqLowFreq.get());
    
    eqLowGain = std::make_unique<mvox::MvoxKnob>("Low Gain", p.apvts, p.eqLowGainId, mvox::Colors::accentTeal);
    eqLowGain->setDisplaySuffix(" dB");
    eqPanel->addComponent(eqLowGain.get());
    
    eqMidFreq = std::make_unique<mvox::MvoxKnob>("Mid Freq", p.apvts, p.eqMidFreqId, mvox::Colors::accentTeal);
    eqMidFreq->setDisplaySuffix(" Hz");
    eqPanel->addComponent(eqMidFreq.get());
    
    eqMidGain = std::make_unique<mvox::MvoxKnob>("Mid Gain", p.apvts, p.eqMidGainId, mvox::Colors::accentTeal);
    eqMidGain->setDisplaySuffix(" dB");
    eqPanel->addComponent(eqMidGain.get());
    
    eqMidQ = std::make_unique<mvox::MvoxKnob>("Mid Q", p.apvts, p.eqMidQId, mvox::Colors::accentTeal);
    eqMidQ->setDisplaySuffix(" Q");
    eqPanel->addComponent(eqMidQ.get());
    
    eqHighFreq = std::make_unique<mvox::MvoxKnob>("High Freq", p.apvts, p.eqHighFreqId, mvox::Colors::accentTeal);
    eqHighFreq->setDisplaySuffix(" Hz");
    eqPanel->addComponent(eqHighFreq.get());
    
    eqHighGain = std::make_unique<mvox::MvoxKnob>("High Gain", p.apvts, p.eqHighGainId, mvox::Colors::accentTeal);
    eqHighGain->setDisplaySuffix(" dB");
    eqPanel->addComponent(eqHighGain.get());
    
    addAndMakeVisible(eqPanel.get());
    
    //==========================================================================
    // De-esser Section
    //==========================================================================
    deesserPanel = std::make_unique<mvox::MvoxPanel>("DE-ESSER", mvox::Colors::accentPink);
    
    deesserThreshold = std::make_unique<mvox::MvoxKnob>("Threshold", p.apvts, p.deesserThresholdId, mvox::Colors::accentPink);
    deesserThreshold->setDisplaySuffix(" dB");
    deesserPanel->addComponent(deesserThreshold.get());
    
    deesserFreq = std::make_unique<mvox::MvoxKnob>("Frequency", p.apvts, p.deesserFreqId, mvox::Colors::accentPink);
    deesserFreq->setDisplaySuffix(" Hz");
    deesserPanel->addComponent(deesserFreq.get());
    
    deesserAmount = std::make_unique<mvox::MvoxKnob>("Amount", p.apvts, p.deesserAmountId, mvox::Colors::accentPink);
    deesserAmount->setDisplaySuffix(" %");
    deesserPanel->addComponent(deesserAmount.get());
    
    addAndMakeVisible(deesserPanel.get());
    
    //==========================================================================
    // Saturation Section
    //==========================================================================
    satPanel = std::make_unique<mvox::MvoxPanel>("SATURATION", mvox::Colors::accentOrange);
    
    satDrive = std::make_unique<mvox::MvoxKnob>("Drive", p.apvts, p.saturationDriveId, mvox::Colors::accentOrange);
    satDrive->setDisplaySuffix(" dB");
    satPanel->addComponent(satDrive.get());
    
    satMix = std::make_unique<mvox::MvoxKnob>("Mix", p.apvts, p.saturationMixId, mvox::Colors::accentOrange);
    satMix->setDisplaySuffix(" %");
    satPanel->addComponent(satMix.get());
    
    satOutput = std::make_unique<mvox::MvoxKnob>("Output", p.apvts, p.saturationOutputId, mvox::Colors::accentOrange);
    satOutput->setDisplaySuffix(" dB");
    satPanel->addComponent(satOutput.get());
    
    addAndMakeVisible(satPanel.get());
    
    //==========================================================================
    // Air Section
    //==========================================================================
    airPanel = std::make_unique<mvox::MvoxPanel>("AIR", mvox::Colors::accentBlue);
    
    airAmount = std::make_unique<mvox::MvoxKnob>("Amount", p.apvts, p.airAmountId, mvox::Colors::accentBlue);
    airAmount->setDisplaySuffix(" %");
    airPanel->addComponent(airAmount.get());
    
    addAndMakeVisible(airPanel.get());
    
    //==========================================================================
    // Limiter Section
    //==========================================================================
    limiterPanel = std::make_unique<mvox::MvoxPanel>("LIMITER", mvox::Colors::accentGreen);
    
    limiterThreshold = std::make_unique<mvox::MvoxKnob>("Threshold", p.apvts, p.limiterThresholdId, mvox::Colors::accentGreen);
    limiterThreshold->setDisplaySuffix(" dB");
    limiterPanel->addComponent(limiterThreshold.get());
    
    addAndMakeVisible(limiterPanel.get());
    
    //==========================================================================
    // Output Section
    //==========================================================================
    outputPanel = std::make_unique<mvox::MvoxPanel>("OUTPUT", mvox::Colors::accentBlue);
    
    outputGain = std::make_unique<mvox::MvoxKnob>("Gain", p.apvts, p.outputGainId, mvox::Colors::accentBlue);
    outputGain->setDisplaySuffix(" dB");
    outputPanel->addComponent(outputGain.get());
    
    addAndMakeVisible(outputPanel.get());
}

mvoxAudioEditor::~mvoxAudioEditor() = default;

//==============================================================================
void mvoxAudioEditor::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds();
    
    // Dark background with subtle gradient
    juce::ColourGradient bgGradient(
        mvox::Colors::bgDark, 
        0.0f, 0.0f,
        mvox::Colors::bgDark.darker(0.15f), 
        0.0f, (float)getHeight(), 
        false);
    g.setGradientFill(bgGradient);
    g.fillRect(bounds);
    
    // Top accent bar
    auto topBar = bounds.removeFromTop(4);
    g.setColour(mvox::Colors::accentPurple);
    g.fillRect(topBar);
    
    // Bottom glow line
    auto bottomLine = bounds.removeFromBottom(40).withHeight(1);
    g.setColour(mvox::Colors::accentPurple.withAlpha(0.2f));
    g.fillRect(bottomLine);
    
    // Subtle grid pattern for depth
    g.setColour(juce::Colour(0x08FFFFFF));
    for (int x = 0; x < getWidth(); x += 20)
        g.drawVerticalLine(x, 0.0f, (float)getHeight());
    for (int y = 0; y < getHeight(); y += 20)
        g.drawHorizontalLine(y, 0.0f, (float)getWidth());
    
    // Left decorative line
    auto leftLine = bounds.removeFromLeft(2);
    g.setColour(mvox::Colors::accentPurple.withAlpha(0.1f));
    g.fillRect(leftLine);
    
    // Right decorative line
    auto rightLine = bounds.removeFromRight(2);
    g.fillRect(rightLine);
}

//==============================================================================
void mvoxAudioEditor::resized()
{
    auto bounds = getLocalBounds();
    
    // Title area
    auto header = bounds.removeFromTop(60);
    titleLabel.setBounds(header.removeFromTop(35).reduced(0, 2));
    subtitleLabel.setBounds(header.reduced(0, 2));
    
    // Brand label in bottom right
    brandLabel.setBounds(getWidth() - 120, getHeight() - 25, 110, 20);
    
    // Bypass toggle in header area
    bypassToggle.setBounds(getWidth() - 80, 8, 70, 28);
    
    // Main content area with padding
    auto content = bounds.reduced(8, 4);
    
    // Layout sections in rows
    auto row1 = content.removeFromTop(200);
    
    auto compSection = row1.removeFromLeft(350).reduced(4);
    compPanel->setBounds(compSection);
    
    auto eqSection = row1.removeFromLeft(row1.getWidth()).reduced(4);
    eqPanel->setBounds(eqSection);
    
    // Row 2: De-esser, Saturation, Air, Limiter, Output
    auto row2 = content.removeFromTop(190);
    
    auto deesserSection = row2.removeFromLeft(180).reduced(4);
    deesserPanel->setBounds(deesserSection);
    
    auto satSection = row2.removeFromLeft(180).reduced(4);
    satPanel->setBounds(satSection);
    
    auto airSection = row2.removeFromLeft(120).reduced(4);
    airPanel->setBounds(airSection);
    
    auto limiterSection = row2.removeFromLeft(120).reduced(4);
    limiterPanel->setBounds(limiterSection);
    
    auto outputSection = row2.reduced(4);
    outputPanel->setBounds(outputSection);
}