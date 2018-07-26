#include "LookAndFeel.h"

/*
CloudBurst DAPP
Copyright (C) 2018  CurbShifter

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

void CloudBurstLookAndFeel::Init()
{
	setColour(TreeView::selectedItemBackgroundColourId, Colour(0xff83acf0));

	setColour(TextEditor::highlightColourId, Colour(0xff83acf0));
	setColour(TextEditor::highlightedTextColourId, Colour(0xff141305));
	setColour(TextEditor::backgroundColourId, Colour(0xfff6f6f6));
	setColour(TextEditor::textColourId, Colours::black);
	setColour(TextEditor::focusedOutlineColourId, Colour(0xffe1e1e1));
	setColour(TextEditor::shadowColourId, Colour(0xffbbbbbb));

	setColour(ListBox::outlineColourId, Colour(0xffe4e4e4));
	setColour(ListBox::backgroundColourId, Colour(0xbefdfdfd));

	setColour(Label::textColourId, Colour(0xff14181A));

	setColour(juce::TextButton::buttonOnColourId, Colour(0x7f00579d));
	setColour(juce::TextButton::buttonColourId, Colour(0xff00579d));
	setColour(juce::TextButton::textColourOnId, Colour(0xffffffff));
	setColour(juce::TextButton::textColourOffId, Colour(0xffffffff));

	setColour(ProgressBar::foregroundColourId, Colour(0xfface1ef));
		
	setColour(ComboBox::outlineColourId, Colour(0xffc4c4c4));
	setColour(PopupMenu::textColourId, Colour(0xff4b4b4b));
	setColour(PopupMenu::highlightedBackgroundColourId, Colour(0xffcbcbcb));
	setColour(PopupMenu::highlightedTextColourId, Colour(0xff4b4b4b));

	setColour(ProgressBar::backgroundColourId, Colour(0xbefdfdfd));
	setColour(ProgressBar::foregroundColourId, Colour(0xff4d90fe));
}
void CloudBurstLookAndFeel::setFont(Font f)
{
	brFont = f.withHeight(20);
}

void CloudBurstLookAndFeel::setFontBold(Font f)
{
	brFontBold = f.withHeight(20);
}

void CloudBurstLookAndFeel::setFontAlt(Font f)
{
	brFontAlt = f.withHeight(20);
}

Typeface::Ptr 	CloudBurstLookAndFeel::getTypefaceForFont(const Font &)
{
	return brFont.getTypeface();
}

void CloudBurstLookAndFeel::drawDocumentWindowTitleBar(DocumentWindow& window, Graphics& g,
	int w, int h, int titleSpaceX, int titleSpaceW,
	const Image* icon, bool drawTitleTextOnLeft)
{
	const bool isActive = window.isActiveWindow();
	g.setGradientFill(ColourGradient(Colour(0xfff3f3f3),
		0.0f, (float)h/2.f,
		Colours::whitesmoke,
		0.0f, (float)h, false));
	g.fillAll();

	Font font(h * 0.65f, Font::bold);
	g.setFont(font);

	int textW = font.getStringWidth(window.getName());
	int iconW = 0;
	int iconH = 0;

	if (icon != nullptr)
	{
		iconH = (int)font.getHeight();
		iconW = icon->getWidth() * iconH / icon->getHeight() + 4;
	}

	textW = jmin(titleSpaceW, textW + iconW);
	int textX = drawTitleTextOnLeft ? titleSpaceX
		: jmax(titleSpaceX, (w - textW) / 2);

	if (textX + textW > titleSpaceX + titleSpaceW)
		textX = titleSpaceX + titleSpaceW - textW;

	if (icon != nullptr)
	{
		g.setOpacity(isActive ? 1.0f : 0.6f);
		g.drawImageWithin(*icon, textX, (h - iconH) / 2, iconW, iconH,
			RectanglePlacement::centred, false);
		textX += iconW;
		textW -= iconW;
	}

	if (window.isColourSpecified(DocumentWindow::textColourId) || isColourSpecified(DocumentWindow::textColourId))
		g.setColour(window.findColour(DocumentWindow::textColourId));
	else
		g.setColour(window.getBackgroundColour().contrasting(isActive ? 0.7f : 0.4f));

	g.drawText(window.getName().toUTF8(), textX, 0, textW, h, Justification::centredLeft, true);
}

//==============================================================================
class CloudBurstLookAndFeel::OSXWindowButton : public Button
{
public:
	OSXWindowButton(const String& name, Colour col,
		const Path& normalShape_,
		const Path& toggledShape_) noexcept
		: Button(name),
		colour(col),
		normalShape(normalShape_),
		toggledShape(toggledShape_)
	{
	}

	//==============================================================================
	void paintButton(Graphics& g, bool isMouseOverButton, bool isButtonDown) override
	{
		float alpha = isMouseOverButton ? (isButtonDown ? 1.0f : 0.8f) : 0.f;

		if (!isEnabled())
			alpha *= 0.5f;

		const float size = (float)jmin<int>(getWidth(), getHeight(), 12);
		const float offsetX = (getWidth() - size) / 2.f;
		const float offsetY = (getHeight() - size) / 2.f;

		const float strokeWidth = 1.f;
		g.setColour(colour.withBrightness(0.2f));
		g.drawEllipse(offsetX + (strokeWidth / 2.f), offsetY + (strokeWidth / 2.f), size - strokeWidth, size - strokeWidth, strokeWidth);

		g.setColour(colour);
		g.fillEllipse(offsetX, offsetY, size, size);

		Path& p = getToggleState() ? toggledShape : normalShape;

		const float sizePath = (float)jmin<int>(getWidth(), getHeight(), 7);
		const float offsetXPath = (getWidth() - sizePath) / 2.f;
		const float offsetYPath = (getHeight() - sizePath) / 2.f;

		const AffineTransform t(p.getTransformToScaleToFit(offsetXPath, offsetYPath, sizePath, sizePath, true));

		g.setColour(Colours::black.withAlpha(alpha * 0.6f));
		g.fillPath(p, t);
	}

private:
	Colour colour;
	Path normalShape, toggledShape;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OSXWindowButton)
};

Button* CloudBurstLookAndFeel::createDocumentWindowButton(int buttonType)
{
	Path shape;
	const float crossThickness = 0.25f;

	if (buttonType == DocumentWindow::closeButton)
	{
		shape.addLineSegment(Line<float>(0.0f, 0.0f, 1.0f, 1.0f), crossThickness * 1.4f);
		shape.addLineSegment(Line<float>(1.0f, 0.0f, 0.0f, 1.0f), crossThickness * 1.4f);

		return new OSXWindowButton("close", Colour(0xffff5d56), shape, shape);
	}

	if (buttonType == DocumentWindow::minimiseButton)
	{
		shape.addLineSegment(Line<float>(0.0f, 0.5f, 1.0f, 0.5f), crossThickness);

		return new OSXWindowButton("minimise", Colour(0xffffbd35), shape, shape);
	}

	if (buttonType == DocumentWindow::maximiseButton)
	{
		const float scale = 1.f;

		shape.addTriangle(0.f, 0.2f * scale, 0.f, 1.f * scale, 0.8f * scale, 1.f * scale);
		shape.addTriangle(0.2f * scale, 0.f, 1.f * scale, 0.f, 1.f * scale, 0.8f * scale);

		return new OSXWindowButton("maximise", Colour(0xff00cc4b), shape, shape);
	}

	jassertfalse;
	return nullptr;
}

void CloudBurstLookAndFeel::drawLabel(Graphics& g, Label& label)
{
	g.fillAll(label.findColour(Label::backgroundColourId));

	if (!label.isBeingEdited())
	{
		const float alpha = label.isEnabled() ? 1.0f : 0.5f;
		const Font font(getLabelFont(label));
		
		g.setColour(label.findColour(Label::textColourId).withMultipliedAlpha(alpha));
		
		g.setFont(brFont.withHeight(font.getHeight()));

		juce::Rectangle<int> textArea(label.getBorderSize().subtractedFrom(label.getLocalBounds()));
		g.drawFittedText(label.getText(), textArea, label.getJustificationType(),
			juce::jmax(1, (int)(textArea.getHeight() / g.getCurrentFont().getHeight())),
			label.getMinimumHorizontalScale());

		g.setColour(label.findColour(Label::outlineColourId).withMultipliedAlpha(alpha));
	}
	else if (label.isEnabled())
	{
		g.setColour(label.findColour(Label::outlineColourId));
	}

	g.drawRect(label.getLocalBounds());
}

void CloudBurstLookAndFeel::drawTooltip(Graphics& g, const String& text, int width, int height)
{
	g.fillAll(findColour(TooltipWindow::backgroundColourId));
#if ! JUCE_MAC // The mac windows already have a non-optional 1 pix outline, so don't double it here..
	g.setColour(findColour(TooltipWindow::outlineColourId));
	g.drawRect(0, 0, width, height+30, 1);
#endif
	const float tooltipFontSize = 13.0f;
	g.setFont(Font(tooltipFontSize, Font::bold));
	g.setColour(findColour(TooltipWindow::textColourId));
	g.drawMultiLineText(text, 4, 12, (int)(width - 8.f));
}

void CloudBurstLookAndFeel::drawRoundThumb (Graphics& g, const float x, const float y,
                        const float diameter, const Colour& colour, float outlineThickness)
{
	const juce::Rectangle<float> a(x, y, diameter, diameter);
    const float halfThickness = outlineThickness * 0.5f;

    Path p;
    p.addEllipse (x + halfThickness, y + halfThickness, diameter - outlineThickness, diameter - outlineThickness);

    const DropShadow ds (Colours::black, 1, Point<int> (0, 0));
    ds.drawForPath (g, p);

    g.setColour (colour);
    g.fillPath (p);

    g.setColour (colour.brighter());
    g.strokePath (p, PathStrokeType (outlineThickness));
}

void CloudBurstLookAndFeel::drawButtonText(Graphics& g, TextButton& button, bool /*isMouseOverButton*/, bool /*isButtonDown*/)
{
	float fontHeight = jmin<float>(button.getHeight() - 4.f, 16.f);
	g.setFont(brFontBold.withHeight(fontHeight));


	g.setColour(button.findColour(button.getToggleState() ? TextButton::textColourOnId
		: TextButton::textColourOffId)
		.withMultipliedAlpha(button.isEnabled() ? 1.0f : 0.5f));

	String txt = button.getButtonText();
	String name = button.getName();

	g.drawFittedText(txt, 2, 0, button.getWidth() - 4, button.getHeight(), Justification::centred, 2);
}

