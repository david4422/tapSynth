/*
  ==============================================================================

    SynthVoice.cpp
    Created: 30 Apr 2023 7:34:55pm
    Author:  david

  ==============================================================================
*/

#include "SynthVoice.h"


SynthVoice::SynthVoice()
{
    
    
}

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}
void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    //osc.setFrequency(juce::MidiMessage::getMidiNoteInHertz (midiNoteNumber));

    adsr.noteOn();
}
void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    adsr.noteOff();

    if (!allowTailOff || !adsr.isActive())
    {
        clearCurrentNote();
    }

}
void  SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{

}
void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{

}
void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    adsr.setSampleRate(sampleRate);

    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = outputChannels;


    osc.prepare(spec);
    gain.prepare(spec);
    osc.setFrequency(440);

    gain.setGainLinear(0.7f);

    adsrParams.attack = 0.8;
    adsrParams.decay = 0.8;
    adsrParams.sustain = 1;
    adsrParams.release = 1.5;

    adsr.setParameters(adsrParams);

    isPrepared = true;
}
void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{


    jassert(isPrepared);


   if(! isVoiceActive())
        return;

    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer.clear();

    juce::dsp::AudioBlock<float> audioBlock{ synthBuffer };
    juce::dsp::ProcessContextReplacing<float> context(audioBlock);
    osc.process(context);
    gain.process(context);

    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());

    if (startSample != 0)
        jassertfalse;


    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);

        if (!adsr.isActive())
            clearCurrentNote();

    }
    
}