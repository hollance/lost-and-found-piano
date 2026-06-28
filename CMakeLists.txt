cmake_minimum_required(VERSION 3.22)

set(CMAKE_OSX_DEPLOYMENT_TARGET "10.13" CACHE STRING "Minimum OS X deployment target")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

project(LostAndFoundPiano VERSION 1.0.1)

option(JUCE_ENABLE_MODULE_SOURCE_GROUPS "Enable Module Source Groups" ON)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 20)

# generate PDB/dSYM files for the Release build
if(MSVC)
    add_compile_options("$<$<NOT:$<CONFIG:Debug>>:/Zi>")
    add_link_options("$<$<NOT:$<CONFIG:Debug>>:/DEBUG>")
    add_link_options("$<$<NOT:$<CONFIG:Debug>>:/OPT:REF>")
    add_link_options("$<$<NOT:$<CONFIG:Debug>>:/OPT:ICF>")
elif(APPLE)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g")
    set(CMAKE_XCODE_ATTRIBUTE_GCC_GENERATE_DEBUGGING_SYMBOLS[variant=Release] "YES")
    set(CMAKE_XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT[variant=Release] "dwarf-with-dsym")
    set(CMAKE_XCODE_ATTRIBUTE_DEPLOYMENT_POSTPROCESSING[variant=Release] "YES")
else()
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g")
endif()

add_subdirectory(libs/JUCE)

juce_add_plugin(${PROJECT_NAME}
    COMPANY_NAME "Lost N' Found"
    PLUGIN_NAME "Piano"
    PLUGIN_MANUFACTURER_CODE Dvbl
    PLUGIN_CODE Lafp
    BUNDLE_ID "blog.audiodev.lostandfound.piano"
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    FORMATS AU VST3 LV2
    PRODUCT_NAME "Lost N' Found Piano"
    VST3_AUTO_MANIFEST FALSE
    LV2URI urn:audiodevblog:lostandfound:Piano
)

juce_generate_juce_header(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    src/dsp/mdaAmbience.cpp
    src/dsp/mdaAmbience.h
    src/dsp/mdaEPiano.cpp
    src/dsp/mdaEPiano.h
    src/dsp/mdaEPianoData.h
    src/dsp/mdaPiano.cpp
    src/dsp/mdaPiano.h
    src/dsp/mdaPianoData.h
    src/dsp/SharedDefs.h
    src/gui/EditorView.cpp
    src/gui/EditorView.h
    src/gui/GroupView.h
    src/gui/LookAndFeel.cpp
    src/gui/LookAndFeel.h
    src/gui/MidiKeyboardComponent.cpp
    src/gui/MidiKeyboardComponent.h
    src/gui/RadioButtonAttachment.cpp
    src/gui/RadioButtonAttachment.h
    src/gui/RotaryKnob.cpp
    src/gui/RotaryKnob.h
    src/gui/SelectionBar.h
    src/Parameters.h
    src/Parameters.cpp
    src/PluginEditor.cpp
    src/PluginEditor.h
    src/PluginProcessor.cpp
    src/PluginProcessor.h
)

source_group(Sources src)
source_group(Sources/DSP src/dsp)
source_group(Sources/GUI src/gui)

target_include_directories(${PROJECT_NAME} PRIVATE src)

juce_add_binary_data(BinaryData SOURCES
    fonts/GoudyBookletter1911.otf
    fonts/VictorMono-Regular.ttf
    images/Knob.svg
)

target_compile_definitions(${PROJECT_NAME} PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_REPORT_APP_USAGE=0
    JUCE_MODAL_LOOPS_PERMITTED=0
    DONT_SET_USING_JUCE_NAMESPACE=1
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        BinaryData
        juce::juce_animation
        juce::juce_audio_utils
        juce::juce_dsp
    PUBLIC
        juce::juce_recommended_warning_flags
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
)
