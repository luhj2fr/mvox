# mvox - Vocal Processor VST3 Plugin

Modern vocal processor plugin inspired by xvox pro by Nuro Audio.
Built with JUCE framework.

## Features
- **Compressor** - Full-featured dynamics processor with threshold, ratio, attack, release, makeup gain, and knee
- **3-Band EQ** - Low shelf, peak mid, and high shelf with adjustable frequencies and gains
- **De-esser** - Frequency-dependent sibilance reduction with adjustable threshold, frequency, and amount
- **Saturation** - Analog-style drive with mix control and output
- **Air** - High-frequency enhancement for presence and sparkle
- **Limiter** - Output protection with adjustable threshold
- **Output Control** - Master gain with bypass

## Requirements
- CMake 3.22+
- C++20 compatible compiler (MSVC 2022, GCC 11+, Clang 14+)
- JUCE 7+ (will be cloned automatically if not found)

## Build Instructions

### Local Windows Build
```bash
# Clone JUCE next to the project folder
git clone --depth 1 https://github.com/juce-framework/JUCE.git

# Configure with Visual Studio 2022
cmake -B build -G "Visual Studio 17 2022"

# Build VST3
cmake --build build --target mvox_VST3 --config Release

# Output: build/mvox_artefacts/Release/VST3/mvox.vst3
```

### GitHub Actions (automatic)
Push to `main` or `master` on GitHub — the workflow in `.github/workflows/build.yml` automatically:
1. Checks out code
2. Clones JUCE
3. Configures with Visual Studio 2022
4. Builds `mvox_VST3` in Release
5. Uploads the `.vst3` as a downloadable artifact

## Installation
Copy the built `.vst3` folder to:
- **Windows**: `C:\Program Files\Common Files\VST3\`

## Plugin Details
- Name: mvox
- Version: 1.0.0
- Format: VST3
- Category: Fx | Dynamics | EQ
- Vendor: luhj2fr
- Channels: Stereo

## Credits
Developed by luhj2fr
Design inspired by xvox pro by Nuro Audio
