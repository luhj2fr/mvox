#pragma once

#include <JuceHeader.h>

namespace mvox
{

namespace ParamRanges
{
    constexpr float compThresholdMin = -60.0f;
    constexpr float compThresholdMax = 0.0f;
    constexpr float compThresholdDefault = -20.0f;
    constexpr float compThresholdStep = 0.1f;

    constexpr float compRatioMin = 1.0f;
    constexpr float compRatioMax = 20.0f;
    constexpr float compRatioDefault = 4.0f;
    constexpr float compRatioStep = 0.1f;

    constexpr float compAttackMin = 0.1f;
    constexpr float compAttackMax = 100.0f;
    constexpr float compAttackDefault = 5.0f;
    constexpr float compAttackStep = 0.1f;

    constexpr float compReleaseMin = 10.0f;
    constexpr float compReleaseMax = 500.0f;
    constexpr float compReleaseDefault = 50.0f;
    constexpr float compReleaseStep = 0.1f;

    constexpr float compGainMin = -24.0f;
    constexpr float compGainMax = 24.0f;
    constexpr float compGainDefault = 0.0f;
    constexpr float compGainStep = 0.1f;

    constexpr float compKneeMin = 0.0f;
    constexpr float compKneeMax = 24.0f;
    constexpr float compKneeDefault = 6.0f;
    constexpr float compKneeStep = 0.1f;

    constexpr float eqLowFreqMin = 20.0f;
    constexpr float eqLowFreqMax = 400.0f;
    constexpr float eqLowFreqDefault = 80.0f;
    constexpr float eqLowFreqStep = 1.0f;

    constexpr float eqLowGainMin = -18.0f;
    constexpr float eqLowGainMax = 18.0f;
    constexpr float eqLowGainDefault = 0.0f;
    constexpr float eqLowGainStep = 0.1f;

    constexpr float eqMidFreqMin = 200.0f;
    constexpr float eqMidFreqMax = 8000.0f;
    constexpr float eqMidFreqDefault = 1000.0f;
    constexpr float eqMidFreqStep = 1.0f;

    constexpr float eqMidGainMin = -18.0f;
    constexpr float eqMidGainMax = 18.0f;
    constexpr float eqMidGainDefault = 0.0f;
    constexpr float eqMidGainStep = 0.1f;

    constexpr float eqMidQMin = 0.1f;
    constexpr float eqMidQMax = 10.0f;
    constexpr float eqMidQDefault = 1.0f;
    constexpr float eqMidQStep = 0.01f;

    constexpr float eqHighFreqMin = 2000.0f;
    constexpr float eqHighFreqMax = 20000.0f;
    constexpr float eqHighFreqDefault = 8000.0f;
    constexpr float eqHighFreqStep = 1.0f;

    constexpr float eqHighGainMin = -18.0f;
    constexpr float eqHighGainMax = 18.0f;
    constexpr float eqHighGainDefault = 0.0f;
    constexpr float eqHighGainStep = 0.1f;

    constexpr float deesserThresholdMin = -60.0f;
    constexpr float deesserThresholdMax = 0.0f;
    constexpr float deesserThresholdDefault = -30.0f;
    constexpr float deesserThresholdStep = 0.1f;

    constexpr float deesserFreqMin = 2000.0f;
    constexpr float deesserFreqMax = 10000.0f;
    constexpr float deesserFreqDefault = 6000.0f;
    constexpr float deesserFreqStep = 1.0f;

    constexpr float deesserAmountMin = 0.0f;
    constexpr float deesserAmountMax = 100.0f;
    constexpr float deesserAmountDefault = 50.0f;
    constexpr float deesserAmountStep = 0.1f;

    constexpr float saturationDriveMin = 0.0f;
    constexpr float saturationDriveMax = 10.0f;
    constexpr float saturationDriveDefault = 0.0f;
    constexpr float saturationDriveStep = 0.01f;

    constexpr float saturationMixMin = 0.0f;
    constexpr float saturationMixMax = 100.0f;
    constexpr float saturationMixDefault = 0.0f;
    constexpr float saturationMixStep = 0.1f;

    constexpr float saturationOutputMin = -18.0f;
    constexpr float saturationOutputMax = 18.0f;
    constexpr float saturationOutputDefault = 0.0f;
    constexpr float saturationOutputStep = 0.1f;

    constexpr float airAmountMin = 0.0f;
    constexpr float airAmountMax = 100.0f;
    constexpr float airAmountDefault = 0.0f;
    constexpr float airAmountStep = 0.1f;

    constexpr float limiterThresholdMin = -30.0f;
    constexpr float limiterThresholdMax = 0.0f;
    constexpr float limiterThresholdDefault = -6.0f;
    constexpr float limiterThresholdStep = 0.1f;

    constexpr float outputGainMin = -24.0f;
    constexpr float outputGainMax = 24.0f;
    constexpr float outputGainDefault = 0.0f;
    constexpr float outputGainStep = 0.1f;
}

} // namespace mvox