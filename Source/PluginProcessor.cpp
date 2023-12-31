/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CompressorV4AudioProcessor::CompressorV4AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    )
    , m_treeState(*this, nullptr, "PARAMETERS", createParameterLayout())

#endif
{
    //m_treeState.addParameterListener(m_gainID, this);
    //m_treeState.addParameterListener(m_threshID, this);
    //m_treeState.addParameterListener(m_ratioID, this);
    //m_treeState.addParameterListener(m_attackID, this);
    //m_treeState.addParameterListener(m_releaseID, this);
    //m_treeState.addParameterListener(m_outputID, this);

    const juce::StringArray parameterIDs = { m_gainID, m_threshID, m_ratioID, m_attackID, m_releaseID, m_outputID,m_wetdryID };
    for (const juce::String& parameterID : parameterIDs)
    {
        m_treeState.addParameterListener(parameterID, this);
    }

}

CompressorV4AudioProcessor::~CompressorV4AudioProcessor()
{
    //m_treeState.removeParameterListener(m_gainID, this);
    //m_treeState.removeParameterListener(m_threshID, this);
    //m_treeState.removeParameterListener(m_ratioID, this);
    //m_treeState.removeParameterListener(m_attackID, this);
    //m_treeState.removeParameterListener(m_releaseID, this);
    //m_treeState.removeParameterListener(m_outputID, this);

    // Remove parameter listeners
    const juce::StringArray parameterIDs = { m_gainID, m_threshID, m_ratioID, m_attackID, m_releaseID, m_outputID, m_wetdryID };
    for (const juce::String& parameterID : parameterIDs)
    {
        m_treeState.removeParameterListener(parameterID, this);
    }

}

void CompressorV4AudioProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    updateParameters();
}

