#pragma once

#include <JuceHeader.h>

namespace mvox
{

// Color scheme - modern dark theme with depth
namespace Colors
{
    inline juce::Colour bgDark(0xFF1A1A1E);
    inline juce::Colour bgPanel(0xFF222226);
    inline juce::Colour bgLight(0xFF2A2A2E);
    inline juce::Colour bgLighter(0xFF323236);
    
    inline juce::Colour accentPurple(0xFF7B2D8E);
    inline juce::Colour accentBlue(0xFF2D5A8E);
    inline juce::Colour accentTeal(0xFF2D8E8E);
    inline juce::Colour accentGreen(0xFF2D8E5A);
    inline juce::Colour accentOrange(0xFF8E5A2D);
    inline juce::Colour accentPink(0xFF8E2D5A);
    
    inline juce::Colour textPrimary(0xFFE0E0E0);
    inline juce::Colour textSecondary(0xFF909090);
    inline juce::Colour textDim(0xFF505050);
    inline juce::Colour textBright(0xFFFFFFFF);
    
    inline juce::Colour shadowColor(0x80000000);
    inline juce::Colour knobTrack(0xFF3A3A3E);
    inline juce::Colour knobFill(0xFF7B2D8E);
    inline juce::Colour toggleOn(0xFF7B2D8E);
    inline juce::Colour toggleOff(0xFF3A3A3E);
}

class MvoxKnob : public juce::Component
{
public:
    MvoxKnob(const juce::String& labelText, juce::AudioProcessorValueTreeState& apvts,
             const juce::String& paramId, juce::Colour accentColor = Colors::accentPurple);
    ~MvoxKnob() override;
    void paint(juce::Graphics& g) override;
    void resized() override;
    void setDisplaySuffix(const juce::String& suffix) { displaySuffix = suffix; }
    void setDecimalPlaces(int places) { decimalPlaces = places; }
    void setAccentColor(juce::Colour color) { accentColor = color; }
private:
    juce::Slider slider;
    juce::Label label;
    juce::AudioProcessorValueTreeState::SliderAttachment attachment;
    juce::Colour accentColor;
    juce::String displaySuffix;
    int decimalPlaces = 1;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MvoxKnob)
};

class MvoxToggle : public juce::Component
{
public:
    MvoxToggle(const juce::String& labelText, juce::AudioProcessorValueTreeState& apvts,
               const juce::String& paramId);
    ~MvoxToggle() override;
    void paint(juce::Graphics& g) override;
    void resized() override;
private:
    juce::TextButton button;
    juce::Label label;
    juce::AudioProcessorValueTreeState::ButtonAttachment attachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MvoxToggle)
};

class MvoxPanel : public juce::Component
{
public:
    MvoxPanel(const juce::String& title, juce::Colour accentColor = Colors::accentPurple);
    ~MvoxPanel() override;
    void paint(juce::Graphics& g) override;
    void resized() override;
    void addComponent(juce::Component* comp);
private:
    juce::String title;
    juce::Colour accentColor;
    juce::OwnedArray<juce::Component> components;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MvoxPanel)
};

} // namespace mvox
