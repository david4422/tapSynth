/*
  ==============================================================================

    SynthVoice.h
    Created: 30 Apr 2023 7:34:55pm
    Author:  david

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    SynthVoice();
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)override;
    void stopNote(float velocity, bool allowTailOff)override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample,int numSamples)override;


private:
    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;
    juce::AudioBuffer<float> synthBuffer;


    juce::dsp::Oscillator<float> osc{ [](float x) {return std::sin(x); } };
    juce::dsp::Gain<float> gain;
    bool isPrepared{ false };
};




 