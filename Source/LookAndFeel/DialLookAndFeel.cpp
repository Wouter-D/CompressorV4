/*
  ==============================================================================

    DialLookAndFeel.cpp
    Created: 16 Jun 2023 7:22:40pm
    Author:  Wouter Duprez

  ==============================================================================
*/

//Courtesy of the AudioPluginCodersGuild

#include "DialLookAndFeel.h"

// Constructor for the DialStyle class
DialLookAndFeel::DialLookAndFeel()
{

}

// Override the drawRotarySlider function to provide custom drawing for rotary sliders
void DialLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
    const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider)
{
    ///** Define color variables for customization. */
 

    //auto dialBounds = juce::Rectangle<int>(x, y, width, height).toFloat();
    //auto centre = dialBounds.getCentre();
    //auto fullRadius = juce::jmin(dialBounds.getWidth() / 1.95f, dialBounds.getHeight() / 1.95f);

    //m_sliderWidth = width;

    ///** Dot color*/
    //g.setColour(juce::Colours::whitesmoke.withAlpha(0.5f));
    //centre = dialBounds.getCentre();

    ///** Draw dots */
    ///** How many dots to draw, works well as num dial intervals + 1 for small ranges, e.g. [0 - 10]*/
    //for (int i = 0; i < 11; ++i)
    //{
    //    auto dotSize = width * 0.015;

    //    /** IF you change the number of dots, do i / (num dots - 1) */
    //    const auto angle = juce::jmap(i / 10.0f, rotaryStartAngle, rotaryEndAngle);

    //    /** Dot distance from slider center */
    //    const auto point = centre.getPointOnCircumference(fullRadius - width * 0.06f, angle);

    //    /** Dot thickness*/
    //    g.fillEllipse(point.getX() - 3, point.getY() - 3, dotSize, dotSize);
    //}

    //fullRadius -= 14.0f;

    //auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

    ///** Track thickness*/
    //float lineWidthMultiplier = width * 0.035;
    //auto lineWidth = juce::jmin(lineWidthMultiplier, fullRadius * 0.5f);
    //auto arcRadius = fullRadius - lineWidth * 2.25;

    //juce::Path backgroundArc;
    //backgroundArc.addCentredArc
    //(
    //    dialBounds.getCentreX(),
    //    dialBounds.getCentreY(),
    //    arcRadius,
    //    arcRadius,
    //    0.0f,
    //    rotaryStartAngle,
    //    rotaryEndAngle,
    //    true
    //);

    ///** Dial fill track color*/
    //g.setColour(outlineColor);
    //g.strokePath(backgroundArc, juce::PathStrokeType(lineWidth, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

    //auto dialRadius = std::max(fullRadius - 4.0f * lineWidth, 10.0f);
    //{
    //    juce::Graphics::ScopedSaveState saved(g);
    //    if (slider.isEnabled())
    //    {
    //        juce::ColourGradient fillGradient
    //        (
    //            brighterColor,
    //            centre.getX() + lineWidth * 0.9f,
    //            centre.getY() - lineWidth * 4.0f,
    //            mainColor,
    //            centre.getX() + dialRadius,
    //            centre.getY() + dialRadius,
    //            true
    //        );

    //        /** Dial center color gradient*/
    //        g.setGradientFill(fillGradient);
    //    }

    //    g.fillEllipse(centre.getX() - dialRadius, centre.getY() - dialRadius, dialRadius * 2.0f, dialRadius * 2.0f);
    //}

    ////dialRadius = std:: max (dialRadius - 4.0f, 10.0f);

    ///** Dial outline color*/
    //g.setColour(dialOutlineColor);

    //auto scale = 2.0f;

    ///** Dial outline thickness*/
    //g.drawEllipse(centre.getX() - dialRadius, centre.getY() - dialRadius, dialRadius * scale, dialRadius * scale, 4.5f);

    ///** Fill Math*/
    //juce::Path dialValueTrack;
    //dialValueTrack.addCentredArc
    //(
    //    dialBounds.getCentreX(),
    //    dialBounds.getCentreY(),
    //    arcRadius,
    //    arcRadius,
    //    0.0f,
    //    rotaryStartAngle,
    //    toAngle,
    //    true
    //);

    ///** Value track fill color*/
    //g.setColour(fillColor);
    //g.strokePath(dialValueTrack, juce::PathStrokeType(lineWidth, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

    ///** Dial tick color*/
    //g.setColour(dialOutlineColor);
    //juce::Path dialTick;
    //dialTick.startNewSubPath(centre.getPointOnCircumference(dialRadius - lineWidth, toAngle));

    ///** Dial tick length*/
    //dialTick.lineTo(centre.getPointOnCircumference((dialRadius - lineWidth) * 0.6f, toAngle));

    ///** Dial tick thickness*/
    //g.strokePath(dialTick, juce::PathStrokeType(lineWidth * 0.75, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));


    //// Calculate the threshold value in dB (replace 0 with the actual threshold value)
    //float thresholdDB = 0.0f;

    //// Get the current dB value (replace outputDB with the actual output dB value)
    //float outputDB = 0.0f;

    //// Calculate the opacity based on the output dB compared to the threshold
    //float opacity = juce::jlimit(0.0f, 1.0f, (outputDB - thresholdDB) / (thresholdDB - 0.0f));

    //// Calculate the color based on the opacity
    //juce::Colour glowColor = juce::Colour::fromRGBA(255, 0, 0, static_cast<int>(opacity * 255));

    //// Draw the slider
    //juce::LookAndFeel_V4::drawRotarySlider(g, x, y, width, height, sliderPos, rotaryStartAngle, rotaryEndAngle, slider);

    //// Calculate the outer perimeter rectangle
    //juce::Rectangle<int> outerRect(x, y, width, height);

    //// Calculate the inner perimeter rectangle
    //int innerSize = 5; // Adjust the size as needed
    //juce::Rectangle<int> innerRect = outerRect.reduced(innerSize);

    //// Set the glow color
    //g.setColour(glowColor);

    float diameter = fmin(width, height) * .7;
    float radius = diameter * 0.5;
    float centerX = x + width * 0.5;
    float centerY = y + height * 0.5;
    float rx = centerX - radius;
    float ry = centerY - radius;
    float angle = rotaryStartAngle + (sliderPos * (rotaryEndAngle - rotaryStartAngle));

    juce::Rectangle<float> dialArea(rx, ry, diameter, diameter);
    // g.fillAll(juce::Colours::antiquewhite);
    g.setColour(juce::Colours::antiquewhite); //center
    g.fillEllipse(dialArea);

    g.setColour(juce::Colours::antiquewhite.withAlpha(0.8f).darker(0.8f)); //outline
    g.drawEllipse(rx, ry, diameter, diameter, 10.f);

    juce::Path dialTick;
    g.setColour(juce::Colours::whitesmoke.darker(0.5)); //tick color
    dialTick.addRectangle(0, -radius + 6, 5.f, radius * 0.5);
    g.fillPath(dialTick, juce::AffineTransform::rotation(angle).translated(centerX, centerY));

    const auto outlineColor = slider.findColour(juce::Slider::rotarySliderOutlineColourId);
    const auto fillColor = juce::Colour::fromRGB(125, 154, 208).withAlpha(0.9f);
    const auto mainColor = slider.findColour(juce::Slider::ColourIds::thumbColourId);
    const auto brighterColor = slider.findColour(juce::Slider::ColourIds::thumbColourId).brighter(0.1f);
    const auto trackColor = slider.findColour(juce::Slider::ColourIds::trackColourId);
    const auto dialOutlineColor = slider.findColour(juce::Slider::backgroundColourId);
}

void DialLookAndFeel::drawLabel(juce::Graphics& g, juce::Label& label)
{
    g.fillAll(label.findColour(juce::Label::backgroundColourId));

    label.setEditable(true);

    if (!label.isBeingEdited())
    {
        auto alpha = label.isEnabled() ? 1.0f : 0.5f;
        const juce::Font font(juce::Font("Helvetica", m_sliderWidth * 0.1, juce::Font::FontStyleFlags::bold));

        g.setColour(label.findColour(juce::Label::textColourId).withMultipliedAlpha(alpha));
        g.setFont(font);

        auto textArea = getLabelBorderSize(label).subtractedFrom(label.getLocalBounds());

        g.drawFittedText(label.getText(), textArea, label.getJustificationType(),
            juce::jmax(1, (int)((float)textArea.getHeight() / font.getHeight())),
            label.getMinimumHorizontalScale());

        g.setColour(label.findColour(juce::Label::outlineColourId).withMultipliedAlpha(alpha));
    }

    else if (label.isEnabled())
    {
        g.setColour(label.findColour(juce::Label::outlineColourId));
    }

    g.drawRect(label.getLocalBounds());
}


