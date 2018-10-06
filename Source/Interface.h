/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 4.3.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_156B5A0DC5E114BE__
#define __JUCE_HEADER_156B5A0DC5E114BE__

//[Headers]     -- You can add your own extra header files here --
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
#include "../JuceLibraryCode/JuceHeader.h"
#include "LookAndFeel.h"
#include "BurstLib.h"

#define SEARCH_RANGE_MINUTES (24*60)
#define PREFIX_CB_RS "CLOUD"
#define PERCENT_FEE 1
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
                                                                    //[/Comments]
*/
class Interface  : public Component,
                   public TextEditorListener,
                   public Timer,
                   public ButtonListener,
                   public SliderListener,
                   public ComboBoxListener
{
public:
    //==============================================================================
    Interface ();
    ~Interface();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	int64 RecalcCosts();
	void textEditorTextChanged(TextEditor &editor); //Called when the user changes the text in some way.
	void textEditorReturnKeyPressed(TextEditor &editor); //Called when the user presses the return key.
	void textEditorEscapeKeyPressed(TextEditor &editor); //Called when the user presses the escape key.
	void textEditorFocusLost(TextEditor &editor); //Called when the text editor loses focus.

	class ProgressWindow : public ThreadWithProgressWindow
	{
	public:
		struct params
		{
			String server;
			String passPhrase;

			String downloadTransactionID;
			String message;
			File fileToUpload;
			unsigned int dropSize;
			unsigned int stackSize;
			unsigned int fee;
			unsigned int deadline;
		};
		ProgressWindow(Interface *parent, String txt, int doThis, params paramatersIn);
		~ProgressWindow();

		// result download
		bool downloadOk;
		String dlFilename;
		MemoryBlock dlData;
		unsigned long long epoch;
		
		// result upload
		unsigned long long confirmTime;
		String uploadFinishMsg;
		uint64 txFeePlancks;
		uint64 costsNQT;
		uint64 feePlancks;
		uint64 burnPlancks;
		String allText;

		String err;
	private:
		Interface *parent;
		
		void *dll_handle;
		burstlibPtr apiHandle;
		BurstLib_FunctionHandles burstLib;

		bool libLoaded;
		int doThis;
		params paramaters;
		var sendMoneyResult;

		void run();
		void Download();
		void Upload();
		int64 RecalcCosts();
		void Donate();
	};

	Array<StringArray> cmdsArray;
	bool parseCommands(const StringArray& filenames);
	bool parseCommandsCore();

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;

    // Binary resources:
    static const char* cloudburstlogosmall_png;
    static const int cloudburstlogosmall_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	void log(String message);
	ScopedPointer<CloudBurstLookAndFeel> wizlaf;
	void timerCallback();
	void SetParameterStruct();
	void RefreshCosts();
	String GetAppValue(const String type);
	void SetAppValue(const String type, const String value);
	void SetView(int nr);

	String Encrypt(String input);
	String Decrypt(String input);

	CriticalSection timerLock;
	CriticalSection cmdLock;

	ApplicationProperties appProp;
	PropertiesFile::Options options;
	File fileToUpload;
	bool showDisclaimer;
	int view;
	int64 costsNQT;
	int64 confirmationSecs;

	String costsLabelTooltip;

	ProgressWindow::params paramaters;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TextButton> syncButton;
    ScopedPointer<TextEditor> burstAddressTextEditor;
    ScopedPointer<Label> burstAddressLabel;
    ScopedPointer<Label> versionLabel;
    ScopedPointer<TextEditor> logTextEditor;
    ScopedPointer<TextEditor> messageTextEditor;
    ScopedPointer<TextButton> addFileButton;
    ScopedPointer<Label> costsLabel;
    ScopedPointer<TextButton> sendButton;
    ScopedPointer<Label> passPhraseLabel;
    ScopedPointer<TextEditor> passPhraseTextEditor;
    ScopedPointer<Label> messageLabel4;
    ScopedPointer<Slider> feeSlider;
    ScopedPointer<Label> feeLabel;
    ScopedPointer<TextButton> removeFileButton;
    ScopedPointer<ToggleButton> savePassPhraseToggleButton;
    ScopedPointer<Label> passPhraseLabel2;
    ScopedPointer<ComboBox> serverComboBox;
    ScopedPointer<Label> serverLabel;
    ScopedPointer<Label> rememberLabel;
    ScopedPointer<ImageButton> imageButton;
    ScopedPointer<TextButton> tabButton1;
    ScopedPointer<TextButton> tabButton2;
    ScopedPointer<Label> disclaimerLabel;
    ScopedPointer<TextButton> disclaimerButton;
    ScopedPointer<Slider> stackSizeSlider;
    ScopedPointer<Label> dropSizeLabel2;
    ScopedPointer<Label> donateLabel;
    ScopedPointer<TextButton> okayButton;
    ScopedPointer<HyperlinkButton> hyperlinkButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Interface)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_156B5A0DC5E114BE__