void CloudBurstLookAndFeel::drawButtonBackground (Graphics& g, Button& button, const Colour& /*backgroundColour*/, bool isMouseOverButton, bool isButtonDown)
{
	const Colour mainColour(button.findColour(button.getToggleState() ? TextButton::buttonOnColourId : TextButton::buttonColourId));
	Colour baseColour(mainColour.withMultipliedSaturation(button.hasKeyboardFocus(true) ? 1.3f : 0.9f).withMultipliedAlpha (button.isEnabled() ? 0.9f : 0.5f));

	if ((isButtonDown || isMouseOverButton) && baseColour.getAlpha() > 0)
        baseColour = baseColour.contrasting (isButtonDown ? 0.2f : 0.1f);

    const float width  = button.getWidth() - 1.0f;
    const float height = button.getHeight() - 1.0f;

    if (width > 0 && height > 0)
    {
		const float spacing = 0.f;

        Path outline;
		outline.addRoundedRectangle(0.5f + spacing, 0.5f + spacing, width - (spacing*2.f), height - (spacing*2.f), 3);
        const Colour outlineColour (button.findColour (button.getToggleState() ? TextButton::textColourOnId : TextButton::textColourOffId));

        g.setColour (baseColour);
        g.fillPath (outline);

		if ((isMouseOverButton && mainColour.getAlpha() <= 0) || button.getToggleState())
		{
			float fontHeight = jmin<float>(button.getHeight() - 4.f, 16.f);
			g.setFont(brFontBold.withHeight(fontHeight));
			String txt = button.getButtonText();
			String name = button.getName();
			float textWidth = (float)g.getCurrentFont().getStringWidth(txt);

			g.setColour(button.findColour(button.getToggleState() ? TextButton::textColourOnId
				: TextButton::textColourOffId)
				.withMultipliedAlpha(button.isEnabled() ? 1.0f : 0.5f));


			for (int i = 0; i < (button.getToggleState() ? 2 : 1); i++)
			{
				g.drawHorizontalLine((int)(height - 3 + i), ((button.getWidth() - textWidth) / 2.f), ((button.getWidth() - textWidth) / 2.f) + textWidth);
			}
		}
    }
}

