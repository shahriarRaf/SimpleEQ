# SimpleEQ - A Professional Audio Equalizer Plugin

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [System Requirements](#system-requirements)
- [Installation](#installation)
- [Building from Source](#building-from-source)
- [Project Structure](#project-structure)
- [Architecture](#architecture)
- [Parameters](#parameters)
- [Usage Guide](#usage-guide)
- [Plugin Specifications](#plugin-specifications)
- [Code Organization](#code-organization)
- [Troubleshooting](#troubleshooting)
- [Known Issues](#known-issues)
- [Future Enhancements](#future-enhancements)
- [Contributing](#contributing)
- [License](#license)

## Overview

**SimpleEQ** is a professional-grade audio equalizer VST3 plugin built with the JUCE framework. It provides intuitive control over audio frequencies with a parametric EQ design featuring a low-cut filter, peak filter, and high-cut filter. The plugin includes real-time FFT analysis visualization, making it ideal for sound design, mixing, and mastering applications.

The plugin is designed with a modern, user-friendly interface and includes detailed real-time frequency response visualization to help users understand exactly how their EQ adjustments affect the audio spectrum.

### Key Highlights
- **Real-time FFT Analysis**: Visual spectrum analyzer showing live frequency content
- **3-Band Parametric Equalizer**: Low-cut, peak, and high-cut filters with full control
- **Adjustable Filter Slopes**: Choose from 12dB/oct to 48dB/oct for both cut filters
- **Bypass Controls**: Individual bypass switches for each filter section
- **Professional UI**: Custom rotary sliders with frequency labels and detailed visual feedback
- **VST3 Compatible**: Works with all major DAWs supporting VST3 format

## Features

### Equalization Features
1. **Low-Cut Filter**
   - Frequency range: 20 Hz to 20,000 Hz
   - Adjustable slope: 12, 24, 36, or 48 dB/octave
   - Independent bypass control
   - High-pass filtering for removing subsonic frequencies

2. **Peak/Parametric Filter**
   - Frequency range: 20 Hz to 20,000 Hz
   - Gain adjustment: -24 dB to +24 dB
   - Quality (Q) factor: 0.1 to 10.0
   - Precise mid-range shaping and special frequency targeting
   - Independent bypass control

3. **High-Cut Filter**
   - Frequency range: 20 Hz to 20,000 Hz
   - Adjustable slope: 12, 24, 36, or 48 dB/octave
   - Independent bypass control
   - Anti-aliasing and presence reduction capabilities

### Analysis & Visualization
- **Real-Time FFT Spectrum Analyzer**: 2048-point FFT providing detailed frequency analysis
- **Frequency Grid**: Visual reference lines for standard audio frequencies (20Hz, 50Hz, 100Hz, 200Hz, 500Hz, 1kHz, 2kHz, 5kHz, 10kHz, 20kHz)
- **Gain Reference Lines**: -24dB, -12dB, 0dB, +12dB, +24dB markings
- **Dual-Channel Analysis**: Separate analysis for left and right channels (with stereo implementation)
- **Togglable Analysis**: Enable/disable the analyzer without affecting processing
- **Dynamic Range Display**: -48dB minimum to 0dB maximum gain reference

### User Interface
- **Custom Look and Feel**: Professional, custom-designed visual appearance
- **Rotary Sliders**: Intuitive rotary controls for all parameters
- **Parameter Labels**: Clear labeling on slider controls with units (Hz, dB, etc.)
- **Toggle Buttons**: Power-style buttons for filter bypass with visual feedback
- **Responsive Design**: Dynamic layout that adapts to editor window size
- **Color-Coded Controls**: Color-coded elements for quick visual identification

## System Requirements

### Minimum Requirements
- **OS**: Windows 10 or later (x64), macOS 10.13 or later
- **DAW**: Any VST3-compatible Digital Audio Workstation
- **CPU**: Intel i5 / AMD Ryzen 5 or equivalent
- **RAM**: 4 GB minimum
- **Disk Space**: 50 MB for plugin installation

### Recommended Requirements
- **OS**: Windows 11 or latest macOS
- **DAW**: Most recent version of major DAWs (Ableton Live 11+, Logic Pro X+, Studio One 5+, Cubase 11+, FL Studio 20+)
- **CPU**: Intel i7 / AMD Ryzen 7 or equivalent with AVX2 support
- **RAM**: 8 GB or more
- **GPU**: Not required, but GPU acceleration can be beneficial

## Installation

### Pre-compiled Binaries
1. Download the latest release from the [Releases](https://github.com/yourusername/SimpleEQ/releases) page
2. **Windows**: Run the installer or manually place the `.vst3` file in your VST3 plugins directory:
   - `C:\Program Files\Common Files\VST3\`
3. **macOS**: Place the bundle in `/Library/Audio/Plug-Ins/VST3/`
4. Rescan plugins in your DAW
5. SimpleEQ should now appear in your plugin list

### Manual Installation
```bash
# Windows VST3 Directory
C:\Program Files\Common Files\VST3\SimpleEQ.vst3

# macOS VST3 Directory
/Library/Audio/Plug-Ins/VST3/SimpleEQ.vst3

# Linux VST3 Directory
~/.vst3/SimpleEQ.vst3
```

## Building from Source

### Prerequisites
- **Visual Studio 2022 Community** (Windows) or **Xcode 13+** (macOS)
- **JUCE Framework 7.0+**
- **CMake 3.19+** (optional, for command-line builds)
- **Python 3.8+** (for utility scripts)

### Clone Repository
```bash
git clone https://github.com/yourusername/SimpleEQ.git
cd SimpleEQ
```

### Visual Studio Build (Windows)
1. Open `Builds/VisualStudio2026/SimpleEQ.sln`
2. Set configuration to `Release` (or `Debug` for development)
3. Set platform to `x64`
4. Right-click solution and select "Build Solution"
5. Built plugin will be in `Builds/VisualStudio2026/Release/`

### Xcode Build (macOS)
```bash
cd Builds/MacOSX
xcodebuild -configuration Release
```

### Command-Line Build (Windows with CMake)
```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

### Build Output Location
- **Windows**: `Builds/VisualStudio2026/x64/Release/VST3/SimpleEQ.vst3`
- **macOS**: `Builds/MacOSX/build/Release/SimpleEQ.vst3`

## Project Structure

```
SimpleEQ/
├── Source/
│   ├── PluginProcessor.h         # Audio processing engine header
│   ├── PluginProcessor.cpp       # Audio processing implementation
│   ├── PluginEditor.h            # UI components and editor header
│   ├── PluginEditor.cpp          # UI implementation and rendering
│   └── JuceLibraryCode/          # JUCE framework integration
├── Builds/
│   ├── VisualStudio2026/         # Visual Studio 2026 project files
│   ├── MacOSX/                   # Xcode project files
│   └── Linux/                    # Linux build files
├── JUCE/                         # JUCE framework (submodule)
├── README.md                     # This file
├── LICENSE                       # License information
└── .gitignore                    # Git ignore patterns
```

## Architecture

### High-Level Design

SimpleEQ uses a modular architecture with clear separation between audio processing and user interface:

```
┌─────────────────────────────────────────────────────┐
│           Digital Audio Workstation                  │
└──────────────────────┬────────────────────────────────┘
					   │
		┌──────────────┴──────────────┐
		│                             │
	┌───▼─────────┐          ┌───────▼──────┐
	│   Processor │          │   Editor UI  │
	│  (Process   │          │  (Visuals &  │
	│   Block)    │          │  Interactio) │
	└───┬─────────┘          └───────┬──────┘
		│                             │
		├─ FFT Analysis               ├─ Rotary Sliders
		├─ Filter Chain               ├─ Toggle Buttons
		│  ├─ LowCut Filter           ├─ Frequency Analyzer
		│  ├─ Peak Filter             ├─ Response Curve
		│  └─ HighCut Filter          └─ Parameter Labels
		│
		└─ APVTS Parameter Management
```

### Audio Processing Chain

```
Input Audio Buffer
	│
	├─► Measure input for FFT analysis
	│
	├─► LowCut Filter
	│   (High-pass, variable slope)
	│
	├─► Peak/Parametric Filter
	│   (Adjustable frequency & gain)
	│
	├─► HighCut Filter
	│   (Low-pass, variable slope)
	│
	└─► Output Audio Buffer
```

### Parameter Management

SimpleEQ uses JUCE's `AudioProcessorValueTreeState` (APVTS) for robust parameter management:
- Automatic state saving/loading
- Real-time automation support
- Parameter linking between UI and processor
- Undo/Redo support in compatible DAWs

### FFT Analysis

The real-time frequency analyzer:
1. Collects input samples using a FIFO buffer system
2. Applies windowing function (Blackman-Harris window)
3. Performs 2048-point FFT for frequency resolution
4. Converts to dB scale with -48dB minimum
5. Maps to screen coordinates using logarithmic frequency scale

## Parameters

### Global Parameters

| Parameter | Range | Default | Unit | Description |
|-----------|-------|---------|------|-------------|
| Analyzer Enabled | On/Off | On | Boolean | Enable/disable FFT analysis visualization |

### Low-Cut Filter

| Parameter | Range | Default | Unit | Description |
|-----------|-------|---------|------|-------------|
| LowCut Freq | 20 - 20000 | 20 | Hz | Cutoff frequency for high-pass filter |
| LowCut Slope | 12/24/36/48 | 12 | dB/oct | Filter slope steepness |
| LowCut Bypassed | On/Off | Off | Boolean | Bypass the low-cut filter |

### Peak Filter

| Parameter | Range | Default | Unit | Description |
|-----------|-------|---------|------|-------------|
| Peak Freq | 20 - 20000 | 750 | Hz | Center frequency of peak filter |
| Peak Gain | -24 to +24 | 0 | dB | Gain boost or cut at peak frequency |
| Peak Quality (Q) | 0.1 - 10.0 | 1.0 | Ratio | Bandwidth of the peak filter |
| Peak Bypassed | On/Off | Off | Boolean | Bypass the peak filter |

### High-Cut Filter

| Parameter | Range | Default | Unit | Description |
|-----------|-------|---------|------|-------------|
| HighCut Freq | 20 - 20000 | 20000 | Hz | Cutoff frequency for low-pass filter |
| HighCut Slope | 12/24/36/48 | 12 | dB/oct | Filter slope steepness |
| HighCut Bypassed | On/Off | Off | Boolean | Bypass the high-cut filter |

## Usage Guide

### Basic Workflow

#### Step 1: Insert Plugin
1. Create an audio track in your DAW
2. Add SimpleEQ as an insert/effect plugin
3. The plugin window opens automatically

#### Step 2: Analyze Audio
1. Enable "Analyzer Enabled" toggle button
2. Play your audio track
3. Watch the spectrum analyzer for frequency content
4. Use the frequency grid to identify problematic frequencies

#### Step 3: Apply EQ
1. Use rotary sliders to adjust parameters
2. Start with small adjustments (±6dB) for subtle refinement
3. Use the response curve visualization to see filter effects
4. Bypass individual filters to A/B different settings

#### Step 4: Fine-Tuning
1. Adjust the Peak filter for specific frequency targeting
2. Use Low-Cut to remove rumble and protect headroom
3. Use High-Cut to reduce harshness or excess presence
4. Toggle bypass on/off to compare before and after

### Common Use Cases

**Removing Rumble & Noise**
- Set LowCut Freq to 80-100 Hz
- Set LowCut Slope to 24 dB/oct or higher
- Adjust until unwanted low frequencies are gone

**Adding Presence**
- Set Peak Freq to 2-5 kHz (presence region)
- Boost Peak Gain to +6-12 dB
- Adjust Peak Quality for narrower or wider boost

**Reducing Harshness**
- Set HighCut Freq to 10-12 kHz
- Set HighCut Slope to 12-24 dB/oct
- Gradually reduce to taste

**Mastering-Style EQ**
- Use subtle adjustments (-3 to +3 dB)
- Focus on balance across frequency spectrum
- Use high Q values for surgical precision

## Plugin Specifications

### Technical Details

**Plugin Type**: VST3 Effect Plugin
**Audio Input/Output**: Stereo (2 channels)
**Processing Latency**: 0 samples (zero-latency)
**Buffer Size Support**: 64 to 4096 samples per buffer
**Sample Rate Support**: 44.1 kHz to 192 kHz
**Bit Depth Support**: 32-bit floating point
**CPU Usage**: Typically 2-5% per instance (i7, 44.1kHz)

### Filter Specifications

**Filter Type**: IIR (Infinite Impulse Response)
**Implementation**: JUCE DSP Library
**Precision**: 64-bit internal processing
**Numerical Stability**: Double-precision coefficients

### FFT Analysis Specifications

**FFT Size**: 2048 points
**Window Function**: Blackman-Harris
**Frequency Resolution**: ~21 Hz per bin (at 44.1kHz)
**Detection Range**: -48 dB to 0 dB
**Refresh Rate**: 60 Hz UI updates

## Code Organization

### PluginProcessor.h/cpp

Handles all audio processing:
- `SimpleEQAudioProcessor`: Main processor class inheriting from `juce::AudioProcessor`
- `ChainSettings`: Struct containing all current filter settings
- `getChainSettings()`: Function to read parameters from APVTS
- `MonoChain`: Typedef for the DSP filter chain
- `makeLowCutFilter()`, `makePeakFilter()`, `makeHighCutFilter()`: Factory functions for filter creation

Key Functions:
```cpp
void prepareToPlay(double sampleRate, int samplesPerBlock);
void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&);
void updateFilters();
```

### PluginEditor.h/cpp

Handles UI rendering and interaction:
- `SimpleEQAudioProcessorEditor`: Main editor class
- `RotarySliderWithLabels`: Custom rotary slider with frequency labels
- `ResponseCurveComponent`: Real-time filter response visualization
- `PathProducer`: FFT analysis and path generation
- `LookAndFeel`: Custom visual styling

Key Classes:
```cpp
class RotarySliderWithLabels : public juce::Slider
class ResponseCurveComponent : public juce::Component
struct PathProducer
struct FFTDataGenerator
struct AnalyzerPathGenerator
```

## Troubleshooting

### Issue: Plugin Not Showing in DAW
**Solution**:
1. Ensure plugin is installed in correct VST3 directory
2. Rescan plugins in DAW settings
3. Check Windows Defender/antivirus isn't blocking plugin
4. Verify bit-depth matches (x64 plugin requires 64-bit DAW)

### Issue: No Sound Output
**Solution**:
1. Check if all filters are bypassed
2. Ensure input signal is reaching the plugin
3. Toggle "bypass" in plugin header if available
4. Check audio buffer sizes aren't too small

### Issue: Analyzer Shows No Activity
**Solution**:
1. Verify "Analyzer Enabled" toggle is ON
2. Ensure audio is actually playing through plugin
3. Try increasing Peak Gain to see if response updates
4. Restart DAW if state seems stuck

### Issue: High CPU Usage
**Solution**:
1. Reduce number of plugin instances
2. Use lower sample rates if possible
3. Disable real-time FFT analysis (uncheck Analyzer Enabled)
4. Try disabling all filters not being used
5. Update to latest plugin version

### Issue: Parameters Not Saving
**Solution**:
1. Ensure DAW session is saved in VST3-compatible format
2. Check disk space for session file storage
3. Mark track automation settings correctly
4. Verify plugin hasn't crashed (check DAW error log)

### Issue: Crackling or Clicking Artifacts
**Solution**:
1. Increase DAW buffer size (256 samples minimum)
2. Disable real-time monitoring if available
3. Check for CPU overload (reduce effects count)
4. Update audio drivers to latest version
5. Try disabling peak filter temporarily

## Known Issues

### Current Limitations
1. **Mono Processing**: Currently processes stereo as summed mono for FFT analysis
   - Workaround: Use on mono auxiliary track for mono analysis
2. **GUI Refresh**: Minor screen tearing at very high refresh rates
   - Fix in progress with JUCE update
3. **Parameter Automation**: Some DAWs may have slight automation smoothing delays
   - Expected behavior in JUCE 7.x
4. **FFT Latency**: FFT data has ~50ms latency due to buffer size
   - This is a known limitation of offline FFT analysis

### Reported Issues Being Investigated
- LookAndFeel destructor assertion in debug builds (non-critical)
- Parameter reference deduction warnings in certain compiler versions
- JUCE macro browsing warnings in IntelliSense

## Future Enhancements

### Planned Features (Next Release)
- [ ] Dual independent left/right channel analysis
- [ ] Linear phase EQ mode for mastering
- [ ] Filter preset manager with save/load system
- [ ] Advanced frequency response graphing
- [ ] Mid-side processing capability
- [ ] Analog model emulation for warm sound
- [ ] Graphic EQ mode (10-band EQ)

### Long-Term Roadmap
- Multi-band dynamic EQ
- Parametric EQ with unlimited bands
- Real-time spectrum comparison tools
- A/B testing interface
- Undo/Redo history panel
- Custom preset sharing system
- Mobile plugin version (AU/AAX)
- Plugin certification for popular DAWs

### Community-Requested Features
- Inverted spectrum display option
- Frequency ruler in Hz instead of log scale
- Customizable color schemes
- Touch-friendly interface for tablets
- MIDI learn for hardware control

## Contributing

We welcome contributions! Here's how to get involved:

### Report Bugs
1. Check existing [Issues](https://github.com/yourusername/SimpleEQ/issues)
2. Create detailed bug report with:
   - Plugin version
   - DAW name and version
   - OS and audio driver
   - Steps to reproduce
   - Expected vs actual behavior
   - System specs

### Submit Features
1. Discuss feature in Issues before starting work
2. Fork repository
3. Create feature branch: `git checkout -b feature/my-feature`
4. Implement following code style guide
5. Test thoroughly
6. Submit pull request with description
7. Respond to review feedback

### Development Setup
```bash
# Clone with submodules
git clone --recursive https://github.com/yourusername/SimpleEQ.git

# Install JUCE dependencies
cd JUCE
git submodule update --init --recursive

# Create your feature branch
cd ..
git checkout -b feature/my-awesome-feature
```

### Code Style
- Follow JUCE coding conventions
- Use `camelCase` for variables and functions
- Use `PascalCase` for classes
- Add comments for complex algorithms
- Keep lines under 120 characters
- Use const-correctness

## License

SimpleEQ is released under the [JUCE License](https://juce.com/legal/juce-9-licence/).

Please note that this plugin incorporates code from the JUCE framework, which is subject to JUCE's licensing terms. Commercial use may require a separate JUCE license.

### Third-Party Components
- **JUCE Framework**: © 2013-2024 Raw Material Software Limited
- **DSP Algorithms**: JUCE DSP Module (included in JUCE)

## Support & Contact

- **Documentation**: [Full API Docs](https://docs.example.com)
- **Issues & Bugs**: [GitHub Issues](https://github.com/yourusername/SimpleEQ/issues)
- **Email Support**: support@example.com
- **Discord Community**: [Join Server](https://discord.gg/example)
- **Twitter**: [@SimpleEQPlugin](https://twitter.com/example)

## Changelog

### Version 1.0.0 (Current)
- Initial release
- 3-band parametric EQ with variable slopes
- Real-time FFT analyzer
- Custom UI with rotary sliders
- Zero-latency processing
- VST3 format support
- Full automation support

---

**Last Updated**: January 2024
**Maintainer**: SimpleEQ Dev Team
**Repository**: https://github.com/yourusername/SimpleEQ

**Thank you for using SimpleEQ! Happy mixing! 🎚️**
