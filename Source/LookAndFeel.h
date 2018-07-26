#ifndef CBLOOKANDFEEL_H_INCLUDED
#define CBLOOKANDFEEL_H_INCLUDED

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


#include "JuceHeader.h"

struct CloudBurstLookAndFeel    : public LookAndFeel_V3
{
	void Init();

	void setFont(Font f);
	void setFontBold(Font f);
	void setFontAlt(Font f);
	Typeface::Ptr 	getTypefaceForFont(const Font &) override;
	
	void drawLabel(Graphics& g, Label& label);
	void drawTooltip(Graphics& g, const String& text, int width, int height);
	void drawRoundThumb(Graphics& g, const float x, const float y, const float diameter, const Colour& colour, float outlineThickness);

	void drawButtonText(Graphics& g, TextButton& button, bool isMouseOverButton, bool isButtonDown);
	void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour, bool isMouseOverButton, bool isButtonDown);
	void drawTickBox(Graphics& g, Component& component, float x, float y, float w, float h, bool ticked, bool isEnabled, bool isMouseOverButton, bool isButtonDown);
	void drawLinearSliderThumb(Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider& slider);
	void drawLinearSlider(Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider& slider);
	void drawLinearSliderBackground(Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider& slider);
	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, Slider& slider);
	void drawTableHeaderBackground(Graphics& g, TableHeaderComponent& header);
	void drawTableHeaderColumn(Graphics& g, const String& columnName, int columnId, int width, int height, bool isMouseOver, bool isMouseDown, int columnFlags);
	void fillTextEditorBackground(Graphics &g, int width, int height, TextEditor &textEditor);
	void drawAlertBox(Graphics&, AlertWindow&, const juce::Rectangle<int>& textArea, TextLayout&) override;
	
	void drawProgressBardrawProgressBar(Graphics& g, ProgressBar& progressBar, int width, int height, double progress, const String& textToShow);
	
	void drawDocumentWindowTitleBar(DocumentWindow&, Graphics&, int w, int h,
		int titleSpaceX, int titleSpaceW,
		const Image* icon, bool drawTitleTextOnLeft) override;
	Button* createDocumentWindowButton(int buttonType) override;
	class OSXWindowButton;

	Font brFont;
	Font brFontBold;
	Font brFontAlt;
};


#endif  // CBLOOKANDFEEL_H_INCLUDED
