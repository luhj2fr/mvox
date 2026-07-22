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

### Windows (Visual Studio)
```bash
# Clone with JUCE
git clone --recursive https://github.com/prodbymdotty/mvox.git
cd mvox

# Or clone JUCE separately
git clone https://github.com/juce-framework/JUCE.git

# Configure
cmake -B build -G "Visual Studio 17 2022"

# Build VST3
cmake --build build --target mvox_VST3 --config Release

# Output will be in build/mvox_artefacts/Release/VST3/
```

### macOS
```bash
cmake -B build -G Xcode
cmake --build build --target mvox_VST3 --config Release
```

### Linux
```bash
cmake -B build -G "Unix Makefiles"
cmake --build build --target mvox_VST3 --config Release
```

## Installation
Copy the built `.vst3` folder to your VST3 plugins directory:
- **Windows**: `C:\Program Files\Common Files\VST3\`
- **macOS**: `~/Library/Audio/Plug-ins/VST3/`
- **Linux**: `~/.vst3/`

## Plugin Details
- Name: mvox
- Version: 1.0.0
- Format: VST3
- Category: Fx | Dynamics | EQ
- Vendor: prodbymdotty
- Channels: Stereo

## Credits
Developed by prodbymdotty
Design inspired by xvox pro by Nuro Audio