void CloudBurstLookAndFeel::drawTickBox(Graphics& g, Component& component,
                    float x, float y, float w, float h,
                    bool ticked,
                    bool /*isEnabled*/,
                    bool /*isMouseOverButton*/,
                    bool /*isButtonDown*/)
{
	g.setColour(Colours::white);
	g.fillRect(juce::Rectangle<float>(x, y, w, h).withSizeKeepingCentre(w - 2, h - 2));

	g.setColour(Colour(Colours::grey).withAlpha(0.8f).withMultipliedAlpha(component.isEnabled() ? 1.0f : 0.5f));
	g.drawRect(juce::Rectangle<float>(x, y, w, h).withSizeKeepingCentre(w-2,h-2));

    if (ticked)
    {
		const Path tick(LookAndFeel_V2::getTickShape(w*0.8f));
		g.setColour(Colour(Colours::black).withAlpha(0.9f).withMultipliedAlpha(component.isEnabled() ? 1.0f : 0.5f));
        const AffineTransform trans (AffineTransform::translation (x - (w/2) + 5, y + (h/6) - 3)); // //.//scale (w / scale, h / scale)
        g.fillPath (tick, trans);
    }
}

void CloudBurstLookAndFeel::drawLinearSliderThumb (Graphics& g, int x, int y, int width, int height,
                            float sliderPos, float minSliderPos, float maxSliderPos,
                            const Slider::SliderStyle style, Slider& slider)
{
    const float sliderRadius = (float) (getSliderThumbRadius (slider) - 2);

    bool isDownOrDragging = slider.isEnabled() && (slider.isMouseOverOrDragging() || slider.isMouseButtonDown());
    Colour knobColour (slider.findColour (Slider::thumbColourId).withMultipliedSaturation ((slider.hasKeyboardFocus (false) || isDownOrDragging) ? 1.3f : 0.9f)
                        .withMultipliedAlpha (slider.isEnabled() ? 1.0f : 0.7f));

    if (style == Slider::LinearHorizontal || style == Slider::LinearVertical)
    {
        float kx, ky;

        if (style == Slider::LinearVertical)
        {
            kx = x + width * 0.5f;
            ky = sliderPos;
        }
        else
        {
            kx = sliderPos;
            ky = y + height * 0.5f;
        }

        const float outlineThickness = slider.isEnabled() ? 0.8f : 0.3f;

        drawRoundThumb (g,
                        kx - sliderRadius,
                        ky - sliderRadius,
                        sliderRadius * 2.0f,
                        knobColour, outlineThickness);
    }
    else
    {
        // Just call the base class for the demo
        LookAndFeel_V2::drawLinearSliderThumb (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
    }
}

void CloudBurstLookAndFeel::drawLinearSlider (Graphics& g, int x, int y, int width, int height,
                        float sliderPos, float minSliderPos, float maxSliderPos,
                        const Slider::SliderStyle style, Slider& slider)
{
    g.fillAll (slider.findColour (Slider::backgroundColourId));

    if (style == Slider::LinearBar || style == Slider::LinearBarVertical)
    {
        const float fx = (float) x, fy = (float) y, fw = (float) width, fh = (float) height;

        Path p;

        if (style == Slider::LinearBarVertical)
            p.addRectangle (fx, sliderPos, fw, 1.0f + fh - sliderPos);
        else
            p.addRectangle (fx, fy, sliderPos - fx, fh);


        Colour baseColour (slider.findColour (Slider::rotarySliderFillColourId)
                            .withMultipliedSaturation (slider.isEnabled() ? 1.0f : 0.5f)
                            .withMultipliedAlpha (0.8f));

        g.setColour (baseColour);
        g.fillPath (p);

        const float lineThickness = jmin (15.0f, jmin (width, height) * 0.45f) * 0.1f;
        g.drawRect (slider.getLocalBounds().toFloat(), lineThickness);
    }
    else
    {
        drawLinearSliderBackground (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
        drawLinearSliderThumb (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
    }
}

void CloudBurstLookAndFeel::drawLinearSliderBackground (Graphics& g, int x, int y, int width, int height,
                                    float /*sliderPos*/,
                                    float /*minSliderPos*/,
                                    float /*maxSliderPos*/,
                                    const Slider::SliderStyle /*style*/, Slider& slider)
{
    const float sliderRadius = getSliderThumbRadius (slider) - 5.0f;
    Path on, off;

    if (slider.isHorizontal())
    {
        const float iy = x + width * 0.5f - sliderRadius * 0.5f;
		juce::Rectangle<float> r(x - sliderRadius * 0.5f, iy, width + sliderRadius, sliderRadius);
        const float onW = r.getWidth() * ((float) slider.valueToProportionOfLength (slider.getValue()));

        on.addRectangle (r.removeFromLeft (onW));
        off.addRectangle (r);
    }
    else
    {
        const float ix = x + width * 0.5f - sliderRadius * 0.5f;
		juce::Rectangle<float> r(ix, y - sliderRadius * 0.5f, sliderRadius, height + sliderRadius);
        const float onH = r.getHeight() * ((float) slider.valueToProportionOfLength (slider.getValue()));

        on.addRectangle (r.removeFromBottom (onH));
        off.addRectangle (r);
    }

    g.setColour (slider.findColour (Slider::rotarySliderFillColourId));
    g.fillPath (on);

    g.setColour (slider.findColour (Slider::trackColourId));
    g.fillPath (off);
}

void CloudBurstLookAndFeel::drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                        float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
{
    const float radius = jmin (width / 2, height / 2) - 2.0f;
    const float centreX = x + width * 0.5f;
    const float centreY = y + height * 0.5f;
    const float rx = centreX - radius;
    const float ry = centreY - radius;
    const float rw = radius * 2.0f;
    const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    const bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();

    if (slider.isEnabled())
        g.setColour (slider.findColour (Slider::rotarySliderFillColourId).withAlpha (isMouseOver ? 1.0f : 0.7f));
    else
        g.setColour (Colour (0x80808080));

    {
        Path filledArc;
        filledArc.addPieSegment (rx, ry, rw, rw, rotaryStartAngle, angle, 0.0);
        g.fillPath (filledArc);
    }

    {
        const float lineThickness = jmin (15.0f, jmin (width, height) * 0.45f) * 0.1f;
        Path outlineArc;
        outlineArc.addPieSegment (rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, 0.0);
        g.strokePath (outlineArc, PathStrokeType (lineThickness));
    }
}

//==============================================================================
void CloudBurstLookAndFeel::drawTableHeaderBackground (Graphics& g, TableHeaderComponent& header)
{
	g.fillAll (Colours::white);
	juce::Rectangle<int> area(header.getLocalBounds());
	g.setGradientFill(ColourGradient(Colour(0xfff3f3f3), 0.0f, (float)area.getY() + ((area.getBottom() - area.getY())*0.25f), //dbdff1
										Colour (0xfff6f8f9), 0.0f, (float) area.getBottom(),
										false));
	g.fillRect (area);

	g.setColour (Colour (0x33000000));
	g.fillRect (area.removeFromBottom (1));

	for (int i = header.getNumColumns (true); --i >= 0;)
		g.fillRect (header.getColumnPosition (i).removeFromRight (1));
}

void CloudBurstLookAndFeel::drawTableHeaderColumn (Graphics& g, const String& columnName, int /*columnId*/,
											int width, int height, bool isMouseOver, bool isMouseDown,
											int columnFlags)
{
	if (isMouseDown)
		g.fillAll (Colour (0x8899aadd));
	else if (isMouseOver)
		g.fillAll (Colour (0x5599aadd));

	juce::Rectangle<int> area(width, height);
	area.reduce (4, 0);

	if ((columnFlags & (TableHeaderComponent::sortedForwards | TableHeaderComponent::sortedBackwards)) != 0)
	{
		Path sortArrow;
		sortArrow.addTriangle (0.0f, 0.0f,
								0.5f, (columnFlags & TableHeaderComponent::sortedForwards) != 0 ? -0.8f : 0.8f,
								1.0f, 0.0f);

		g.setColour (Colour (0x99000000));
		g.fillPath (sortArrow, sortArrow.getTransformToScaleToFit (area.removeFromRight (height / 2).reduced (2).toFloat(), true));
	}

	g.setColour (Colours::black);
	g.setFont (Font (height * 0.5f, Font::italic));//plain bold
	g.drawFittedText (columnName, area, Justification::centredLeft, 1);
}

void CloudBurstLookAndFeel::fillTextEditorBackground(Graphics &g, int width, int height, TextEditor &textEditor)
{
	g.fillAll(textEditor.findColour(TextEditor::backgroundColourId).darker(textEditor.isEnabled() ? 0.f : 0.05f));
	g.setColour(textEditor.findColour (TextEditor::shadowColourId).withMultipliedAlpha(textEditor.isEnabled() ? 1.0f : 0.7f));
	g.drawLine(0,0,(float)width,0);
	g.drawLine(0, 0, 0, (float)height);

	if (textEditor.getName().compare("messageTextEditor") == 0)
	{
		if (textEditor.getText().isEmpty())
		{
			g.setColour(Colours::grey);
			g.setFont(24);
			g.drawText("enter your message here", Rectangle<int>(0, 0, width, height), Justification::centred, 1);
		}
	}
}

void CloudBurstLookAndFeel::drawAlertBox(Graphics& g, AlertWindow& alert, const Rectangle<int>& textArea, TextLayout& textLayout)
{
	g.fillAll(alert.findColour(AlertWindow::backgroundColourId));

	int iconSpaceUsed = 0;

	const int iconWidth = 80;
	int iconSize = jmin(iconWidth + 50, alert.getHeight() + 20);

	if (alert.containsAnyExtraComponents() || alert.getNumButtons() > 2)
		iconSize = juce::jmin(iconSize, textArea.getHeight() + 50);

	const juce::Rectangle<int> iconRect(iconSize / -10, iconSize / -10,
		iconSize, iconSize);

	if (alert.getAlertType() != AlertWindow::NoIcon)
	{
		Path icon;
		uint32 colour;
		char character;

		if (alert.getAlertType() == AlertWindow::WarningIcon)
		{
			colour = 0x55ff5555;
			character = '!';

			icon.addTriangle(iconRect.getX() + iconRect.getWidth() * 0.5f, (float)iconRect.getY(),
				(float)iconRect.getRight(), (float)iconRect.getBottom(),
				(float)iconRect.getX(), (float)iconRect.getBottom());

			icon = icon.createPathWithRoundedCorners(5.0f);
		}
		else
		{
			colour = alert.getAlertType() == AlertWindow::InfoIcon ? (uint32)0x605555ff : (uint32)0x404496f2;
			character = alert.getAlertType() == AlertWindow::InfoIcon ? 'i' : '?';

			icon.addEllipse(iconRect.toFloat());
		}

		GlyphArrangement ga;
		ga.addFittedText(Font(iconRect.getHeight() * 0.9f, Font::bold),
			String::charToString((juce_wchar)(uint8)character),
			(float)iconRect.getX(), (float)iconRect.getY(),
			(float)iconRect.getWidth(), (float)iconRect.getHeight(),
			Justification::centred, false);
		ga.createPath(icon);

		icon.setUsingNonZeroWinding(false);
		g.setColour(Colour(colour));
		g.fillPath(icon);

		iconSpaceUsed = iconWidth;
	}

	g.setColour(alert.findColour(AlertWindow::textColourId));

	textLayout.draw(g, juce::Rectangle<int>(textArea.getX() + iconSpaceUsed,
		textArea.getY(),
		textArea.getWidth() - iconSpaceUsed,
		textArea.getHeight()).toFloat());

	g.setColour(alert.findColour(AlertWindow::outlineColourId));
	g.drawRect(0, 0, alert.getWidth(), alert.getHeight());
}

void CloudBurstLookAndFeel::drawProgressBardrawProgressBar(Graphics& g, ProgressBar& progressBar,
	int width, int height,
	double progress, const String& textToShow)
{
	const Colour background(progressBar.findColour(ProgressBar::backgroundColourId));
	const Colour foreground(progressBar.findColour(ProgressBar::foregroundColourId));

	g.fillAll(background);

	if (progress >= 0.0f && progress < 1.0f)
	{
		drawGlassLozenge(g, 1.0f, 1.0f,
			(float)jlimit(0.0, width - 2.0, progress * (width - 2.0)),
			(float)(height - 2),
			foreground,
			1.0f, 3.0f,
			false, false, true, true);
	}
	else
	{
		// spinning bar..
		g.setColour(foreground);

		const int stripeWidth = height * 2;
		const int position = (int)(Time::getMillisecondCounter() / 15) % stripeWidth;

		Path p;

		for (float x = (float)(-position); x < width + stripeWidth; x += stripeWidth)
			p.addQuadrilateral(x, 0.0f,
			x + stripeWidth * 0.5f, 0.0f,
			x, (float)height,
			x - stripeWidth * 0.5f, (float)height);

		Image im(Image::ARGB, width, height, true);

		{
			Graphics g2(im);
			drawGlassLozenge(g2, 1.0f, 1.0f,
				(float)(width - 2),
				(float)(height - 2),
				foreground,
				1.f, 3.0f,
				false, false, true, true);
		}

		g.setTiledImageFill(im, 0, 0, 0.85f);
		g.fillPath(p);
	}

	if (textToShow.isNotEmpty())
	{
		g.setColour(Colour::contrasting(background, foreground));
		g.setFont(height * 0.6f);

		g.drawText(textToShow.toUTF8(), 0, 0, width, height, Justification::centred, false);
	}
}