juce::AudioProcessorValueTreeState::ParameterLayout CompressorV4AudioProcessor::createParameterLayout()
{
    //  Use smart pointers in ParameterLayout creation: Instead of manually creating unique pointers and pushing them into the params vector, you can use std::make_unique directly in the push_back function   //
    
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;

    juce::NormalisableRange<float> attackRange = juce::NormalisableRange<float>(0.0f, 200.0f, 1.0f);
    attackRange.setSkewForCentre(50.0f);

    juce::NormalisableRange<float> releaseRange = juce::NormalisableRange<float>(5.0f, 5000.0f, 1.0f);
    releaseRange.setSkewForCentre(160.0f);

    params.push_back(std::make_unique<juce::AudioParameterFloat>(m_gainID, m_gainName, -60.0f, 24.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(m_threshID, m_threshName, -60.0f, 10.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(m_ratioID, m_ratioName, 1.0f, 20.0f, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(m_attackID, m_attackName, attackRange, 50.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(m_releaseID, m_releaseName, releaseRange, 160.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(m_outputID, m_outputName, -60.0f, 24.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(m_wetdryID, m_wetdryID, 0, 1, 1.0f));


    return { params.begin(), params.end() };

   /* auto pInput = std::make_unique<juce::AudioParameterFloat>(m_gainID,
        m_gainName,
        -60.0f,
        24.0f,
        0.0f);

    auto pThresh = std::make_unique<juce::AudioParameterFloat>(m_threshID,
        m_threshName,
        -60.0f,
        10.0f,
        0.0f);

    auto pRatio = std::make_unique<juce::AudioParameterFloat>(m_ratioID,
        m_ratioName,
        1.0f,
        20.0f,
        1.0f);

    auto pAttack = std::make_unique<juce::AudioParameterFloat>(m_attackID,
        m_attackName,
        attackRange,
        50.0f);

    auto pRelease = std::make_unique<juce::AudioParameterFloat>(m_releaseID,
        m_releaseName,
        releaseRange,
        160.0f);

    auto pOutput = std::make_unique<juce::AudioParameterFloat>(m_outputID,
        m_outputName,
        -60.0f,
        24.0f,
        0.0f);

    params.push_back(std::move(pInput));
    params.push_back(std::move(pThresh));
    params.push_back(std::move(pRatio));
    params.push_back(std::move(pAttack));
    params.push_back(std::move(pRelease));
    params.push_back(std::move(pOutput));

    return { params.begin(), params.end() };*/
}

void CompressorV4AudioProcessor::updateParameters()
{
    //Update all DSP module parameters
    m_inputModule.setGainDecibels(m_treeState.getRawParameterValue(m_gainID)->load());
    m_compressorModule.setThreshold(m_treeState.getRawParameterValue(m_threshID)->load());
    m_compressorModule.setRatio(m_treeState.getRawParameterValue(m_ratioID)->load());
    m_compressorModule.setAttack(m_treeState.getRawParameterValue(m_attackID)->load());
    m_compressorModule.setRelease(m_treeState.getRawParameterValue(m_releaseID)->load());
    m_outputModule.setGainDecibels(m_treeState.getRawParameterValue(m_outputID)->load());
    m_drywetMix.setValue(m_treeState.getRawParameterValue(m_wetdryID)->load());

}

//void CompressorV4AudioProcessor::setThreshold(float newThresh)
//{
//    m_thresh = newThresh;
//}
//
//void CompressorV4AudioProcessor::setRatio(float newRatio)
//{
//    m_ratio = newRatio;
//}
//
//void CompressorV4AudioProcessor::setAttack(float newAttack)
//{
//    m_attack = newAttack;
//}
//
//void CompressorV4AudioProcessor::setRelease(float newRelease)
//{
//    m_release = newRelease;
//}
//
//void CompressorV4AudioProcessor::setWetDryMix(float newMix)
//{
//    m_drywetMix.setTargetValue(newMix);
//}

//float CompressorV4AudioProcessor::handleDryWetMix(float input)
//{
//    const float sampleRate = m_spec.sampleRate;
//
//        /* Initialise separate attack/release times*/
//
//
//        const auto x = input;
//
//        auto x_Uni = abs(x);
//        auto x_dB = juce::Decibels::gainToDecibels(x_Uni);
//
//        if (x_dB < -96.0)
//        {
//            x_dB = -96.0;
//        }
//
//        if (x_dB > m_thresh)
//        {
//            m_gainSC = m_thresh + (x_dB - m_thresh) / m_ratio;
//        }
//
//        else
//        {
//            m_gainSC = x_dB;
//        }
//
//        m_gainChange_dB = m_gainSC - x_dB;
//
//        if (m_gainChange_dB < m_gainSmoothPrevious)
//        {
//            m_gainSmooth = ((1 - alphaAttack) * m_gainChange_dB) + (alphaAttack * m_gainSmoothPrevious);
//            m_currentSignal = m_gainSmooth;
//        }
//
//        else
//        {
//            m_gainSmooth = ((1 - alphaRelease) * m_gainChange_dB) + (alphaRelease * m_gainSmoothPrevious);
//            m_currentSignal = m_gainSmooth;
//        }
//
//        m_gainSmoothPrevious = m_gainSmooth;
//
//        auto mix = (1.0 - m_mix.getNextValue()) * x + (x * juce::Decibels::decibelsToGain(m_gainSmooth)) * m_drywetMix.getNextValue();
//
//        return m_mix;
//}

//==============================================================================
const juce::String CompressorV4AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool CompressorV4AudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool CompressorV4AudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool CompressorV4AudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double CompressorV4AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int CompressorV4AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int CompressorV4AudioProcessor::getCurrentProgram()
{
    return 0;
}

void CompressorV4AudioProcessor::setCurrentProgram(int index)
{
}

const juce::String CompressorV4AudioProcessor::getProgramName(int index)
{
    return {};
}

void CompressorV4AudioProcessor::changeProgramName(int index, const juce::String& newName)
{
}

//==============================================================================
void CompressorV4AudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    // Initialize spec for dsp modules
    m_spec.maximumBlockSize = samplesPerBlock;
    m_spec.sampleRate = sampleRate;
    m_spec.numChannels = getTotalNumOutputChannels();

    // Prepare DSP modules for processing
    m_drywetMix.reset(m_spec.sampleRate,0.02f);
    m_inputModule.prepare(m_spec);
    m_outputModule.prepare(m_spec);
    m_compressorModule.prepare(m_spec);
    m_drywetModule.prepare(m_spec);

    m_inputModule.setRampDurationSeconds(0.05);//Smooth change from parameter
    m_outputModule.setRampDurationSeconds(0.05);//Smooth change from parameter
    m_drywetModule.setWetMixProportion(0.01);//Smooth change from parameter

    updateParameters();
}

void CompressorV4AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool CompressorV4AudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif

void CompressorV4AudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    //Get RMS value for visualization level meter
    m_rmsvalueLeft = juce::Decibels::gainToDecibels( buffer.getRMSLevel(0, 0, buffer.getNumSamples()));
    m_rmsvalueRight = juce::Decibels::gainToDecibels( buffer.getRMSLevel(1, 0, buffer.getNumSamples()));
    buffer.getRMSLevel(1,0,buffer.getNumSamples());

    juce::dsp::AudioBlock<float> block{ buffer };

    //Process DSP modules
    m_inputModule.process(juce::dsp::ProcessContextReplacing<float>(block));
    m_compressorModule.process(juce::dsp::ProcessContextReplacing<float>(block));
    m_outputModule.process(juce::dsp::ProcessContextReplacing<float>(block));   

    for (int channel = 0; channel < getNumInputChannels(); ++channel)
    {
        float* channelData = buffer.getWritePointer(channel);
        const float* inputData = buffer.getReadPointer(channel);

        for (int i = 0; i < buffer.getNumSamples(); ++i)
            channelData[i] = (inputData[i] * (1.0f - m_drywetMix) + convolvedData[i] * m_drywetMix);
        channelData[i] = (inputData[i] * (1 - m_drywetMix->get())) + (wetSignal * (0 + m_drywetMix->get()));
    }

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);

        for (int sample = 0; sample < getTotalNumInputChannels(); ++sample)
        {

            drySignal = channelData[sample];
            wetSignal = drySignal * gainReduction;

            if (m_drywetMix->get() == 0)
            {
                channelData[sample] = drySignal;
            }
            else if (m_drywetMix->get() == 1)
            {
                channelData[sample] = wetSignal;
            }
            else
            {
                channelData[sample] = (drySignal * (1 - m_drywetMix->get())) + (wetSignal * (0 + m_drywetMix->get()));
            }
        }
    }


}

//==============================================================================
bool CompressorV4AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* CompressorV4AudioProcessor::createEditor()
{
    return new CompressorV4AudioProcessorEditor(*this);
    //return new juce::GenericAudioProcessorEditor (*this);
}

//==============================================================================
void CompressorV4AudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

    //save parameters
    juce::MemoryOutputStream stream(destData, false);
    m_treeState.state.writeToStream(stream);
}

void CompressorV4AudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

    auto tree = juce::ValueTree::readFromData(data, size_t(sizeInBytes));

    if (tree.isValid())
    {
        m_treeState.state = tree;
    }
}

float CompressorV4AudioProcessor::getRMSValue(const int channel) const
{
    jassert(channel == 0 || 1);
    if (channel == 0)
        return m_rmsvalueLeft;
    if (channel == 1)
        return m_rmsvalueRight;
    return 0.f;
}


//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CompressorV4AudioProcessor();
}
