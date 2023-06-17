/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CompressorV4AudioProcessorEditor::CompressorV4AudioProcessorEditor(CompressorV4AudioProcessor& p)
	: AudioProcessorEditor(&p), audioProcessor(p)
	, m_gainDialLabel("Gain", "Gain")
	, m_threshDiallLabel("Thresh", "Thresh")
	, m_ratioDiallLabel("Ratio", "Ratio")
	, m_attackDialLabel("Attack", "Attack")
	, m_releaseDiallLabel("Release", "Release")
	, m_outputDialLabel("MakeupGain", "MakeupGain")
	, m_drywetDialLabel("DryWet", "DryWet")

{
	startTimerHz(84);

	//Populating and setting slider properties on all sliders
	for (size_t index = 0; index < m_dials.size(); index++)
	{
		setSliderProperties(*m_dials[index]);
	}

	//Set attachements
	attachSliders();

	//MeterVisibility
	addAndMakeVisible(m_horizontalMeterL);
	addAndMakeVisible(m_horizontalMeterR);

	//Populating and setting textlabel properties on all sliders
	for (size_t index = 0; index < m_dialLabels.size(); index++)
	{
		setLabelProperties(*m_dialLabels[index]);
		m_dialLabels[index]->attachToComponent(m_dials[index], false);
	}

	//Setting to resizable
	setSize(1000, 500);
	juce::AudioProcessorEditor::setResizable(true, true);
	juce::AudioProcessorEditor::setResizeLimits(getWidth() * 0.75, getHeight() * 0.75, getWidth() * 1.25, getHeight() * 1.25);
	juce::AudioProcessorEditor::getConstrainer()->setFixedAspectRatio(2.0f);
	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
}

CompressorV4AudioProcessorEditor::~CompressorV4AudioProcessorEditor()
{
	for (auto& dial : m_dials)
	{
		dial->setLookAndFeel(nullptr);
	}

	m_dials.clear();
	m_dials.shrink_to_fit();
}

//void CompressorV4AudioProcessorEditor::timerCallBack()
//{
//	if (++framesElapsed > 100)
//	{
//		framesElapsed = 0;
//		maxRmsLeft = -100.f;
//		maxRmsRight = -100.f;
//	}
//
//	const auto leftGain = audioProcessor.getRmsLevel(0);
//	const auto rightGain = audioProcessor.getRmsLevel(1);
//	if (leftGain > maxRmsLeft)
//		maxRmsLeft = leftGain;
//	if (rightGain > maxRmsRight)
//		maxRmsRight = rightGain;
//	currentRmsValue.setText(juce::String{ leftGain, 2 } + "   " + juce::String{ rightGain, 2 }, sendNotification);
//	maxRmsValue.setText(juce::String{ maxRmsLeft, 2 } + "   " + String{ maxRmsRight, 2 }, sendNotification);
//}

void CompressorV4AudioProcessorEditor::timerCallback()
{
	m_horizontalMeterL.setLevel(audioProcessor.getRMSValue(0));
	m_horizontalMeterR.setLevel(audioProcessor.getRMSValue(1));
	m_horizontalMeterL.repaint();
	m_horizontalMeterR.repaint();
}

//==============================================================================
void CompressorV4AudioProcessorEditor::paint(juce::Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

	g.setGradientFill(juce::ColourGradient::vertical(juce::Colour::fromRGB(137, 156, 168).darker(0.75f)
	    ,getHeight()
	    ,juce::Colour::fromRGB(137, 156, 168).brighter(0.02f)
	    ,getHeight() * 0.4));

	g.fillRoundedRectangle(0, 0, getWidth(), getHeight(), 50.f);

	for (size_t index = 0; index < m_dials.size(); index++)
	{
		setSliderProperties(*m_dials[index]);
	}

	
}

