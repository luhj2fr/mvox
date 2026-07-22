#include "UIComponents.h"

namespace mvox
{

//==============================================================================
// MvoxKnob
//==============================================================================
MvoxKnob::MvoxKnob(const juce::String& labelText, 
                   juce::AudioProcessorValueTreeState& apvts,
                   const juce::String& paramId, 
                   juce::Colour accent)
    : accentColor(accent)
    , attachment(apvts, paramId, slider)
{
    slider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 18);
    slider.setColour(juce::Slider::rotarySliderFillColourId, accentColor);
    slider.setColour(juce::Slider::rotarySliderOutlineColourId, Colors::knobTrack);
    slider.setColour(juce::Slider::textBoxTextColourId, Colors::textPrimary);
    slider.setColour(juce::Slider::textBoxBackgroundColourId, Colors::bgLight);
    slider.setColour(juce::Slider::textBoxOutlineColourId, Colors::bgPanel);
    slider.setVelocityBasedMode(true);
    slider.setVelocityModeParameters(1.0f, 0.5f, 0.0f);
    addAndMakeVisible(slider);
    
    label.setText(labelText, juce::dontSendNotification);
    label.setColour(juce::Label::textColourId, Colors::textSecondary);
    label.setJustificationType(juce::Justification::centred);
    label.setFont(juce::Font(10.0f, juce::Font::plain));
    addAndMakeVisible(label);
    
    setSize(70, 95);
}

MvoxKnob::~MvoxKnob() = default;

void MvoxKnob::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();
    auto knobArea = bounds.reduced(8, 8).withHeight(bounds.getHeight() - 30);
    auto shadowRect = knobArea.reduced(2).translated(0, 3);
    
    g.setColour(Colors::shadowColor);
    g.fillEllipse(shadowRect);
}

void MvoxKnob::resized()
{
    auto bounds = getLocalBounds();
    slider.setBounds(8, 8, bounds.getWidth() - 16, bounds.getWidth() - 16);
    label.setBounds(0, bounds.getHeight() - 22, bounds.getWidth(), 20);
}

//==============================================================================
// MvoxToggle
//==============================================================================
MvoxToggle::MvoxToggle(const juce::String& labelText,
                       juce::AudioProcessorValueTreeState& apvts,
                       const juce::String& paramId)
    : button(labelText)
    , label(labelText, juce::String())
    , attachment(apvts, paramId, button)
{
    button.setClickingTogglesState(true);
    button.setColour(juce::TextButton::buttonColourId, Colors::toggleOff);
    button.setColour(juce::TextButton::buttonOnColourId, Colors::toggleOn);
    button.setColour(juce::TextButton::textColourOffId, Colors::textSecondary);
    button.setColour(juce::TextButton::textColourOnId, Colors::textBright);
    addAndMakeVisible(button);
    
    setSize(60, 30);
}

MvoxToggle::~MvoxToggle() = default;

void MvoxToggle::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();
    g.setColour(Colors::shadowColor);
    g.fillRoundedRectangle(bounds.reduced(2).translated(0, 2), 4.0f);
}

void MvoxToggle::resized()
{
    button.setBounds(getLocalBounds());
}

//==============================================================================
// MvoxPanel
//==============================================================================
MvoxPanel::MvoxPanel(const juce::String& titleText, juce::Colour accent)
    : title(titleText)
    , accentColor(accent)
{
    setSize(200, 200);
}

MvoxPanel::~MvoxPanel() = default;

void MvoxPanel::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();
    
    // Drop shadow
    juce::Path shadowPath;
    shadowPath.addRoundedRectangle(bounds.reduced(4).translated(0, 4), 8.0f);
    g.setColour(Colors::shadowColor);
    g.fillPath(shadowPath);
    
    // Panel background
    g.setColour(Colors::bgPanel);
    g.fillRoundedRectangle(bounds.reduced(2), 8.0f);
    
    // Inner glow at top
    auto glowRect = bounds.reduced(2).withHeight(30);
    juce::ColourGradient glow(accentColor.withAlpha(0.1f), 0.0f, glowRect.getY(),
                              Colors::bgPanel, 0.0f, glowRect.getBottom(), false);
    g.setGradientFill(glow);
    g.fillRoundedRectangle(glowRect, 8.0f);
    
    // Title bar
    auto titleBar = bounds.removeFromTop(30).reduced(10, 5);
    g.setColour(accentColor);
    g.fillRoundedRectangle(titleBar.toFloat(), 4.0f);
    
    g.setColour(Colors::textBright);
    g.setFont(juce::Font(11.0f, juce::Font::bold));
    g.drawText(title, titleBar.toFloat(), juce::Justification::centred);
    
    // Border accent
    g.setColour(accentColor.withAlpha(0.3f));
    g.drawRoundedRectangle(bounds.reduced(2), 8.0f, 1.0f);
}

void MvoxPanel::resized()
{
    auto area = getLocalBounds().reduced(10, 35);
    int x = area.getX();
    int y = area.getY();
    
    for (auto* comp : components)
    {
        if (x + comp->getWidth() > area.getRight())
        {
            x = area.getX();
            y += 100;
        }
        comp->setTopLeftPosition(x, y);
        x += comp->getWidth() + 8;
    }
}

void MvoxPanel::addComponent(juce::Component* comp)
{
    components.add(comp);
    addAndMakeVisible(comp);
}

} // namespace mvox