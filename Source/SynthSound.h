/*
  ==============================================================================

    SynthSound.h
    Created: 30 Apr 2023 7:35:58pm
    Author:  david

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
class SynthSound : public juce::SynthesiserSound
{
public:
    
    virtual bool appliesToNote(int midiNoteNumber) override { return true; };
    virtual bool appliesToChannel(int midiChannel) override { return true; };

private:

};