void CompressorV4AudioProcessorEditor::resized()
{
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor..

		// Calculate dial sizes and margins based on editor dimensions
	auto dialSize = static_cast<int>(getWidth() * 0.13);
	auto mainLeftMargin = static_cast<int>(getWidth() * 0.03);
	auto mainRightMargin = static_cast<int>(getWidth() * 0.03);
	auto verticalMargin = static_cast<int>(getHeight() * 0.3);

	// Set bounds for each dial using calculated values
	//m_threshDial.setBounds(mainLeftMargin + dialSize + mainRightMargin
	//	, static_cast<int>(getHeight() * 0.26)
	//	, dialSize
	//	, dialSize);
	//	
	//m_outputDial.setBounds(m_threshDiallLabel.getX() + m_threshDiallLabel.getWidth() + mainRightMargin
	//	, static_cast<int>(getHeight() * 0.26)
	//	, dialSize
	//	, dialSize);

	//m_gainDial.setBounds(m_outputDialLabel.getX() + m_outputDialLabel.getWidth() + mainRightMargin
	//	,static_cast<int>(getHeight() * 0.26)
	//	, dialSize
	//	, dialSize);

	m_attackDial.setBounds(mainLeftMargin
		, 35
		, dialSize
		, dialSize);

	m_releaseDial.setBounds(mainLeftMargin
		, m_attackDial.getY() + verticalMargin,
		dialSize
		, dialSize);

	m_ratioDial.setBounds(mainLeftMargin
		, m_releaseDial.getY() + verticalMargin
		, dialSize
		, dialSize);

	//
	m_threshDial.setBounds(mainLeftMargin + dialSize + mainRightMargin*2
		, static_cast<int>(getHeight() * 0.47)
		, static_cast<int>(dialSize * 2.2)
		, static_cast<int>(dialSize * 2.2));

	m_outputDial.setBounds(m_threshDial.getX() + m_threshDial.getWidth() + mainRightMargin
		, static_cast<int>(getHeight() * 0.47)
		, static_cast<int>(dialSize * 2.2)
		, static_cast<int>(dialSize * 2.2));
	//

	m_gainDial.setBounds(m_attackDial.getX() + m_attackDial.getWidth() * 6.2
		, 30
		, dialSize
		, dialSize);

	m_drywetDial.setBounds(m_attackDial.getX() + m_attackDial.getWidth() * 6.2
		, m_releaseDial.getY() + verticalMargin
		, dialSize
		, dialSize);

	//Meter bounds
	m_horizontalMeterL.setBounds(getWidth()*0.3, 50, 400, 25);
	m_horizontalMeterR.setBounds(getWidth() *0.3, 80, 400, 25);

	////auto dialSize = getWidth() * JUCE_LIVE_CONSTANT(0.13);
	////auto mainLeftMargin = getWidth() * JUCE_LIVE_CONSTANT(0.05);
	////auto mainRightMarin = getWidth() * JUCE_LIVE_CONSTANT(0.03);
	////auto verticalMargin = getHeight() * JUCE_LIVE_CONSTANT(0.3);

	//auto dialSize = getWidth() * 0.13;
	//auto mainLeftMargin = getWidth() * 0.05;
	//auto mainRightMarin = getWidth() * 0.03;
	//auto verticalMargin = getHeight() * 0.3;

	////(int x, int y, int w, int h)
	//m_attackDial.setBounds(getWidth() * 0.03, 30, dialSize, dialSize);
	//m_releaseDial.setBounds(m_attackDial.getX(), m_attackDial.getY() + verticalMargin, dialSize, dialSize);
	//m_ratioDial.setBounds(m_releaseDial.getX(), m_releaseDial.getY() + verticalMargin, dialSize, dialSize);
	//m_threshDial.setBounds(getWidth() * 0.3, getHeight() * 0.5, dialSize * 1.5, dialSize * 1.5);
	//m_outputDial.setBounds(m_threshDial.getWidth() * 2.8, getHeight() * 0.5, dialSize * 1.5, dialSize * 1.5);
	//m_gainDial.setBounds(m_attackDial.getWidth() * 6.5, 30, dialSize, dialSize);
}
