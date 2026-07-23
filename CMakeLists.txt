cmake_minimum_required(VERSION 3.22)
project(mvox VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find JUCE - expects JUCE_PATH environment variable or cloned locally
if(NOT DEFINED JUCE_PATH)
    if(DEFINED ENV{JUCE_PATH})
        set(JUCE_PATH $ENV{JUCE_PATH})
    else()
        # Default location
        set(JUCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/JUCE")
    endif()
endif()

if(NOT EXISTS "${JUCE_PATH}/CMakeLists.txt")
    message(FATAL_ERROR "JUCE not found at ${JUCE_PATH}. "
            "Set JUCE_PATH env var or clone JUCE to that location.")
endif()

add_subdirectory(${JUCE_PATH} JUCE)

# Plugin sources
set(SOURCES
    Source/PluginProcessor.cpp
    Source/PluginEditor.cpp
    Source/UIComponents.cpp
)

set(HEADERS
    Source/PluginProcessor.h
    Source/PluginEditor.h
    Source/UIComponents.h
    Source/PluginParameters.h
)

# Create the VST3 plugin target
juce_add_plugin(mvox
    COMPANY_NAME "prodbymdotty"
    PLUGIN_NAME "mvox"
    PLUGIN_MANUFACTURER "prodbymdotty"
    PLUGIN_CODE "mvox"
    PLUGIN_DESCRIPTION "Vocal Processor Plugin"
    PLUGIN_VERSION "1.0.0"
    FORMATS VST3
    PRODUCT_NAME "mvox"
    VENDOR "prodbymdotty"
    VST3_CATEGORY "Fx"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
)

juce_generate_juce_header(mvox)

target_sources(mvox PRIVATE ${SOURCES} ${HEADERS})
target_compile_definitions(mvox PRIVATE
    JucePlugin_PluginName="mvox"
    JucePlugin_ManufacturerCode=0x70726F64
    JucePlugin_PluginCode=0x6D766F78
    JUCE_VST3_CAN_REPLACE_VST2=0
)

# Enable C++20 and optimizations
target_compile_features(mvox PRIVATE cxx_std_20)

target_link_libraries(mvox
    PRIVATE
        juce::juce_audio_basics
        juce::juce_audio_devices
        juce::juce_audio_formats
        juce::juce_audio_processors
        juce::juce_audio_utils
        juce::juce_core
        juce::juce_data_structures
        juce::juce_dsp
        juce::juce_events
        juce::juce_graphics
        juce::juce_gui_basics
        juce::juce_gui_extra
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_warning_flags
)

if(MSVC)
    target_compile_options(mvox PRIVATE /W4 /utf-8)
endif()

# Copy resources for binary
set(ASSETS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Assets")
if(EXISTS ${ASSETS_DIR})
    file(GLOB ASSETS "${ASSETS_DIR}/*")
    foreach(ASSET ${ASSETS})
        configure_file(${ASSET} ${CMAKE_CURRENT_BINARY_DIR}/Assets/${ASSET} COPYONLY)
    endforeach()
endif()

message(STATUS "mvox plugin project configured")
message(STATUS "Build VST3: cmake --build . --target mvox_VST3")
