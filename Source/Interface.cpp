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

//[Headers] You can add your own extra header files here...
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

#include "Logger.h"
#include "Version.h"
#include "BurstLib.c"
//[/Headers]

#include "Interface.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#define STR_SIZE 2048
#define HERE_BE_DRAGONS "godmode"
void Interface::log(String message)
{
	ToLog(message);
	logTextEditor->setText(message, dontSendNotification);
}
//[/MiscUserDefs]

//==============================================================================
Interface::Interface ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (syncButton = new TextButton ("new button"));
    syncButton->setTooltip (TRANS("You will be asked for a location to save the file"));
    syncButton->setButtonText (TRANS("Download"));
    syncButton->addListener (this);

    addAndMakeVisible (burstAddressTextEditor = new TextEditor ("new text editor"));
    burstAddressTextEditor->setTooltip (TRANS("The CLOUD id or numerical id of the file/message you want to download"));
    burstAddressTextEditor->setMultiLine (false);
    burstAddressTextEditor->setReturnKeyStartsNewLine (false);
    burstAddressTextEditor->setReadOnly (false);
    burstAddressTextEditor->setScrollbarsShown (true);
    burstAddressTextEditor->setCaretVisible (true);
    burstAddressTextEditor->setPopupMenuEnabled (true);
    burstAddressTextEditor->setText (String());

    addAndMakeVisible (burstAddressLabel = new Label ("burstAddressLabel",
                                                      TRANS("CLOUD ID")));
    burstAddressLabel->setFont (Font (18.00f, Font::plain));
    burstAddressLabel->setJustificationType (Justification::centred);
    burstAddressLabel->setEditable (false, false, false);
    burstAddressLabel->setColour (TextEditor::textColourId, Colours::black);
    burstAddressLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (versionLabel = new Label ("new label",
                                                 TRANS("v0.1")));
    versionLabel->setFont (Font (15.00f, Font::bold));
    versionLabel->setJustificationType (Justification::centredRight);
    versionLabel->setEditable (false, false, false);
    versionLabel->setColour (TextEditor::textColourId, Colours::black);
    versionLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (logTextEditor = new TextEditor ("new text editor"));
    logTextEditor->setMultiLine (true);
    logTextEditor->setReturnKeyStartsNewLine (true);
    logTextEditor->setReadOnly (true);
    logTextEditor->setScrollbarsShown (true);
    logTextEditor->setCaretVisible (false);
    logTextEditor->setPopupMenuEnabled (true);
    logTextEditor->setColour (TextEditor::textColourId, Colour (0xff00579d));
    logTextEditor->setColour (TextEditor::backgroundColourId, Colour (0x00ffffff));
    logTextEditor->setColour (TextEditor::shadowColourId, Colour (0x00ffffff));
    logTextEditor->setText (String());

    addAndMakeVisible (messageTextEditor = new TextEditor ("messageTextEditor"));
    messageTextEditor->setMultiLine (true);
    messageTextEditor->setReturnKeyStartsNewLine (true);
    messageTextEditor->setReadOnly (false);
    messageTextEditor->setScrollbarsShown (true);
    messageTextEditor->setCaretVisible (true);
    messageTextEditor->setPopupMenuEnabled (true);
    messageTextEditor->setText (String());

    addAndMakeVisible (addFileButton = new TextButton ("addFileButton"));
    addFileButton->setTooltip (TRANS("Select a file to upload (1 MB max)"));
    addFileButton->setButtonText (TRANS("Select file"));
    addFileButton->addListener (this);
    addFileButton->setColour (TextButton::buttonColourId, Colour (0xfff2f2f2));
    addFileButton->setColour (TextButton::buttonOnColourId, Colour (0xfff2f2f2));

    addAndMakeVisible (costsLabel = new Label ("costsLabel",
                                               TRANS("-")));
    costsLabel->setTooltip (TRANS("The total cost and confirmation speed depends on the size of the data (after max compression), the selected base fee and the stacked slots."));
    costsLabel->setFont (Font (25.00f, Font::plain));
    costsLabel->setJustificationType (Justification::centredRight);
    costsLabel->setEditable (false, false, false);
    costsLabel->setColour (Label::textColourId, Colours::black);
    costsLabel->setColour (TextEditor::textColourId, Colours::black);
    costsLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sendButton = new TextButton ("sendButton"));
    sendButton->setTooltip (TRANS("Upload your message and/or file to the Burst blockchain"));
    sendButton->setButtonText (TRANS("Upload"));
    sendButton->addListener (this);
    sendButton->setColour (TextButton::buttonColourId, Colour (0xfff2f2f2));
    sendButton->setColour (TextButton::buttonOnColourId, Colour (0xfff2f2f2));

    addAndMakeVisible (passPhraseLabel = new Label ("passPhraseLabel",
                                                    TRANS("Secret pass phrase")));
    passPhraseLabel->setFont (Font (15.00f, Font::plain));
    passPhraseLabel->setJustificationType (Justification::centredRight);
    passPhraseLabel->setEditable (false, false, false);
    passPhraseLabel->setColour (Label::textColourId, Colours::white);
    passPhraseLabel->setColour (TextEditor::textColourId, Colours::black);
    passPhraseLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (passPhraseTextEditor = new TextEditor ("new text editor"));
    passPhraseTextEditor->setTooltip (TRANS("enter your pass phrase here"));
    passPhraseTextEditor->setMultiLine (false);
    passPhraseTextEditor->setReturnKeyStartsNewLine (false);
    passPhraseTextEditor->setReadOnly (false);
    passPhraseTextEditor->setScrollbarsShown (false);
    passPhraseTextEditor->setCaretVisible (true);
    passPhraseTextEditor->setPopupMenuEnabled (true);
    passPhraseTextEditor->setText (String());

    addAndMakeVisible (messageLabel4 = new Label ("messageLabel",
                                                  TRANS("no file selected")));
    messageLabel4->setFont (Font (14.00f, Font::plain));
    messageLabel4->setJustificationType (Justification::centredLeft);
    messageLabel4->setEditable (false, false, false);
    messageLabel4->setColour (Label::textColourId, Colours::white);
    messageLabel4->setColour (TextEditor::textColourId, Colours::black);
    messageLabel4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (feeSlider = new Slider ("new slider"));
    feeSlider->setTooltip (TRANS("Slot priority: the base fee for each part of the upload. A higher value gives more confirm priority. Putting this value low during a time of high traffic could cause your upload to partially fail and result in a unusable broken file !"));
    feeSlider->setRange (1, 1020, 1);
    feeSlider->setSliderStyle (Slider::IncDecButtons);
    feeSlider->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);
    feeSlider->addListener (this);

    addAndMakeVisible (feeLabel = new Label ("feeLabel",
                                             TRANS("Slot priority")));
    feeLabel->setTooltip (TRANS("Slot priority: the base fee for each part of the upload. A higher value gives more confirm priority. Putting this value low during a time of high traffic could cause your upload to partially fail and result in a unusable broken file !"));
    feeLabel->setFont (Font (15.00f, Font::plain));
    feeLabel->setJustificationType (Justification::centredLeft);
    feeLabel->setEditable (false, false, false);
    feeLabel->setColour (Label::textColourId, Colours::black);
    feeLabel->setColour (TextEditor::textColourId, Colours::black);
    feeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (removeFileButton = new TextButton ("new button"));
    removeFileButton->setTooltip (TRANS("Remove the file from this upload"));
    removeFileButton->setButtonText (TRANS("clear"));
    removeFileButton->addListener (this);
    removeFileButton->setColour (TextButton::buttonColourId, Colour (0xfff2f2f2));
    removeFileButton->setColour (TextButton::buttonOnColourId, Colour (0xfff2f2f2));
    removeFileButton->setColour (TextButton::textColourOffId, Colours::black);
    removeFileButton->setColour (TextButton::textColourOnId, Colours::black);

    addAndMakeVisible (savePassPhraseToggleButton = new ToggleButton ("new toggle button"));
    savePassPhraseToggleButton->setTooltip (TRANS("Saves your pass phrase on this computer. It will be obscured but offers no guarantees of protection !"));
    savePassPhraseToggleButton->setButtonText (String());
    savePassPhraseToggleButton->addListener (this);
    savePassPhraseToggleButton->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (passPhraseLabel2 = new Label ("passPhraseLabel",
                                                     TRANS("Message")));
    passPhraseLabel2->setFont (Font (15.00f, Font::plain));
    passPhraseLabel2->setJustificationType (Justification::centredRight);
    passPhraseLabel2->setEditable (false, false, false);
    passPhraseLabel2->setColour (Label::textColourId, Colours::white);
    passPhraseLabel2->setColour (TextEditor::textColourId, Colours::black);
    passPhraseLabel2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (serverComboBox = new ComboBox ("new combo box"));
    serverComboBox->setTooltip (TRANS("Use a wallet that is well  connected (has peers). This will improve upload confirmation time."));
    serverComboBox->setEditableText (true);
    serverComboBox->setJustificationType (Justification::centredLeft);
    serverComboBox->setTextWhenNothingSelected (TRANS("http://127.0.0.1:8125/"));
    serverComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    serverComboBox->addItem (TRANS("http://127.0.0.1:8125/"), 1);
    serverComboBox->addItem (TRANS("https://wallet.burst.cryptoguru.org:8125/"), 2);
    serverComboBox->addItem (TRANS("https://wallet.dev.burst-test.net/"), 3);
    serverComboBox->addListener (this);

    addAndMakeVisible (serverLabel = new Label ("new label",
                                                TRANS("Wallet")));
    serverLabel->setFont (Font (15.00f, Font::plain));
    serverLabel->setJustificationType (Justification::centredLeft);
    serverLabel->setEditable (false, false, false);
    serverLabel->setColour (TextEditor::textColourId, Colours::black);
    serverLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (rememberLabel = new Label ("rememberLabel",
                                                  TRANS("remember")));
    rememberLabel->setFont (Font (15.00f, Font::plain));
    rememberLabel->setJustificationType (Justification::centredLeft);
    rememberLabel->setEditable (false, false, false);
    rememberLabel->setColour (Label::textColourId, Colours::white);
    rememberLabel->setColour (TextEditor::textColourId, Colours::black);
    rememberLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (imageButton = new ImageButton ("new button"));
    imageButton->addListener (this);

    imageButton->setImages (false, true, true,
                            ImageCache::getFromMemory (cloudburstlogosmall_png, cloudburstlogosmall_pngSize), 1.000f, Colour (0x00000000),
                            ImageCache::getFromMemory (cloudburstlogosmall_png, cloudburstlogosmall_pngSize), 1.000f, Colour (0x00000000),
                            ImageCache::getFromMemory (cloudburstlogosmall_png, cloudburstlogosmall_pngSize), 1.000f, Colour (0x00000000));
    addAndMakeVisible (tabButton1 = new TextButton ("new button"));
    tabButton1->setButtonText (TRANS("Download"));
    tabButton1->addListener (this);

    addAndMakeVisible (tabButton2 = new TextButton ("new button"));
    tabButton2->setButtonText (TRANS("Upload"));
    tabButton2->addListener (this);

    addAndMakeVisible (disclaimerLabel = new Label ("disclaimerLabel",
                                                    TRANS("DISCLAIMER\n"
                                                    "Any uploaded data will be PUBLIC ! You hold sole responsibility for the contents that is uploaded. \n"
                                                    "\n"
                                                    "No warranties or guarantees are given to the user of this software.\n"
                                                    "\n"
                                                    "Using new wallet with limited funds is recommended !")));
    disclaimerLabel->setFont (Font (15.00f, Font::bold));
    disclaimerLabel->setJustificationType (Justification::centredLeft);
    disclaimerLabel->setEditable (false, false, false);
    disclaimerLabel->setColour (Label::backgroundColourId, Colours::white);
    disclaimerLabel->setColour (Label::textColourId, Colours::red);
    disclaimerLabel->setColour (Label::outlineColourId, Colours::black);
    disclaimerLabel->setColour (TextEditor::textColourId, Colours::black);
    disclaimerLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (disclaimerButton = new TextButton ("disclaimerButton"));
    disclaimerButton->setButtonText (TRANS("Okay, I got it !"));
    disclaimerButton->addListener (this);

    addAndMakeVisible (stackSizeSlider = new Slider ("stackSizeSlider"));
    stackSizeSlider->setTooltip (TRANS("Higher slot stacking will speed up confirmation of the upload but the total costs will be higher."));
    stackSizeSlider->setRange (1, 1020, 1);
    stackSizeSlider->setSliderStyle (Slider::IncDecButtons);
    stackSizeSlider->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);
    stackSizeSlider->addListener (this);

    addAndMakeVisible (dropSizeLabel2 = new Label ("dropSizeLabel",
                                                   TRANS("Slot stacking")));
    dropSizeLabel2->setTooltip (TRANS("Higher slot stacking will speed up confirmation of the upload but the total costs will be higher."));
    dropSizeLabel2->setFont (Font (15.00f, Font::plain));
    dropSizeLabel2->setJustificationType (Justification::centredLeft);
    dropSizeLabel2->setEditable (false, false, false);
    dropSizeLabel2->setColour (Label::textColourId, Colours::black);
    dropSizeLabel2->setColour (TextEditor::textColourId, Colours::black);
    dropSizeLabel2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (donateLabel = new Label ("new label",
                                                TRANS("The first decentralised cloud file storage !\n"
                                                "For more info please visit")));
    donateLabel->setFont (Font (16.00f, Font::plain));
    donateLabel->setJustificationType (Justification::centred);
    donateLabel->setEditable (false, false, false);
    donateLabel->setColour (TextEditor::textColourId, Colours::black);
    donateLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (okayButton = new TextButton ("okayButton"));
    okayButton->setButtonText (TRANS("Okay"));
    okayButton->addListener (this);

    addAndMakeVisible (hyperlinkButton = new HyperlinkButton (TRANS("CloudBurst DAPP"),
                                                              URL ("https://github.com/CurbShifter/CloudBurstDAPP")));
    hyperlinkButton->setTooltip (TRANS("https://github.com/CurbShifter/CloudBurstDAPP"));
    hyperlinkButton->setButtonText (TRANS("CloudBurst DAPP"));
    hyperlinkButton->setColour (HyperlinkButton::textColourId, Colour (0xcc00579d));


    //[UserPreSize]

	costsLabel->setTooltip(" " + costsLabel->getTooltip() + TRANS("with a ") + String(PERCENT_FEE) + TRANS("% dapp usage fee"));
	costsLabelTooltip = costsLabel->getTooltip();

	wizlaf = new CloudBurstLookAndFeel();
	Typeface::Ptr typefacePtr = Typeface::createSystemTypefaceFor(BinaryData::NotoSansRegular_ttf, BinaryData::NotoSansRegular_ttfSize);
	Font f(typefacePtr);
	wizlaf->setFont(f);
	wizlaf->setColour(TreeView::selectedItemBackgroundColourId, Colour(0xff83acf0));
	wizlaf->setColour(TextEditor::highlightColourId, Colour(0xff83acf0));
	wizlaf->setColour(TextEditor::highlightedTextColourId, Colour(0xff141305));
	wizlaf->setColour(TextEditor::backgroundColourId, Colour(0xfff6f6f6));
	wizlaf->setColour(TextEditor::textColourId, Colours::black);
	wizlaf->setColour(TextEditor::focusedOutlineColourId, Colour(0xfface1ef));
	wizlaf->setColour(TextEditor::shadowColourId, Colour(0xffbbbbbb));
	wizlaf->setColour(ListBox::outlineColourId, Colour(0xffe4e4e4));
	wizlaf->setColour(ListBox::backgroundColourId, Colour(0xbefdfdfd));
	wizlaf->setColour(Label::textColourId, Colour(0xffffffff));
	wizlaf->setColour(juce::TextButton::buttonOnColourId, Colour(0xfface1ef));
	wizlaf->setColour(juce::TextButton::buttonColourId, Colour(0xff88bbc8));
	wizlaf->setColour(juce::TextButton::textColourOnId, Colour(0xffffffff));
	wizlaf->setColour(juce::TextButton::textColourOffId, Colour(0xffffffff));
	wizlaf->setColour(juce::TextButton::buttonOnColourId, Colour(0xfface1ef));
	wizlaf->setColour(ProgressBar::foregroundColourId, Colour(0xfface1ef));
	LookAndFeel::setDefaultLookAndFeel(wizlaf);
	wizlaf->Init();

	syncButton->setColour(TextButton::buttonColourId, (Colour(0xff00579d)));
	addFileButton->setColour(TextButton::buttonColourId, (Colour(0xfff2f2f2)));
	sendButton->setColour(TextButton::buttonColourId, (Colour(0xfff2f2f2)));
	removeFileButton->setColour(TextButton::buttonColourId, (Colour(0xfff2f2f2)));
	tabButton1->setColour(TextButton::buttonColourId, (Colour(0xff00579d)));
	tabButton2->setColour(TextButton::buttonColourId, (Colour(0xff00579d)));
	disclaimerButton->setColour(TextButton::buttonColourId, (Colour(0xfff2f2f2)));

	syncButton->setColour(TextButton::buttonOnColourId, (Colour(0xff00579d)));
	addFileButton->setColour(TextButton::buttonOnColourId, (Colour(0xfff2f2f2)));
	sendButton->setColour(TextButton::buttonOnColourId, (Colour(0xfff2f2f2)));
	removeFileButton->setColour(TextButton::buttonOnColourId, (Colour(0xfff2f2f2)));
	tabButton1->setColour(TextButton::buttonOnColourId, (Colour(0xff00579d)));
	tabButton2->setColour(TextButton::buttonOnColourId, (Colour(0xff00579d)));
	disclaimerButton->setColour(TextButton::buttonOnColourId, (Colour(0xfff2f2f2)));

	addFileButton->setColour(TextButton::textColourOffId, Colours::black);
	addFileButton->setColour(TextButton::textColourOnId, Colours::black);
	sendButton->setColour(TextButton::textColourOffId, Colours::black);
	sendButton->setColour(TextButton::textColourOnId, Colours::black);
	disclaimerButton->setColour(TextButton::textColourOffId, Colours::black);
	disclaimerButton->setColour(TextButton::textColourOnId, Colours::black);

	serverLabel->setColour(Label::textColourId, Colours::black);
	serverLabel->setColour(Label::backgroundColourId, Colour(0x00000000));

	burstAddressLabel->setColour(Label::textColourId, Colours::black);
	burstAddressLabel->setColour(Label::backgroundColourId, Colour(0x00000000));
	versionLabel->setColour(Label::textColourId, Colours::black);
	versionLabel->setColour(Label::backgroundColourId, Colour(0x00000000));

	options.commonToAllUsers = false;
	options.applicationName = "CloudBurst";
	options.folderName = "CurbShifter";
	options.filenameSuffix = "settings";
	options.osxLibrarySubFolder = "Application Support";
	options.storageFormat = PropertiesFile::storeAsXML;
	appProp.setStorageParameters(options);

	passPhraseTextEditor->setPasswordCharacter(0x2022);
	burstAddressTextEditor->setTextToShowWhenEmpty("Transaction ID", Colours::lightgrey);
	burstAddressTextEditor->setFont(30);
	burstAddressTextEditor->setInputRestrictions(27, "0123456789-abcdefghjklmnopqrstuvwxyzABCDEFGHJKLMNOPQRSTUVWXYZ"); // PREFIX -XXXX-XXXX-XXXX-XXXXX // "1234567890"  including 0 and 1 because numerical option. and O because of CLOUD prefix

	serverComboBox->setSelectedItemIndex(0, dontSendNotification);
	messageTextEditor->addListener(this);

	showDisclaimer = GetAppValue("showDisclaimer").getIntValue() > -3;
	view = 0;
	costsNQT = 0;

	messageTextEditor->setInputRestrictions(4096);
    //[/UserPreSize]

    setSize (600, 380);


    //[Constructor] You can add your own custom stuff here..
	SetView(0);

	serverComboBox->setText(GetAppValue("server"), dontSendNotification);
	burstAddressTextEditor->setText(GetAppValue("burstAddress"), dontSendNotification);
	passPhraseTextEditor->setText(Decrypt(GetAppValue("passPhraseEnc")), dontSendNotification);
	savePassPhraseToggleButton->setToggleState(GetAppValue("savePassPhrase").getIntValue() > 0, dontSendNotification);

	burstAddressTextEditor->addListener(this);
	passPhraseTextEditor->addListener(this);

	versionLabel->setText("v1.2." SVNRevision, dontSendNotification);

	feeSlider->setValue(10, dontSendNotification);
	stackSizeSlider->setValue(10, dontSendNotification);

	parseCommands(StringArray::fromTokens(JUCEApplicationBase::getCommandLineParameters(), " ", "\"'"));

	startTimer(1000);
    //[/Constructor]
}

Interface::~Interface()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    syncButton = nullptr;
    burstAddressTextEditor = nullptr;
    burstAddressLabel = nullptr;
    versionLabel = nullptr;
    logTextEditor = nullptr;
    messageTextEditor = nullptr;
    addFileButton = nullptr;
    costsLabel = nullptr;
    sendButton = nullptr;
    passPhraseLabel = nullptr;
    passPhraseTextEditor = nullptr;
    messageLabel4 = nullptr;
    feeSlider = nullptr;
    feeLabel = nullptr;
    removeFileButton = nullptr;
    savePassPhraseToggleButton = nullptr;
    passPhraseLabel2 = nullptr;
    serverComboBox = nullptr;
    serverLabel = nullptr;
    rememberLabel = nullptr;
    imageButton = nullptr;
    tabButton1 = nullptr;
    tabButton2 = nullptr;
    disclaimerLabel = nullptr;
    disclaimerButton = nullptr;
    stackSizeSlider = nullptr;
    dropSizeLabel2 = nullptr;
    donateLabel = nullptr;
    okayButton = nullptr;
    hyperlinkButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Interface::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
	/*
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    g.setColour (Colour (0xfff2f2f2));
    g.fillRect (0, 80, 600, 300);

    g.setColour (Colour (0xff00579d));
    g.fillRect (0, 380, 600, 300);

    g.setColour (Colour (0xfff2f2f2));
    g.fillRect (16, 528, 568, 63);

    //[UserPaint] Add your own custom painting code here..
	*/
	g.fillAll(Colours::white);

	if (view == 0)
	{
		g.setColour(Colour(0xfff2f2f2));
		g.fillRect(0, 80, 600, 300);
	}
	else if (view == 1)
	{
		g.setColour(Colour(0xff00579d));
		g.fillRect(0, 80, 600, 300);

		if (!showDisclaimer)
		{
			g.setColour(Colour(0xfff2f2f2));
			g.fillRect(16, 228, 568, 63);
		}
	}
	else
	{
		g.setColour(Colour(0xfff2f2f2));
		g.fillRect(0, 80, 600, 300);
	}
    //[/UserPaint]
}

void Interface::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    syncButton->setBounds (100, 195, 400, 48);
    burstAddressTextEditor->setBounds (100, 154, 400, 33);
    burstAddressLabel->setBounds (100, 119, 400, 29);
    versionLabel->setBounds (534, 50, 54, 20);
    logTextEditor->setBounds (100, 256, 400, 101);
    messageTextEditor->setBounds (140, 428, 444, 84);
    addFileButton->setBounds (11, 396, 120, 24);
    costsLabel->setBounds (272, 534, 304, 52);
    sendButton->setBounds (424, 636, 160, 32);
    passPhraseLabel->setBounds (10, 606, 120, 24);
    passPhraseTextEditor->setBounds (140, 606, 444, 24);
    messageLabel4->setBounds (200, 396, 384, 24);
    feeSlider->setBounds (18, 536, 150, 22);
    feeLabel->setBounds (170, 536, 94, 22);
    removeFileButton->setBounds (141, 396, 56, 24);
    savePassPhraseToggleButton->setBounds (142, 634, 24, 24);
    passPhraseLabel2->setBounds (10, 428, 120, 24);
    serverComboBox->setBounds (140, 41, 264, 24);
    serverLabel->setBounds (140, 15, 263, 24);
    rememberLabel->setBounds (173, 634, 88, 24);
    imageButton->setBounds (430, 10, 128, 56);
    tabButton1->setBounds (11, 9, 120, 24);
    tabButton2->setBounds (11, 41, 120, 24);
    disclaimerLabel->setBounds (664, 112, 392, 216);
    disclaimerButton->setBounds (664, 336, 392, 24);
    stackSizeSlider->setBounds (18, 562, 150, 22);
    dropSizeLabel2->setBounds (170, 562, 94, 22);
    donateLabel->setBounds (704, 440, 320, 80);
    okayButton->setBounds (704, 592, 168, 24);
    hyperlinkButton->setBounds (664, 520, 400, 40);
    //[UserResized] Add your own custom resize handling here..

	int ty = -300;
	messageTextEditor->setBounds(messageTextEditor->getBounds().translated(0, ty));
	addFileButton->setBounds(addFileButton->getBounds().translated(0, ty));
	removeFileButton->setBounds(removeFileButton->getBounds().translated(0, ty));
	costsLabel->setBounds(costsLabel->getBounds().translated(0, ty));
	sendButton->setBounds(sendButton->getBounds().translated(0, ty));
	passPhraseLabel->setBounds(passPhraseLabel->getBounds().translated(0, ty));
	passPhraseTextEditor->setBounds(passPhraseTextEditor->getBounds().translated(0, ty));
	savePassPhraseToggleButton->setBounds(savePassPhraseToggleButton->getBounds().translated(0, ty));
	rememberLabel->setBounds(rememberLabel->getBounds().translated(0, ty));
	feeSlider->setBounds(feeSlider->getBounds().translated(0, ty));
	stackSizeSlider->setBounds(stackSizeSlider->getBounds().translated(0, ty));
	feeLabel->setBounds(feeLabel->getBounds().translated(0, ty));
	dropSizeLabel2->setBounds(dropSizeLabel2->getBounds().translated(0, ty));
	passPhraseLabel2->setBounds(passPhraseLabel2->getBounds().translated(0, ty));
	messageLabel4->setBounds(messageLabel4->getBounds().translated(0, ty));

	juce::Rectangle<int> rect(0, 80, 600, 300);
	disclaimerLabel->setBounds(rect.reduced(80).withTrimmedBottom(25));
	disclaimerButton->setBounds(disclaimerLabel->getBounds().translated(0, disclaimerLabel->getHeight()).withHeight(25));


	juce::Rectangle<int> rect2(rect.withTrimmedBottom(80).reduced(50));
	donateLabel->setBounds(rect2.withTrimmedBottom(rect2.getHeight() / 2));
	hyperlinkButton->setBounds(rect2.withTrimmedTop(rect2.getHeight() / 2).withTrimmedBottom(rect2.getHeight() / 4));
	okayButton->setBounds(rect2.withHeight(25).withY(rect2.getY() + rect2.getHeight()));

    //[/UserResized]
}

void Interface::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == syncButton)
    {
        //[UserButtonCode_syncButton] -- add your button handler code here..
		SetParameterStruct();
		ProgressWindow progressThread(this, "Download...", 0, paramaters);
		progressThread.runThread();
		logTextEditor->setText("", dontSendNotification);
		if (progressThread.allText.isNotEmpty() && progressThread.downloadOk)
		{
			if (progressThread.allText.isNotEmpty())
				logTextEditor->setText(progressThread.allText, dontSendNotification);			

			//	NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, progressThread.allText.dropLastCharacters(progressThread.allText.length() - 140));
			if (progressThread.dlData.getSize() > 0 && progressThread.dlFilename.isNotEmpty())
			{
				FileChooser myChooser("Select a download folder to save " + progressThread.dlFilename, File::getSpecialLocation(File::userDesktopDirectory), "*.*");
				if (myChooser.browseForDirectory())
				{
					File saveFile = (myChooser.getResult().getChildFile(progressThread.dlFilename));

					if (!saveFile.existsAsFile()) // dont overwite existing files
					{
						saveFile.getParentDirectory().createDirectory();
						if (progressThread.dlData.getSize() > 0 && saveFile.existsAsFile() == false)
							saveFile.appendData(progressThread.dlData.getData(), progressThread.dlData.getSize());
					}
				}
			}
		}
		else if (progressThread.epoch > 0)
			NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, ProjectInfo::projectName, "The upload seems incomplete !\nIt is either broken or wait for confirmation.");
		else NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, ProjectInfo::projectName, "Nothing found !");

        //[/UserButtonCode_syncButton]
    }
    else if (buttonThatWasClicked == addFileButton)
    {
        //[UserButtonCode_addFileButton] -- add your button handler code here..
		MemoryBlock mbIn;
		FileChooser myChooser("Please select the file you want to upload...", File::getSpecialLocation(File::userDesktopDirectory), "*.*");
		if (myChooser.browseForFileToOpen())
		{
			if (myChooser.getResult().getSize() < 8 * 128 * 1020 || passPhraseTextEditor->getText().endsWith(HERE_BE_DRAGONS)) // 11 addresses - 8 bytes
			{
				fileToUpload = (myChooser.getResult());

				String filename = fileToUpload.getFileName();
				messageLabel4->setText(filename + " (" + String(fileToUpload.getSize() / 1000.f / 1000.f, 2) + " MB)", dontSendNotification);

				RefreshCosts();
			}
			else NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, ProjectInfo::projectName, "max is 1 MB !");
		}
        //[/UserButtonCode_addFileButton]
    }
    else if (buttonThatWasClicked == sendButton)
    {
        //[UserButtonCode_sendButton] -- add your button handler code here..
		String neatNr(costsNQT);
		neatNr = neatNr.paddedLeft('0', 9);
		neatNr = neatNr.substring(0, neatNr.length() - 8) + "." + neatNr.substring(neatNr.length() - 8, neatNr.length());

		if (confirmationSecs > (SEARCH_RANGE_MINUTES * 60))
		{
			NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, ProjectInfo::projectName, "The confirmation will probably take longer than " + RelativeTime(SEARCH_RANGE_MINUTES * 60).getDescription() + " !\nYou should use a higher stack size.");
		}
		else if (NativeMessageBox::showOkCancelBox(AlertWindow::QuestionIcon, ProjectInfo::projectName, "Upload your message (and attachment)?\n" + neatNr + " BURST"))
		{
			SetParameterStruct();
			ProgressWindow progressThread(this, "Upload...", 1, paramaters);
			progressThread.runThread();

			NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, progressThread.uploadFinishMsg);
		}
        //[/UserButtonCode_sendButton]
    }
    else if (buttonThatWasClicked == removeFileButton)
    {
        //[UserButtonCode_removeFileButton] -- add your button handler code here..
		fileToUpload = File();
		messageLabel4->setText("no file selected", dontSendNotification);
		RefreshCosts();
        //[/UserButtonCode_removeFileButton]
    }
    else if (buttonThatWasClicked == savePassPhraseToggleButton)
    {
        //[UserButtonCode_savePassPhraseToggleButton] -- add your button handler code here..
		SetAppValue("savePassPhrase", String(savePassPhraseToggleButton->getToggleState()));

		if (savePassPhraseToggleButton->getToggleState())
			SetAppValue("passPhraseEnc", Encrypt(passPhraseTextEditor->getText()));
		else SetAppValue("passPhraseEnc", "");
        //[/UserButtonCode_savePassPhraseToggleButton]
    }
    else if (buttonThatWasClicked == imageButton)
    {
        //[UserButtonCode_imageButton] -- add your button handler code here..
		SetView(2);
        //[/UserButtonCode_imageButton]
    }
    else if (buttonThatWasClicked == tabButton1)
    {
        //[UserButtonCode_tabButton1] -- add your button handler code here..
		SetView(0);
        //[/UserButtonCode_tabButton1]
    }
    else if (buttonThatWasClicked == tabButton2)
    {
        //[UserButtonCode_tabButton2] -- add your button handler code here..
		SetView(1);
        //[/UserButtonCode_tabButton2]
    }
    else if (buttonThatWasClicked == disclaimerButton)
    {
        //[UserButtonCode_disclaimerButton] -- add your button handler code here..
		showDisclaimer = false;
		SetAppValue("showDisclaimer", String(GetAppValue("showDisclaimer").getIntValue() - 1));
		SetView(1);
        //[/UserButtonCode_disclaimerButton]
    }
    else if (buttonThatWasClicked == okayButton)
    {
        //[UserButtonCode_okayButton] -- add your button handler code here..
		SetView(1);
        //[/UserButtonCode_okayButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void Interface::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
	RefreshCosts();
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == feeSlider)
    {
        //[UserSliderCode_feeSlider] -- add your slider handling code here..
        //[/UserSliderCode_feeSlider]
    }
    else if (sliderThatWasMoved == stackSizeSlider)
    {
        //[UserSliderCode_stackSizeSlider] -- add your slider handling code here..
        //[/UserSliderCode_stackSizeSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void Interface::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == serverComboBox)
    {
        //[UserComboBoxCode_serverComboBox] -- add your combo box handling code here..
		SetAppValue("server", serverComboBox->getText());
        //[/UserComboBoxCode_serverComboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void Interface::textEditorTextChanged(TextEditor &editor) //Called when the user changes the text in some way.
{
	if (burstAddressTextEditor == &editor)
	{
		SetAppValue("burstAddress", editor.getText());
	}
	else if (passPhraseTextEditor == &editor)
	{
		if (savePassPhraseToggleButton->getToggleState())
			SetAppValue("passPhraseEnc", Encrypt(editor.getText()));
		else SetAppValue("passPhraseEnc", "");
	}
}
void Interface::textEditorReturnKeyPressed(TextEditor &/*editor*/) //Called when the user presses the return key.
{}
void Interface::textEditorEscapeKeyPressed(TextEditor &/*editor*/) //Called when the user presses the escape key.
{}
void Interface::textEditorFocusLost(TextEditor &editor) //Called when the text editor loses focus.
{
	if (messageTextEditor == &editor)
	{
		RefreshCosts();
	}
}

void Interface::RefreshCosts()
{
	SetParameterStruct();
	ProgressWindow progressThread(this, "Calculating costs...", 2, paramaters);
	progressThread.runThread();

	confirmationSecs = progressThread.confirmTime;// ((int)(progressThread.allAddresses.size() / stackSizeSlider->getValue()) + 1) * 4 * 60;

	String feePlancksNeatNr(progressThread.feePlancks);
	feePlancksNeatNr = feePlancksNeatNr.paddedLeft('0', 9);
	feePlancksNeatNr = feePlancksNeatNr.substring(0, feePlancksNeatNr.length() - 8) + "." + feePlancksNeatNr.substring(feePlancksNeatNr.length() - 8, feePlancksNeatNr.length());

	String txFeePlancksNeatNr(progressThread.txFeePlancks);
	txFeePlancksNeatNr = txFeePlancksNeatNr.paddedLeft('0', 9);
	txFeePlancksNeatNr = txFeePlancksNeatNr.substring(0, txFeePlancksNeatNr.length() - 8) + "." + txFeePlancksNeatNr.substring(txFeePlancksNeatNr.length() - 8, txFeePlancksNeatNr.length());

	// alternative display
	String txtAlt("\n\n" + //String(progressThread.allAddresses.size()) + " Multi Out (" + String(progressThread.addressesNum * 8) + " bytes)\n" +
		String((float)progressThread.burnPlancks) + " planck burn\n" +
		txFeePlancksNeatNr + " BURST tx fee\n" +
		feePlancksNeatNr + " BURST dapp fee");
	costsLabel->setTooltip(costsLabelTooltip + txtAlt);

	int64 totalNQT = progressThread.burnPlancks + progressThread.txFeePlancks + progressThread.feePlancks;
	String neatNr(totalNQT);
	neatNr = neatNr.paddedLeft('0', 9);
	neatNr = neatNr.substring(0, neatNr.length() - 8) + "." + neatNr.substring(neatNr.length() - 8, neatNr.length());

	String txt("~ " + RelativeTime(confirmationSecs).getDescription() + " to confirm" + "\n" + neatNr + " BURST");
	costsLabel->setText(txt, dontSendNotification);

	costsNQT = totalNQT;
}

String Interface::GetAppValue(const String type)
{
	String ret;
	PropertiesFile* props2 = appProp.getUserSettings();
	if (props2){
		ret = props2->getValue(type);
	}
	return ret.replace("&quot;", "\"");
}

void Interface::SetAppValue(const String type, const String value)
{
	PropertiesFile* props2 = appProp.getUserSettings();
	if (props2){
		props2->setValue(type, value.replace("\"", "&quot;"));
	}
	appProp.closeFiles();
}

void Interface::SetView(int nr)
{
	if (nr == 2 && view == 2)
		nr = 0;
	view = nr;

	if (nr == 0)
	{
		tabButton1->setColour(TextButton::buttonColourId, (Colour(0xff00579d)));
		tabButton1->setColour(TextButton::buttonOnColourId, (Colour(0xff00579d)));
		tabButton1->setColour(TextButton::textColourOnId, (Colour(0xffffffff)));
		tabButton1->setColour(TextButton::textColourOffId, (Colour(0xffffffff)));

		tabButton2->setColour(TextButton::buttonColourId, (Colour(0xffffffff)));
		tabButton2->setColour(TextButton::buttonOnColourId, (Colour(0xffffffff)));
		tabButton2->setColour(TextButton::textColourOnId, (Colour(0xff000000)));
		tabButton2->setColour(TextButton::textColourOffId, (Colour(0xff000000)));
	}
	else if (nr == 1)
	{
		tabButton1->setColour(TextButton::buttonColourId, (Colour(0xffffffff)));
		tabButton1->setColour(TextButton::buttonOnColourId, (Colour(0xffffffff)));
		tabButton1->setColour(TextButton::textColourOnId, (Colour(0xff000000)));
		tabButton1->setColour(TextButton::textColourOffId, (Colour(0xff000000)));

		tabButton2->setColour(TextButton::buttonColourId, (Colour(0xff00579d)));
		tabButton2->setColour(TextButton::buttonOnColourId, (Colour(0xff00579d)));
		tabButton2->setColour(TextButton::textColourOnId, (Colour(0xffffffff)));
		tabButton2->setColour(TextButton::textColourOffId, (Colour(0xffffffff)));
	}

	tabButton1->setVisible(nr != 2);
	tabButton2->setVisible(nr != 2);
	serverLabel->setVisible(nr != 2);
	serverComboBox->setVisible(nr != 2);

	burstAddressTextEditor->setVisible(view == 0);
	burstAddressLabel->setVisible(view == 0);
	logTextEditor->setVisible(view == 0);
	syncButton->setVisible(view == 0);

	messageTextEditor->setVisible(!showDisclaimer && view == 1);
	addFileButton->setVisible(!showDisclaimer && view == 1);
	removeFileButton->setVisible(!showDisclaimer && view == 1);
	costsLabel->setVisible(!showDisclaimer && view == 1);
	sendButton->setVisible(!showDisclaimer && view == 1);
	passPhraseLabel->setVisible(!showDisclaimer && view == 1);
	passPhraseTextEditor->setVisible(!showDisclaimer && view == 1);
	savePassPhraseToggleButton->setVisible(!showDisclaimer && view == 1);
	rememberLabel->setVisible(!showDisclaimer && view == 1);
	feeSlider->setVisible(!showDisclaimer && view == 1);
	stackSizeSlider->setVisible(!showDisclaimer && view == 1);
	feeLabel->setVisible(!showDisclaimer && view == 1);
	dropSizeLabel2->setVisible(!showDisclaimer && view == 1);
	passPhraseLabel2->setVisible(!showDisclaimer && view == 1);
	messageLabel4->setVisible(!showDisclaimer && view == 1);

	disclaimerLabel->setVisible(showDisclaimer && view == 1);
	disclaimerButton->setVisible(showDisclaimer && view == 1);

	hyperlinkButton->setVisible(view == 2);
	donateLabel->setVisible(view == 2);
	okayButton->setVisible(view == 2);

	repaint();
}

void Interface::SetParameterStruct()
{
	paramaters.server = serverComboBox->getText();
	if (paramaters.server.isEmpty())
		paramaters.server = "http://127.0.0.1:8125/";
	paramaters.passPhrase = passPhraseTextEditor->getText().upToLastOccurrenceOf(HERE_BE_DRAGONS, false, false);
	paramaters.downloadTransactionID = burstAddressTextEditor->getText();
	paramaters.message = messageTextEditor->getText();
	paramaters.fileToUpload = fileToUpload;
	paramaters.dropSize = 1;
	paramaters.stackSize = (unsigned int)stackSizeSlider->getValue();
	paramaters.fee = (unsigned int)feeSlider->getValue() * 735000;
	paramaters.deadline = 24;
}

Interface::ProgressWindow::~ProgressWindow()
{
	if (apiHandle && burstLib.DeleteHandle)
		burstLib.DeleteHandle(apiHandle);
	BurstLib_UnloadDLL(dll_handle);
}

Interface::ProgressWindow::ProgressWindow(Interface *parent, String txt, int doThis, params paramatersIn)
	: ThreadWithProgressWindow(txt, true, true, 15000, TRANS("Cancel"))
{
	this->parent = parent;
	this->doThis = doThis;

	txFeePlancks = 0;
	burnPlancks = 0;	
	costsNQT = 0;
	feePlancks = 0;

	paramaters = paramatersIn;
	
	libLoaded = false;
	File library_path(File::getSpecialLocation(File::hostApplicationPath).getParentDirectory());
#if defined(_WIN64) || defined(_WIN32)
	library_path = library_path.getChildFile("BurstLib.dll");
#elif defined(__APPLE__)
	library_path = library_path.getParentDirectory().getChildFile("Resources").getChildFile("BurstLib.dylib");
#endif
	dll_handle = 0;
	if (library_path.existsAsFile())
	{
		dll_handle = BurstLib_LoadDLL(library_path.getFullPathName().toRawUTF8(), &burstLib);// Call the library functions
		if (!dll_handle || burstLib.GetHandle == nullptr)
			ToLog("BurstLib library not found!");
		else
		{
			apiHandle = burstLib.GetHandle();
			if (apiHandle)
			{
				ToLog(("BurstLib version ") + String(burstLib.GetBurstLibVersionNumber(apiHandle)));
				libLoaded = true;
			}
			else ToLog("Failed to create API handle!");
		}
	}
	if (!libLoaded)
	{
		NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, ProjectInfo::projectName, "No BurstLib found, or it failed to load !\n" + library_path.getFullPathName());
		juce::JUCEApplication::quit();
	}
	else
	{
		burstLib.SetNode(apiHandle, paramaters.server.toRawUTF8(), paramaters.server.getNumBytesAsUTF8());
		burstLib.SetSecretPhrase(apiHandle, paramaters.passPhrase.toRawUTF8(), paramaters.passPhrase.getNumBytesAsUTF8());
	}
}

void Interface::ProgressWindow::run()
{
	ThreadWithProgressWindow::setProgress(0);
	if (burstLib.SetNode == 0)
		return;

	if (doThis == 0)
	{
		setStatusMessage("Searching and building data...");
		Download();
	}
	else if (doThis == 1)
	{
		setStatusMessage("Sending data...");
		Upload();
	}
	else if (doThis == 2)
	{
		setStatusMessage("Recalculating costs...");
		RecalcCosts();
	}
	else if (doThis == 3)
	{
		setStatusMessage("Donating...");
		Donate();
	}
}

void Interface::ProgressWindow::Download()
{
	allText.clear();
	downloadOk = false;

	if (burstLib.CloudDownloadStart == 0 || burstLib.CloudDownloadFinished == 0 || burstLib.CloudCancel == 0)
		return;

	dlData.ensureSize(8 * 128 * 1020, true);
	int dlDataSize = dlData.getSize();

	char filename[1024];
	int filenameSize = 1024;
	char msg[STR_SIZE];
	int msgSize = STR_SIZE;
	memset(&msg[0], 0, STR_SIZE);
	epoch = 0;

	if (burstLib.CloudDownloadStart(apiHandle,
		paramaters.downloadTransactionID.toRawUTF8(), paramaters.downloadTransactionID.getNumBytesAsUTF8(),
		0, 0))
	{
		float progress = 0.f;
		while (burstLib.CloudDownloadFinished(apiHandle,
			&msg[0], msgSize,
			paramaters.downloadTransactionID.toRawUTF8(), paramaters.downloadTransactionID.getNumBytesAsUTF8(),
			&filename[0], filenameSize,
			dlData.getData(), dlDataSize,
			epoch,
			progress) == false && !threadShouldExit())
		{
			setStatusMessage(String((int)(progress * 100.f)) + "%");
			setProgress(jmin<float>(jmax<float>(progress, 0.f), 1.f));
			Time::waitForMillisecondCounter(Time::getApproximateMillisecondCounter() + 100);
		}
		if (threadShouldExit())
			burstLib.CloudCancel(apiHandle, &msg[0], msgSize);
		else
		{
			dlData.setSize(dlDataSize, true);
			if (epoch > 0 && (dlDataSize > 0 || msgSize > 0)) // 2014-08-11 04:00:00 genesis
				downloadOk = true;
		}

		dlFilename = String(filename, filenameSize);

		allText = paramaters.downloadTransactionID + "\n";
		allText += dlFilename + "\n";
		allText += String(&msg[0], msgSize);

		ToLog(allText);
	}
}

void Interface::ProgressWindow::Upload()
{
	char jobId[STR_SIZE];
	int jobIdSize = STR_SIZE;
	memset(&jobId[0], 0, STR_SIZE);
	String filename = paramaters.fileToUpload.getFileName();

	txFeePlancks = 0;
	feePlancks = 0;
	burnPlancks = 0;
	costsNQT = 0;
	confirmTime = 0;

	if (burstLib.CloudUploadStart(apiHandle,
		&jobId[0], jobIdSize,
		paramaters.message.toUTF8(), paramaters.message.getNumBytesAsUTF8(),
		filename.toRawUTF8(), filename.getNumBytesAsUTF8(),
		paramaters.stackSize,
		paramaters.fee))
	{
		char uploadResult[STR_SIZE];
		int uploadResultSize = STR_SIZE;
		memset(&uploadResult[0], 0, STR_SIZE);
		
		float progress = 0.f;
		while (burstLib.CloudUploadFinished(apiHandle,
			&uploadResult[0], uploadResultSize,
			&jobId[0], jobIdSize,
			txFeePlancks,
			feePlancks,
			burnPlancks,
			costsNQT,
			confirmTime,
			progress) == false && !threadShouldExit())
		{
			setProgress(jmin<float>(jmax<float>(progress, 0.f), 1.f));
			Time::waitForMillisecondCounter(Time::getApproximateMillisecondCounter() + 100);
		}

		if (threadShouldExit())
		{
			char msg[STR_SIZE];
			int msgSize = STR_SIZE;
			burstLib.CloudCancel(apiHandle, &msg[0], msgSize);
		}
		else
		{
			uploadFinishMsg = String(&uploadResult[0], uploadResultSize);
			if (uploadFinishMsg.startsWith("CLOUD"))
			{
				SystemClipboard::copyTextToClipboard(uploadFinishMsg);
				uploadFinishMsg = ("All data has been send !\nPlease wait for the transaction(s) to be confirmed\n\n" + uploadFinishMsg + "\n\nThe download ID has been copied to the clipboard.");
			}
		}
	}
	else uploadFinishMsg = "failed to upload";

	ToLog(uploadFinishMsg);
}

int64 Interface::ProgressWindow::RecalcCosts()
{
	char jobId[STR_SIZE];
	int jobIdSize = STR_SIZE;
	memset(&jobId[0], 0, STR_SIZE);
	String filename = paramaters.fileToUpload.getFullPathName();
	
	txFeePlancks = 0;
	feePlancks = 0;
	burnPlancks = 0;
	costsNQT = 0;
	confirmTime = 0;

	if (burstLib.CloudCalcCostsStart(apiHandle,
		&jobId[0], jobIdSize,
		paramaters.message.toUTF8(), paramaters.message.getNumBytesAsUTF8(),
		filename.toRawUTF8(), filename.getNumBytesAsUTF8(),
		paramaters.stackSize,
		paramaters.fee))
	{
		char uploadResult[STR_SIZE];
		int uploadResultSize = STR_SIZE;
		memset(&uploadResult[0], 0, STR_SIZE);

		float progress = 0.f;
		while (burstLib.CloudCalcCostsFinished(apiHandle,
			&uploadResult[0], uploadResultSize,
			&jobId[0], jobIdSize,
			txFeePlancks,
			feePlancks,
			burnPlancks,
			costsNQT,
			confirmTime,
			progress) == false && !threadShouldExit())
		{
			setProgress(jmin<float>(jmax<float>(progress, 0.f), 1.f));
			Time::waitForMillisecondCounter(Time::getApproximateMillisecondCounter() + 100);
		}
		if (threadShouldExit())
		{
			char msg[STR_SIZE];
			int msgSize = STR_SIZE;
			burstLib.CloudCancel(apiHandle, &msg[0], msgSize);
		}
	}
	return costsNQT;
}

void Interface::ProgressWindow::Donate()
{
	char returnStr[STR_SIZE];
	int returnSize = STR_SIZE;
	const char *recipient = "BURST-72X9-E6F3-YSM2-CLQUD";
	burstLib.sendMoney(apiHandle, &returnStr[0], returnSize, recipient, strlen(recipient), 100000000, 735000 * 2, 24 * 60, true);
	sendMoneyResult = String(&returnStr[0], returnSize);
}

#define BIKELOCK "BIKELOCK95467231"
String Interface::Encrypt(String input)
{
	if (input.isEmpty())
		return String::empty;

	MemoryBlock memoryBlock;
	memoryBlock.loadFromHexString(String::toHexString(input.toUTF8(), (int)input.getNumBytesAsUTF8()));

	String encryptionKey(BIKELOCK, strlen(BIKELOCK));
	BlowFish blowFish(encryptionKey.toUTF8(), (int)encryptionKey.getNumBytesAsUTF8());
	blowFish.encrypt(memoryBlock);

	return memoryBlock.toBase64Encoding();
}

String Interface::Decrypt(String input)
{
	if (input.isEmpty())
		return String::empty;

	MemoryBlock memoryBlock;
	memoryBlock.fromBase64Encoding(input);

	String encryptionKey(BIKELOCK, strlen(BIKELOCK));
	BlowFish blowFish(encryptionKey.toUTF8(), (int)encryptionKey.getNumBytesAsUTF8());
	blowFish.decrypt(memoryBlock);

	return memoryBlock.toString();
}

void Interface::timerCallback()
{
	const juce::ScopedTryLock scopedLock(timerLock);
	if (!scopedLock.isLocked())
		return;

	parseCommandsCore();
}

bool Interface::parseCommands(const StringArray& cmds)
{
	const ScopedLock lock(cmdLock);

	this->cmdsArray.add(cmds);
	return true;
}

bool Interface::parseCommandsCore()
{
	const ScopedLock lock(cmdLock);

	if (cmdsArray.size() <= 0)
		return false;
	stopTimer();
	StringArray cmds = cmdsArray.getFirst();
	cmdsArray.remove(0);
	
	/*
	cloudburst
		-output "c:/consoleoutput.txt"
		-upload "c:/bla.txt"
			-msg "hello world !"
			-priority 1
			-stack 1
			-maxCostNQT

		-download CLOUD-XXX...
			-folder "c:\\foo"
	*/
	ToLog(cmds.joinIntoString(" "));

	String textOutput;

	if (cmds.contains("-download"))
	{
		SetParameterStruct();

		File downloadFolder;
		for (int i = 0; i < cmds.size(); i++)
		{ // set all params
			if (cmds[i].compareIgnoreCase("-download") == 0 && cmds.size() > i + 1)
			{
				paramaters.downloadTransactionID = (cmds[i + 1]);
			}
			if (cmds[i].compareIgnoreCase("-folder") == 0 && cmds.size() > i + 1)
			{
				downloadFolder = File(cmds[i + 1].unquoted());
			}
		}
		if (paramaters.downloadTransactionID.isNotEmpty() && downloadFolder.exists())
		{
			ProgressWindow progressThread(this, "Download...", 0, paramaters);
			progressThread.runThread();
			if (progressThread.allText.isNotEmpty())
				textOutput += (progressThread.allText) + "\n";
			if (progressThread.allText.isNotEmpty() || progressThread.downloadOk)
			{
				if (progressThread.dlData.getSize() > 0 && progressThread.dlFilename.isNotEmpty())
				{
					File saveFile = (downloadFolder.getChildFile(progressThread.dlFilename));
					if (!saveFile.existsAsFile()) // dont overwite existing files
					{
						saveFile.getParentDirectory().createDirectory();
						if (progressThread.dlData.getSize() > 0 && saveFile.existsAsFile() == false)
						{
							saveFile.appendData(progressThread.dlData.getData(), progressThread.dlData.getSize());
							textOutput += "\nSAVED:\n" + saveFile.getFullPathName() + "\n";
						}
					}
				}
			}
			else if (progressThread.epoch > 0)
				textOutput += ("The upload seems incomplete !\nIt is either broken or wait for confirmation.\n");
			else textOutput += ("Nothing found !\n");
		}
		else
		{
			textOutput += "ERROR: arguments incorrect; ";
			if (paramaters.downloadTransactionID.isEmpty())
				textOutput += "no txid\n";
			else textOutput += "dl folder does not exist\n";
		}
	}

	// -upload "E:\\temp\\testupload.txt" -msg "E:\\temp\\testupload.txt" -priority 2 -stack 2 -output "E:\\temp\\test.txt"
	if (cmds.contains("-upload"))
	{
		SetParameterStruct();
		paramaters.fileToUpload = File();
		paramaters.message.clear();
		paramaters.fee = 1;
		paramaters.stackSize = 1;

		int maxCostNQT = 1000000000;
		for (int i = 0; i < cmds.size(); i++)
		{ // set all params
			if (cmds[i].compareIgnoreCase("-upload") == 0 && cmds.size() > i + 1)
			{
				File file = File(cmds[i + 1].unquoted());
				if (file.getSize() < 8 * 128 * 1020 || passPhraseTextEditor->getText().endsWith(HERE_BE_DRAGONS))
				{
					String filename = file.getFileName();
					textOutput += (filename + " (" + String(fileToUpload.getSize() / 1000.f, 2) + " KB)") + "\n";
					paramaters.fileToUpload = file;
				}
				else textOutput += "ERROR: max is 1 MB !\n";
			}
			if (cmds[i].compareIgnoreCase("-msg") == 0 && cmds.size() > i + 1)
			{
				if (File(cmds[i + 1].unquoted()).existsAsFile())
				{
					paramaters.message = File(cmds[i + 1].unquoted()).loadFileAsString();
				}
				else paramaters.message = (cmds[i + 1].unquoted());
				textOutput += paramaters.message + "\n";
			}
			if (cmds[i].compareIgnoreCase("-priority") == 0 && cmds.size() > i + 1)
			{
				paramaters.fee = (unsigned int)jmin<int>(jmax<int>(String(cmds[i + 1].unquoted()).getIntValue(), 1), 100) * 735000;
				textOutput += "fee: " + String(paramaters.fee) + "\n";
			}
			if (cmds[i].compareIgnoreCase("-stack") == 0 && cmds.size() > i + 1)
			{
				paramaters.stackSize = jmin<int>(jmax<int>(String(cmds[i + 1].unquoted()).getIntValue(), 1), 1020);
				textOutput += "stackSize: " + String(paramaters.stackSize) + "\n";
			}
			if (cmds[i].compareIgnoreCase("-maxCostNQT") == 0 && cmds.size() > i + 1)
			{
				maxCostNQT = String(cmds[i + 1].unquoted()).getIntValue();
				textOutput += "maxCostNQT: " + String(maxCostNQT) + " planck\n";
			}
		}
				
		// check if all params are set. 
		// refresh costs and upload
		RefreshCosts();
		String neatNr(costsNQT);
		neatNr = neatNr.paddedLeft('0', 9);
		neatNr = neatNr.substring(0, neatNr.length() - 8) + "." + neatNr.substring(neatNr.length() - 8, neatNr.length());

		if (costsNQT > maxCostNQT)
			textOutput += ("Costs are too high !" + String(costsNQT) + " placnk\n");
		else
		{
			if (!paramaters.fileToUpload.existsAsFile() && paramaters.message.length() <= 0)
				textOutput += ("Nothing to upload !\n");
			else
			{
				if (confirmationSecs > (SEARCH_RANGE_MINUTES * 60))
					textOutput += ("The confirmation will probably take longer than " + RelativeTime(SEARCH_RANGE_MINUTES * 60).getDescription() + " !\nYou should use a higher stack size.\n");
				else
				{
					textOutput += "Upload " + neatNr + " BURST\n";

					ProgressWindow progressThread(this, "Upload... " + neatNr + " BURST", 1, paramaters);
					progressThread.runThread();

					textOutput += progressThread.uploadFinishMsg + "\n";
				}
			}
		}
	}

	textOutput += "-------------------\n";

	String outputFilePath;
	for (int i = 0; i < cmds.size(); i++)
	{ // set all params
		String str1(cmds[i]);
		if (str1.compareIgnoreCase("-output") == 0 && cmds.size() - 1 > i)
		{
			String str(cmds[i + 1]);
			outputFilePath = File::createLegalPathName(str.unquoted());
		}
	}
	if (outputFilePath.isNotEmpty())
	{
		File outputFile(outputFilePath);
		if (!outputFile.exists())
			outputFile.create();
		if (outputFile.exists())
			outputFile.appendText(textOutput);
	}

	if (cmds.contains("-quit", true))
	{
		JUCEApplication::quit();
	}

	cmds.clear();

	startTimer(1000);

	return true;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Interface" componentName=""
                 parentClasses="public Component, public TextEditorListener, public Timer"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="380">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 80 600 300" fill="solid: fff2f2f2" hasStroke="0"/>
    <RECT pos="0 380 600 300" fill="solid: ff00579d" hasStroke="0"/>
    <RECT pos="16 528 568 63" fill="solid: fff2f2f2" hasStroke="0"/>
  </BACKGROUND>
  <TEXTBUTTON name="new button" id="9f97bd07ba5128ac" memberName="syncButton"
              virtualName="" explicitFocusOrder="0" pos="100 195 400 48" tooltip="You will be asked for a location to save the file"
              buttonText="Download" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTEDITOR name="new text editor" id="ae20646702a5c87b" memberName="burstAddressTextEditor"
              virtualName="" explicitFocusOrder="0" pos="100 154 400 33" tooltip="The CLOUD id or numerical id of the file/message you want to download"
              initialText="" multiline="0" retKeyStartsLine="0" readonly="0"
              scrollbars="1" caret="1" popupmenu="1"/>
  <LABEL name="burstAddressLabel" id="515ff14449bef53a" memberName="burstAddressLabel"
         virtualName="" explicitFocusOrder="0" pos="100 119 400 29" edTextCol="ff000000"
         edBkgCol="0" labelText="CLOUD ID" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="18"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="fb4c396e279f7faa" memberName="versionLabel"
         virtualName="" explicitFocusOrder="0" pos="534 50 54 20" edTextCol="ff000000"
         edBkgCol="0" labelText="v0.1" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="1" italic="0" justification="34"/>
  <TEXTEDITOR name="new text editor" id="87957e73989795c1" memberName="logTextEditor"
              virtualName="" explicitFocusOrder="0" pos="100 256 400 101" textcol="ff00579d"
              bkgcol="ffffff" shadowcol="ffffff" initialText="" multiline="1"
              retKeyStartsLine="1" readonly="1" scrollbars="1" caret="0" popupmenu="1"/>
  <TEXTEDITOR name="messageTextEditor" id="9b333effc42d4382" memberName="messageTextEditor"
              virtualName="" explicitFocusOrder="0" pos="140 428 444 84" initialText=""
              multiline="1" retKeyStartsLine="1" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="addFileButton" id="b55e853f3b049743" memberName="addFileButton"
              virtualName="" explicitFocusOrder="0" pos="11 396 120 24" tooltip="Select a file to upload (1 MB max)"
              bgColOff="fff2f2f2" bgColOn="fff2f2f2" buttonText="Select file"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="costsLabel" id="479eda42bd72bd10" memberName="costsLabel"
         virtualName="" explicitFocusOrder="0" pos="272 534 304 52" tooltip="The total cost and confirmation speed depends on the size of the data (after max compression), the selected base fee and the stacked slots."
         textCol="ff000000" edTextCol="ff000000" edBkgCol="0" labelText="-"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="25" bold="0" italic="0" justification="34"/>
  <TEXTBUTTON name="sendButton" id="362b275688d9ed9e" memberName="sendButton"
              virtualName="" explicitFocusOrder="0" pos="424 636 160 32" tooltip="Upload your message and/or file to the Burst blockchain"
              bgColOff="fff2f2f2" bgColOn="fff2f2f2" buttonText="Upload" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <LABEL name="passPhraseLabel" id="b374e0cf387af521" memberName="passPhraseLabel"
         virtualName="" explicitFocusOrder="0" pos="10 606 120 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Secret pass phrase"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="34"/>
  <TEXTEDITOR name="new text editor" id="f0cbabb6811d2f5" memberName="passPhraseTextEditor"
              virtualName="" explicitFocusOrder="0" pos="140 606 444 24" tooltip="enter your pass phrase here"
              initialText="" multiline="0" retKeyStartsLine="0" readonly="0"
              scrollbars="0" caret="1" popupmenu="1"/>
  <LABEL name="messageLabel" id="b44efe580d0e72e6" memberName="messageLabel4"
         virtualName="" explicitFocusOrder="0" pos="200 396 384 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="no file selected"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="14" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="c8561c8705132bfa" memberName="feeSlider"
          virtualName="" explicitFocusOrder="0" pos="18 536 150 22" tooltip="Slot priority: the base fee for each part of the upload. A higher value gives more confirm priority. Putting this value low during a time of high traffic could cause your upload to partially fail and result in a unusable broken file !"
          min="1" max="1020" int="1" style="IncDecButtons" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <LABEL name="feeLabel" id="4d7a0986a6503fe9" memberName="feeLabel" virtualName=""
         explicitFocusOrder="0" pos="170 536 94 22" tooltip="Slot priority: the base fee for each part of the upload. A higher value gives more confirm priority. Putting this value low during a time of high traffic could cause your upload to partially fail and result in a unusable broken file !"
         textCol="ff000000" edTextCol="ff000000" edBkgCol="0" labelText="Slot priority"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="new button" id="a0c0f631653cc62f" memberName="removeFileButton"
              virtualName="" explicitFocusOrder="0" pos="141 396 56 24" tooltip="Remove the file from this upload"
              bgColOff="fff2f2f2" bgColOn="fff2f2f2" textCol="ff000000" textColOn="ff000000"
              buttonText="clear" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TOGGLEBUTTON name="new toggle button" id="1d7bff6e655d4d32" memberName="savePassPhraseToggleButton"
                virtualName="" explicitFocusOrder="0" pos="142 634 24 24" tooltip="Saves your pass phrase on this computer. It will be obscured but offers no guarantees of protection !"
                txtcol="ffffffff" buttonText="" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <LABEL name="passPhraseLabel" id="e4b14070796630a1" memberName="passPhraseLabel2"
         virtualName="" explicitFocusOrder="0" pos="10 428 120 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Message" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="34"/>
  <COMBOBOX name="new combo box" id="da97db377c3c4122" memberName="serverComboBox"
            virtualName="" explicitFocusOrder="0" pos="140 41 264 24" tooltip="Use a wallet that is well  connected (has peers). This will improve upload confirmation time."
            editable="1" layout="33" items="http://127.0.0.1:8125/&#10;https://wallet.burst.cryptoguru.org:8125/&#10;https://wallet.dev.burst-test.net/"
            textWhenNonSelected="http://127.0.0.1:8125/" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="93f0e05b4e1d4b53" memberName="serverLabel"
         virtualName="" explicitFocusOrder="0" pos="140 15 263 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Wallet" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="rememberLabel" id="90553a5f913e2d1d" memberName="rememberLabel"
         virtualName="" explicitFocusOrder="0" pos="173 634 88 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="remember" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <IMAGEBUTTON name="new button" id="c35d1ce1b36277e0" memberName="imageButton"
               virtualName="" explicitFocusOrder="0" pos="430 10 128 56" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="cloudburstlogosmall_png" opacityNormal="1" colourNormal="0"
               resourceOver="cloudburstlogosmall_png" opacityOver="1" colourOver="0"
               resourceDown="cloudburstlogosmall_png" opacityDown="1" colourDown="0"/>
  <TEXTBUTTON name="new button" id="796cb7ac8d9b1126" memberName="tabButton1"
              virtualName="" explicitFocusOrder="0" pos="11 9 120 24" buttonText="Download"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="84bc929735a69dec" memberName="tabButton2"
              virtualName="" explicitFocusOrder="0" pos="11 41 120 24" buttonText="Upload"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="disclaimerLabel" id="340cd006b09c5456" memberName="disclaimerLabel"
         virtualName="" explicitFocusOrder="0" pos="664 112 392 216" bkgCol="ffffffff"
         textCol="ffff0000" outlineCol="ff000000" edTextCol="ff000000"
         edBkgCol="0" labelText="DISCLAIMER&#10;Any uploaded data will be PUBLIC ! You hold sole responsibility for the contents that is uploaded. &#10;&#10;No warranties or guarantees are given to the user of this software.&#10;&#10;Using new wallet with limited funds is recommended !"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="1" italic="0" justification="33"/>
  <TEXTBUTTON name="disclaimerButton" id="82d693671c30505c" memberName="disclaimerButton"
              virtualName="" explicitFocusOrder="0" pos="664 336 392 24" buttonText="Okay, I got it !"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <SLIDER name="stackSizeSlider" id="3a8aa9339e836109" memberName="stackSizeSlider"
          virtualName="" explicitFocusOrder="0" pos="18 562 150 22" tooltip="Higher slot stacking will speed up confirmation of the upload but the total costs will be higher."
          min="1" max="1020" int="1" style="IncDecButtons" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <LABEL name="dropSizeLabel" id="27124cdba4f5f7" memberName="dropSizeLabel2"
         virtualName="" explicitFocusOrder="0" pos="170 562 94 22" tooltip="Higher slot stacking will speed up confirmation of the upload but the total costs will be higher."
         textCol="ff000000" edTextCol="ff000000" edBkgCol="0" labelText="Slot stacking"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="5b7105aba36f1fb" memberName="donateLabel"
         virtualName="" explicitFocusOrder="0" pos="704 440 320 80" edTextCol="ff000000"
         edBkgCol="0" labelText="The first decentralised cloud file storage !&#10;For more info please visit"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="16" bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="okayButton" id="ad1eddda5aacb301" memberName="okayButton"
              virtualName="" explicitFocusOrder="0" pos="704 592 168 24" buttonText="Okay"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <HYPERLINKBUTTON name="new hyperlink" id="c6b248828b3c9e7e" memberName="hyperlinkButton"
                   virtualName="" explicitFocusOrder="0" pos="664 520 400 40" tooltip="https://github.com/CurbShifter/CloudBurstDAPP"
                   textCol="cc00579d" buttonText="CloudBurst DAPP" connectedEdges="0"
                   needsCallback="0" radioGroupId="0" url="https://github.com/CurbShifter/CloudBurstDAPP"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//==============================================================================
// Binary resources - be careful not to edit any of these sections!

// JUCER_RESOURCE: cloudburstlogosmall_png, 8950, "burst/cloudburst-logo-small.png"
static const unsigned char resource_Interface_cloudburstlogosmall_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,200,0,0,0,107,8,6,0,0,0,50,208,205,222,0,0,0,9,112,72,89,115,0,0,23,18,0,
0,23,18,1,103,159,210,82,0,0,0,32,99,72,82,77,0,0,122,37,0,0,128,131,0,0,249,255,0,0,128,233,0,0,117,48,0,0,234,96,0,0,58,152,0,0,23,111,146,95,197,70,0,0,34,124,73,68,65,84,120,218,236,157,121,148,28,
87,117,255,63,85,213,203,172,146,70,51,146,181,239,18,178,44,107,179,141,141,101,140,49,193,56,9,222,98,126,192,47,39,54,54,33,144,176,4,7,2,1,2,230,132,152,67,32,14,33,196,113,130,249,25,12,14,203,15,
147,32,47,177,177,45,176,45,201,155,144,100,203,90,61,218,53,26,141,164,145,102,211,44,61,211,221,85,249,227,189,214,188,174,233,238,122,175,166,167,71,210,244,247,156,62,179,116,45,175,94,221,251,238,
126,159,197,7,30,164,140,156,152,15,188,21,88,8,204,5,230,1,83,129,26,192,5,58,128,86,96,47,176,95,126,94,4,142,156,247,51,99,71,136,245,30,103,246,238,31,96,185,105,176,172,243,246,81,35,101,62,200,194,
213,192,13,192,85,192,69,64,109,129,99,167,203,159,215,40,255,107,7,118,2,235,129,53,192,171,229,41,45,51,200,185,142,42,224,125,192,199,128,43,135,121,173,58,96,181,252,124,14,216,0,252,187,100,150,254,
242,84,159,131,194,114,140,63,251,71,128,205,192,143,138,192,28,126,56,192,59,128,159,3,27,129,15,150,201,173,204,32,231,10,174,4,214,1,223,7,22,151,224,126,203,128,159,1,207,1,171,202,100,87,102,144,
179,249,121,63,11,172,149,106,80,169,113,13,240,2,240,23,101,210,43,51,200,217,134,58,224,167,192,189,64,229,40,142,163,6,184,31,120,80,254,94,70,153,65,70,29,211,128,255,1,62,112,22,141,233,195,192,83,
64,67,153,12,207,94,68,198,8,115,60,9,44,31,198,53,58,129,38,249,179,71,26,224,85,82,42,77,167,176,59,184,16,174,2,126,5,220,4,180,149,201,177,204,32,165,70,173,36,192,48,204,177,83,50,214,139,8,79,87,
11,144,242,29,19,7,166,0,151,73,155,230,6,68,128,209,148,73,126,9,188,23,232,45,147,100,153,65,74,5,11,120,0,17,13,55,193,26,224,7,192,111,52,8,182,31,56,36,63,191,4,190,10,92,7,220,1,252,161,193,61,223,
9,220,39,213,174,50,202,54,72,73,112,55,102,177,135,151,129,235,129,91,128,199,67,174,230,93,138,52,184,5,120,221,224,220,59,129,79,151,73,178,204,32,35,129,168,180,9,170,165,125,240,54,224,111,13,206,
255,103,224,90,224,233,34,142,105,13,34,80,120,159,193,57,95,3,150,148,201,178,172,98,13,7,245,146,136,222,133,200,151,154,1,140,67,184,110,109,224,52,34,169,48,170,113,173,1,169,214,252,100,132,198,218,
5,124,10,216,33,25,197,9,56,126,28,34,53,229,247,128,100,153,60,203,12,162,139,184,84,127,110,151,210,97,106,17,174,57,128,200,193,122,188,4,227,255,15,224,20,240,159,64,44,224,216,171,129,247,143,32,
211,150,113,30,169,88,149,210,224,125,85,170,44,127,84,36,230,112,17,121,88,143,151,240,89,30,1,254,74,243,216,47,81,14,34,150,25,36,0,239,66,100,195,254,144,225,197,48,114,225,27,192,195,163,240,76,247,
3,223,209,56,110,137,92,12,202,40,51,200,16,84,72,2,126,134,145,73,236,219,36,175,63,90,248,18,34,198,18,132,79,107,168,99,101,140,49,6,153,6,60,10,124,97,132,198,150,0,254,18,17,13,31,45,244,1,159,145,
106,94,33,172,2,86,150,73,180,204,32,25,204,7,158,69,4,218,70,10,143,34,226,29,163,141,167,129,231,53,142,251,195,50,137,150,25,4,96,54,34,153,112,36,99,0,189,192,55,207,162,185,255,182,198,49,183,150,
213,172,209,197,217,224,230,173,65,120,120,222,18,226,220,52,176,7,216,141,136,57,88,242,122,11,129,5,210,158,201,224,17,224,181,179,104,238,159,1,26,129,69,5,142,89,0,76,2,154,203,164,58,118,25,228,95,
17,201,126,38,120,5,120,8,120,9,209,85,164,207,247,125,12,152,35,63,75,165,62,127,239,89,54,247,73,224,255,3,95,41,112,76,12,248,60,194,147,247,134,134,221,82,198,121,198,32,119,200,143,46,214,35,114,
172,214,5,16,203,128,92,157,27,229,74,125,182,226,249,0,6,65,58,21,62,46,25,228,191,16,137,148,199,202,164,123,254,219,32,13,136,220,35,29,244,35,50,101,175,149,68,117,190,172,164,123,129,110,205,133,
108,21,240,117,96,171,100,170,114,161,213,121,206,32,95,2,102,106,28,215,41,141,213,175,49,180,30,227,92,199,73,249,49,193,100,57,23,91,128,255,91,38,225,243,147,65,22,2,127,174,113,220,105,68,218,248,
255,156,167,243,223,135,40,196,10,131,153,136,26,251,135,17,73,142,101,156,71,12,242,199,232,53,78,184,11,209,42,231,124,133,7,28,24,230,53,254,4,81,249,56,175,76,206,231,7,131,212,0,183,105,28,247,51,
105,144,158,239,120,179,8,215,88,141,8,62,46,45,221,176,173,50,131,140,16,46,39,184,110,187,3,248,242,24,89,164,118,48,212,77,29,6,11,128,39,128,89,165,96,14,59,157,192,114,83,231,117,227,106,40,141,155,
119,26,162,134,99,169,124,121,58,49,143,31,33,186,165,143,5,172,145,115,51,67,218,21,115,16,193,195,43,40,28,68,204,133,217,136,216,202,239,49,162,249,102,22,78,186,31,203,75,227,89,118,153,65,66,160,
26,209,225,227,54,41,49,234,13,206,29,64,52,91,40,52,230,233,242,30,25,105,115,52,199,113,81,69,66,122,242,186,65,136,203,107,103,34,240,167,128,227,57,142,171,82,174,157,246,73,0,245,187,20,34,65,178,
26,17,244,243,124,58,74,18,225,230,221,159,99,65,168,146,115,247,97,68,97,87,133,230,252,93,1,252,147,166,19,36,36,127,216,196,251,142,9,6,209,42,220,44,171,88,42,129,221,133,112,65,254,12,248,3,67,230,
200,168,28,187,242,40,189,127,37,175,189,19,17,15,216,42,143,127,210,167,182,213,33,218,245,108,147,159,7,52,24,250,31,228,177,219,149,107,239,68,120,208,230,251,84,153,109,242,187,157,192,61,190,239,
182,43,223,253,153,156,227,245,210,214,104,84,62,111,202,231,220,32,137,217,175,171,244,74,7,197,109,82,234,62,98,48,135,31,67,84,37,142,152,111,33,214,223,62,38,236,144,98,74,144,183,35,138,129,134,91,
195,177,217,183,210,102,164,193,195,228,238,140,56,1,248,125,169,127,175,70,52,96,155,235,83,229,214,23,184,223,20,68,101,225,165,57,190,155,40,153,124,174,84,19,59,17,205,174,85,143,81,167,207,190,154,
171,252,189,85,170,76,133,210,214,103,200,113,79,39,127,84,125,187,36,248,59,17,169,57,213,26,243,120,15,240,107,68,142,90,17,165,135,133,149,78,80,209,221,12,182,115,222,51,72,177,36,200,39,164,23,165,
24,5,78,185,18,10,255,218,199,28,109,82,146,156,86,254,183,152,193,45,12,174,240,157,255,219,2,247,251,119,31,115,52,201,49,36,148,255,93,168,92,211,159,113,252,186,207,155,164,74,128,55,228,185,126,201,
112,42,135,97,254,33,130,93,223,63,4,110,70,108,212,19,132,133,242,189,20,89,189,138,82,209,125,132,120,162,21,215,138,148,25,68,3,255,128,232,216,81,172,134,208,254,106,187,10,68,253,120,6,71,228,74,
125,9,67,187,164,215,231,96,144,148,148,74,185,176,20,184,81,249,123,45,98,171,130,92,201,141,23,200,159,239,244,73,143,77,62,38,85,199,217,33,175,167,226,78,105,124,175,64,164,154,100,48,78,218,29,65,
88,43,23,11,29,207,215,159,81,236,32,162,101,83,211,181,31,203,29,27,77,87,134,203,32,223,0,254,166,136,227,73,200,21,220,111,116,170,42,205,143,21,194,58,237,59,54,147,196,167,122,127,78,144,63,93,252,
86,223,28,124,75,18,53,57,84,147,19,82,233,86,37,194,126,6,35,225,85,190,113,238,83,152,48,131,164,100,168,54,105,135,28,243,73,150,1,205,121,122,22,189,38,115,115,41,118,58,138,151,164,162,231,8,88,78,
153,65,2,240,73,68,105,108,49,209,38,213,15,21,203,11,168,96,239,240,125,215,40,37,206,28,229,127,7,115,48,82,6,43,148,223,251,200,14,218,45,243,17,246,155,136,142,42,83,148,255,239,81,236,165,169,100,
119,92,217,38,25,234,18,223,241,25,102,173,245,217,43,135,209,75,92,204,224,251,210,238,10,194,251,139,166,74,219,81,42,186,155,169,236,62,130,107,143,141,221,251,194,62,229,42,224,31,67,156,151,66,236,
12,219,14,140,71,20,3,169,21,115,93,57,86,110,117,197,118,125,106,73,2,177,133,0,8,87,239,33,68,225,149,154,233,154,47,82,237,72,175,83,6,205,190,21,221,47,133,14,73,134,140,43,255,223,229,83,215,98,190,
85,126,154,239,30,155,25,220,171,112,186,162,182,101,198,233,25,206,231,221,136,238,47,133,212,219,171,165,221,180,125,248,234,149,67,77,231,30,236,116,2,215,169,40,51,72,1,169,115,31,250,126,121,128,
199,128,255,102,176,75,122,143,84,73,38,201,85,55,19,32,107,39,59,149,221,246,173,242,109,114,165,205,32,87,123,209,43,200,238,96,152,175,6,189,129,236,108,226,253,138,138,83,239,83,151,246,202,113,45,
45,96,47,169,210,172,95,26,239,203,125,99,81,25,106,165,111,254,119,133,116,104,60,69,225,22,65,17,233,132,24,30,131,88,22,86,170,151,218,246,157,120,214,216,217,251,53,204,147,222,129,112,121,234,96,
157,92,229,94,200,99,111,180,81,56,23,105,6,112,177,79,93,10,242,224,172,246,73,156,87,242,28,55,79,74,177,12,118,40,191,95,226,147,66,153,132,201,107,148,255,245,32,54,231,204,224,34,229,247,163,136,
52,118,191,123,119,135,111,101,199,167,146,133,193,247,8,238,161,117,9,162,2,115,24,234,85,156,154,246,215,137,247,157,192,181,199,78,153,188,169,110,90,129,112,185,234,224,71,136,118,161,47,12,99,124,
243,124,158,157,23,53,212,16,85,53,58,37,189,73,185,240,118,223,223,47,248,212,165,92,118,207,50,31,179,102,164,89,204,39,113,50,81,241,107,125,204,186,47,143,199,171,147,252,158,182,32,188,66,112,133,
225,69,195,166,20,55,201,248,147,175,51,214,96,202,32,55,51,212,175,159,207,128,188,131,225,39,225,249,119,160,221,24,112,124,141,143,80,15,42,94,169,92,171,170,170,18,109,207,99,247,164,17,77,33,26,164,
77,225,87,187,144,118,207,236,28,146,98,137,111,44,7,20,143,215,92,159,199,43,108,25,109,23,193,25,193,243,8,191,11,22,216,49,42,79,31,164,186,115,223,152,146,30,97,84,172,91,53,142,217,136,72,55,41,6,
252,65,185,61,202,239,83,21,227,52,83,120,180,194,71,196,141,121,36,142,133,8,164,101,208,194,96,62,151,67,118,192,243,164,36,236,213,62,105,182,211,199,108,106,82,210,90,105,95,169,30,175,77,12,238,57,
226,247,120,237,25,230,60,29,10,248,190,14,145,21,112,58,220,229,61,234,90,55,97,145,198,35,50,166,24,196,68,130,84,19,188,91,83,18,209,133,163,88,91,137,169,246,71,135,66,8,85,136,232,248,118,249,249,
150,162,2,89,62,162,204,133,11,124,43,248,1,69,218,205,244,49,230,1,249,92,215,250,174,177,43,143,196,73,74,117,105,177,129,199,107,203,48,231,233,68,192,247,113,223,88,140,164,71,69,247,33,106,219,119,
143,57,233,97,202,32,111,35,184,134,252,55,195,180,57,84,76,241,173,228,135,25,172,223,158,38,37,64,165,252,28,200,65,168,30,34,17,48,23,46,69,228,112,101,176,91,249,125,62,217,30,186,117,242,167,26,143,
25,240,49,223,133,62,98,109,241,49,183,223,64,191,38,135,51,35,143,247,200,6,59,70,64,98,96,80,128,209,33,180,75,223,165,161,101,61,150,151,98,172,20,73,133,101,144,11,53,102,168,152,181,227,243,201,78,
147,120,89,209,249,103,147,237,62,221,150,195,102,233,40,160,122,44,45,64,160,11,125,223,109,82,198,163,26,225,106,60,102,129,79,93,242,200,78,73,233,245,49,212,18,159,13,145,187,236,214,142,16,237,111,
99,226,177,245,50,49,48,239,244,7,165,147,36,209,137,210,91,118,246,199,169,160,162,187,137,234,206,253,184,118,148,177,8,147,85,101,70,192,247,3,20,206,154,53,197,172,2,42,205,13,62,15,208,58,105,3,248,
9,181,53,207,181,103,251,254,86,137,93,237,135,155,146,234,79,149,207,158,104,99,112,7,168,171,125,204,243,152,252,185,194,55,150,12,19,172,70,228,146,169,182,76,182,138,100,57,32,9,114,82,243,115,212,
181,110,198,179,28,218,167,172,134,116,127,174,231,153,22,48,151,189,228,43,160,178,108,113,47,47,141,157,236,198,242,188,193,42,65,171,159,250,150,23,177,188,20,158,21,43,51,72,0,198,7,124,127,82,122,
106,138,5,127,239,171,79,73,79,204,44,224,79,149,255,255,26,81,212,180,210,167,2,78,67,236,210,100,249,36,230,151,24,154,210,241,47,82,250,93,138,216,128,51,131,255,150,30,166,241,62,99,127,5,98,95,195,
211,136,130,166,152,178,72,60,130,104,205,51,205,199,236,207,72,70,187,204,103,127,252,243,153,107,75,198,136,246,182,80,213,211,76,52,113,138,218,246,93,164,34,213,76,110,122,134,68,213,84,250,198,205,
243,51,137,237,179,167,114,225,24,67,82,120,44,112,226,56,253,237,140,63,181,149,170,238,38,226,189,45,224,201,199,180,44,44,207,197,73,245,141,73,219,35,12,131,196,52,86,169,98,166,120,110,70,4,19,43,
20,21,231,239,125,199,28,102,176,134,226,18,159,218,53,3,209,61,197,143,79,34,82,243,213,120,206,149,12,166,202,103,208,196,96,93,124,151,148,36,215,41,78,130,92,158,186,47,34,226,46,215,248,60,94,117,
192,187,115,28,127,63,240,11,44,7,156,40,145,254,14,234,142,191,194,248,147,175,19,29,232,196,179,236,51,196,105,185,41,166,30,120,148,166,183,220,78,50,62,1,220,20,62,123,172,16,26,179,84,44,39,6,110,
138,186,99,47,81,119,252,21,226,137,19,120,150,147,51,66,126,190,151,212,22,211,6,9,34,254,56,193,155,84,230,244,146,224,84,12,253,216,145,189,192,71,201,239,154,124,26,172,247,96,217,123,20,6,9,194,46,
41,233,214,74,226,207,247,76,79,2,215,99,71,247,96,199,192,142,122,96,125,10,248,93,158,227,155,16,169,247,223,206,225,125,203,53,143,175,2,119,98,217,159,192,169,32,146,234,166,161,105,45,179,119,61,
72,253,209,23,112,82,125,164,157,138,172,149,219,179,35,196,19,173,52,52,63,231,207,164,189,153,224,237,218,182,101,164,2,78,156,170,174,3,204,216,243,83,166,28,122,156,232,64,7,105,167,18,215,142,225,
89,246,144,207,88,135,137,4,9,106,2,80,143,112,159,234,251,218,45,155,113,39,183,16,235,111,195,203,188,116,169,3,119,79,88,68,127,213,244,135,177,120,5,55,125,53,120,75,133,157,97,237,193,178,183,96,
57,235,73,39,112,146,189,164,99,227,1,239,199,224,189,128,63,238,225,157,209,214,44,240,154,5,113,89,224,166,190,14,94,166,10,113,177,226,205,122,13,120,25,39,78,117,251,46,234,90,55,209,53,113,41,93,
19,151,54,98,199,174,193,75,95,135,231,173,4,111,50,88,199,176,172,109,88,246,122,60,79,216,59,94,26,60,247,9,233,181,242,178,84,26,219,73,131,125,18,203,218,5,158,231,36,187,153,208,178,158,9,39,183,
16,75,180,225,218,209,130,73,128,105,39,206,184,182,109,116,54,172,160,119,252,66,72,39,170,17,189,123,131,176,73,216,52,46,13,71,214,82,223,178,30,203,75,147,30,35,9,135,165,98,144,163,1,223,87,73,53,
101,175,9,131,76,56,185,133,218,142,55,73,43,171,165,5,212,31,123,137,238,241,11,232,172,95,190,103,160,162,126,143,235,8,55,190,157,78,16,73,245,81,213,117,128,154,206,61,68,251,219,57,93,183,132,142,
134,149,47,123,150,237,75,76,244,192,178,73,59,149,66,133,176,35,68,251,91,137,14,116,209,51,126,1,88,206,86,220,212,214,236,49,89,224,84,50,254,248,43,76,57,244,4,182,155,164,166,163,145,186,19,27,233,
170,95,222,219,91,51,115,77,58,82,185,198,179,34,88,110,10,39,157,32,150,104,165,182,125,39,120,30,199,103,191,151,116,180,230,0,110,242,192,160,174,31,133,116,146,120,79,51,78,186,159,120,223,9,42,187,
155,168,232,57,74,44,113,10,207,142,104,18,171,133,229,165,169,111,89,207,64,213,5,164,162,53,139,128,70,60,118,74,9,46,245,49,43,34,45,109,11,232,7,119,83,188,231,40,147,143,60,75,117,199,94,92,59,130,
103,151,183,29,209,34,81,62,240,160,238,177,55,33,90,212,20,194,207,49,41,208,177,35,204,220,253,16,213,167,15,12,53,4,61,15,219,77,10,61,60,82,113,198,205,104,187,73,236,244,0,150,252,14,203,193,114,
83,184,78,44,143,74,96,225,217,81,92,59,130,235,196,137,246,119,224,164,19,156,174,91,76,235,140,119,51,80,57,89,232,243,94,90,120,116,176,168,63,182,129,134,230,231,1,239,140,100,179,220,36,150,231,225,
58,241,51,247,178,60,87,142,167,31,60,23,11,151,158,113,243,104,94,240,65,210,145,170,51,6,111,109,199,46,38,30,123,133,120,239,81,108,55,5,158,43,199,229,12,74,78,147,151,230,165,73,69,107,233,173,157,
131,103,71,6,5,149,39,88,34,21,173,25,188,174,101,19,239,61,65,117,103,35,78,58,81,42,131,123,156,252,212,40,106,124,82,106,23,93,20,47,144,124,86,49,200,36,169,54,76,42,112,76,151,244,210,52,234,49,72,
148,73,77,79,83,223,178,222,175,90,212,33,138,177,196,219,244,220,51,174,40,47,179,202,15,137,9,120,170,66,99,33,34,227,221,64,187,133,215,2,222,17,60,239,128,103,57,39,177,44,236,244,0,233,104,21,109,
83,174,164,99,210,165,164,99,227,192,77,50,229,224,99,212,157,248,157,144,104,150,125,43,34,169,209,83,239,99,121,158,98,196,158,25,203,1,224,187,118,58,65,239,184,121,52,45,186,13,219,77,50,229,208,227,
212,182,109,7,108,92,59,242,17,176,116,18,7,83,136,106,205,54,233,65,251,34,190,72,184,229,165,177,220,52,131,110,167,33,122,229,160,55,208,178,187,93,43,154,192,178,218,164,71,171,73,142,183,163,72,116,
52,19,145,101,241,78,68,185,193,84,201,32,49,178,219,35,101,50,184,247,73,59,239,121,130,55,53,186,89,58,61,188,81,224,143,30,19,6,201,184,84,223,19,112,204,99,82,218,104,176,167,5,216,204,216,243,19,
106,58,26,201,168,81,114,146,71,98,47,193,19,136,128,221,67,192,227,150,231,38,44,55,201,64,69,61,237,83,174,36,222,219,194,132,19,191,83,153,117,45,162,32,73,7,15,33,234,205,177,221,1,78,79,184,144,72,
170,155,202,211,135,51,207,101,33,98,30,139,53,174,117,28,145,96,216,43,93,207,191,43,242,60,120,146,81,94,68,148,48,63,41,9,216,20,171,17,165,191,239,33,92,237,187,135,136,157,253,29,249,27,107,232,208,
220,72,161,197,212,77,161,19,41,191,17,221,148,120,105,144,31,155,115,19,3,149,13,162,149,165,192,220,17,122,224,201,136,54,62,191,0,94,244,44,251,15,92,39,78,116,160,147,11,14,62,193,248,214,45,42,115,
56,100,39,20,6,225,76,138,141,107,199,168,233,216,77,69,207,81,149,233,39,145,93,65,88,8,207,43,106,200,91,71,96,30,44,249,108,239,147,11,218,111,25,154,254,95,8,115,16,25,219,27,128,255,67,248,198,16,
22,34,208,250,27,68,133,170,95,223,172,97,100,247,173,12,194,86,83,6,249,57,122,105,217,223,66,108,117,28,12,55,69,42,62,129,163,115,111,17,250,180,208,24,86,149,224,225,87,73,134,255,184,103,57,194,174,
200,78,167,152,193,208,136,123,33,100,57,39,60,59,234,183,47,86,74,213,81,7,106,250,250,101,37,152,139,12,145,234,52,21,191,78,46,6,31,41,242,24,254,26,81,252,101,251,24,113,250,40,50,200,155,166,12,210,
138,8,110,233,172,12,255,4,60,40,87,237,194,72,247,147,168,157,77,247,132,69,216,94,18,224,170,18,78,194,191,73,61,55,23,3,85,107,94,163,151,224,148,243,11,13,198,164,218,112,11,74,52,15,81,68,223,173,
171,2,180,131,53,140,92,131,236,63,37,59,75,98,46,163,187,201,83,99,152,155,127,7,253,148,146,15,35,42,222,238,145,43,104,193,251,181,79,186,4,207,138,212,82,146,14,229,89,248,71,134,214,216,155,52,142,
222,65,176,27,220,228,122,153,202,195,170,18,207,133,131,232,220,152,43,53,254,42,68,59,217,202,17,30,195,61,136,218,21,8,183,243,113,49,177,35,76,10,244,105,68,143,220,95,105,30,63,23,209,92,225,243,
136,72,246,17,68,93,121,58,75,226,120,222,33,215,174,248,138,103,217,211,240,188,201,37,110,171,191,64,170,14,143,41,255,91,108,112,254,27,26,70,174,110,217,107,151,178,0,77,53,176,91,138,133,21,210,238,
81,19,79,27,164,116,169,42,193,253,39,35,66,5,255,198,208,186,253,82,226,56,176,53,108,121,216,26,68,203,206,191,48,20,225,203,24,218,105,80,178,136,253,88,108,160,13,219,29,152,235,218,177,209,40,91,
187,209,199,32,38,170,205,30,141,151,190,204,128,217,142,43,99,136,143,194,92,92,233,99,144,175,148,80,213,3,209,203,224,254,81,54,208,155,128,142,225,16,226,93,242,197,223,90,156,241,88,79,199,18,167,
192,115,23,27,158,232,223,216,211,14,169,183,170,6,121,53,217,205,231,76,140,234,124,94,159,9,6,234,154,167,24,207,195,153,139,176,239,87,245,156,205,199,124,43,133,99,136,100,211,109,136,12,236,203,201,
221,28,60,31,166,75,213,114,2,193,27,183,122,242,57,117,85,14,15,61,151,246,174,225,76,32,136,236,208,59,229,4,92,55,108,254,112,147,123,42,187,155,192,178,87,27,156,245,20,67,93,202,25,73,245,57,10,39,
13,250,81,233,51,168,167,25,76,120,208,62,131,38,251,7,54,134,52,236,127,137,216,42,219,255,76,151,0,159,53,180,129,84,181,238,79,8,206,228,86,241,31,136,86,79,254,90,156,79,73,251,85,103,241,170,71,228,
254,233,44,16,147,17,222,72,93,245,239,179,136,108,238,32,156,18,12,226,196,192,77,139,84,139,112,246,200,141,8,159,248,109,161,153,195,178,6,236,116,98,95,44,209,102,121,150,179,204,224,204,13,12,109,
118,13,98,219,129,223,74,117,101,162,46,139,42,191,47,51,144,66,199,41,174,7,107,151,34,9,77,24,235,233,60,115,177,25,17,87,217,72,112,77,79,6,153,44,231,10,68,119,26,19,38,205,167,118,223,39,181,14,157,
103,138,33,58,205,236,212,60,86,215,113,208,47,205,3,237,141,83,237,73,135,127,77,116,160,19,34,149,97,27,18,247,3,183,35,82,211,79,133,99,16,231,132,147,236,57,226,164,122,38,121,216,211,12,25,36,31,
154,201,238,67,21,132,206,144,30,167,205,4,167,108,44,212,188,86,7,131,13,28,234,8,174,226,84,177,63,64,42,153,108,22,154,113,18,44,65,63,22,52,32,37,71,144,3,66,7,189,26,170,21,202,24,117,213,171,67,
228,239,147,150,155,65,26,90,214,51,123,247,131,52,28,126,154,232,64,123,166,22,35,12,153,127,31,225,10,124,24,227,100,52,123,127,172,191,109,192,78,247,207,197,178,106,12,38,177,208,74,96,97,86,159,162,
118,149,55,113,47,6,17,94,156,236,242,219,160,23,216,170,232,225,117,6,139,212,193,160,73,54,120,166,237,138,36,213,37,190,189,20,206,193,171,70,127,183,177,118,178,247,103,41,132,229,6,207,117,8,195,
162,62,59,237,84,224,36,123,105,56,250,28,115,118,61,200,164,166,167,137,37,78,9,70,49,151,40,187,165,52,185,74,234,155,187,53,85,172,13,85,221,77,88,94,122,161,193,189,154,201,189,127,96,6,181,100,215,
145,7,33,211,162,180,6,179,72,126,16,131,204,50,240,0,237,87,84,189,75,13,136,250,24,133,51,28,106,12,231,34,67,232,151,27,74,176,66,122,250,20,244,93,214,135,209,79,78,188,170,136,239,106,8,34,32,202,
42,61,167,2,59,149,160,254,232,243,76,104,221,76,71,195,74,218,47,184,156,84,124,34,184,73,83,27,229,53,249,249,162,52,180,46,151,162,112,129,156,36,181,143,141,5,222,198,168,216,243,206,132,48,15,82,
184,83,199,84,116,162,248,131,246,199,102,197,155,101,162,218,236,208,240,142,69,13,9,19,134,238,146,85,8,7,2,164,246,69,6,78,135,180,162,174,153,172,206,65,234,211,10,3,99,191,81,243,184,106,204,210,
129,94,10,197,32,103,220,49,25,70,73,247,83,223,178,142,241,109,219,232,154,184,148,246,11,222,74,50,222,32,235,24,114,56,113,100,86,46,184,224,186,98,142,69,78,85,2,209,172,224,25,69,204,87,103,49,136,
229,88,118,178,183,61,222,219,98,121,118,228,74,131,177,7,197,30,150,26,120,233,78,40,186,169,73,122,67,11,193,77,167,23,133,92,225,76,226,14,65,221,100,46,54,120,166,83,138,186,105,18,24,12,146,14,9,
68,174,149,142,100,248,185,230,61,167,27,44,130,105,233,180,9,207,32,126,70,113,146,221,212,183,172,103,220,169,55,232,152,180,138,222,113,243,132,199,43,75,61,178,177,83,125,84,246,52,147,138,213,210,
51,126,1,201,104,45,222,25,21,205,19,140,229,121,72,238,57,157,101,38,56,49,234,143,60,75,188,175,117,156,235,196,139,185,26,188,221,144,48,59,67,16,244,33,141,149,83,247,122,174,162,251,199,12,87,198,
237,69,100,210,102,229,153,76,210,25,46,70,100,245,230,155,143,39,208,219,240,199,4,38,210,185,141,224,116,32,61,6,25,100,20,135,180,227,224,164,250,104,104,126,1,239,232,250,60,214,176,119,102,83,249,
180,83,73,42,54,142,100,188,142,254,202,73,12,84,212,51,80,209,64,218,169,32,29,169,200,158,115,203,102,98,243,111,152,120,252,101,92,39,54,141,236,45,7,130,86,131,160,66,155,183,25,204,195,227,33,137,
73,199,75,182,196,128,48,119,42,99,152,169,121,158,23,224,193,50,125,166,23,149,223,77,154,143,79,70,212,199,223,67,233,96,242,92,77,132,40,16,211,82,65,132,68,137,21,124,67,25,70,182,220,20,177,68,43,
241,190,227,212,180,239,4,108,60,59,130,107,199,196,182,93,150,117,166,14,196,242,60,156,100,55,158,232,26,184,204,64,37,58,25,176,26,92,99,96,104,119,1,255,169,172,152,38,193,197,32,39,68,61,133,183,
128,246,219,84,61,138,190,174,187,50,118,146,189,169,80,46,111,222,124,131,103,122,94,249,125,139,161,161,254,5,169,78,111,44,17,131,172,54,92,204,140,171,18,139,159,74,108,89,120,150,100,8,167,66,214,
111,91,88,238,0,145,84,47,145,100,207,153,159,78,170,87,214,84,91,48,180,47,85,16,49,229,91,13,22,34,92,206,186,204,246,128,226,13,155,98,200,32,65,198,228,44,244,93,155,123,125,207,160,139,163,20,142,
63,93,104,96,207,116,251,136,219,180,207,114,53,240,3,74,147,96,233,160,159,223,166,227,76,9,47,65,12,6,60,45,183,222,106,9,198,41,124,190,137,199,228,132,84,65,44,185,42,196,229,189,175,71,68,114,39,
24,16,215,55,125,58,173,238,62,26,125,4,119,101,159,103,160,199,171,6,186,73,62,218,86,10,187,87,63,134,254,118,121,191,36,59,30,180,65,74,181,106,131,241,92,132,136,86,223,72,254,214,175,197,64,61,102,
197,84,235,70,155,65,86,33,210,59,194,230,169,155,120,76,222,35,245,245,12,131,68,48,219,51,49,163,25,222,206,96,199,120,12,85,145,195,4,7,231,150,134,80,215,44,204,82,76,10,121,176,110,1,62,110,112,173,
7,114,216,69,63,69,236,183,110,130,43,16,169,47,183,16,156,134,19,22,51,208,79,157,233,195,44,171,98,68,24,228,98,130,59,252,21,11,49,204,18,232,252,72,0,159,64,148,153,170,88,97,232,193,10,74,135,208,
13,98,245,32,54,253,4,145,59,54,199,80,221,140,40,204,53,94,50,250,13,136,68,78,221,119,252,67,114,55,202,248,38,34,97,209,180,80,106,165,100,146,59,200,191,79,228,112,112,153,193,98,124,140,224,61,84,
74,194,32,231,2,246,33,210,183,215,14,211,232,11,178,63,42,12,116,255,131,12,198,97,150,163,239,205,3,81,1,152,144,196,98,73,111,82,189,225,156,236,66,100,185,230,155,175,175,50,184,73,145,9,222,130,216,
14,251,14,224,191,138,252,30,223,106,184,136,36,194,220,164,88,70,186,133,94,111,220,209,132,135,168,82,91,158,135,57,106,48,43,111,13,74,91,48,73,173,56,168,216,17,23,26,62,215,124,169,247,47,145,231,
154,50,199,65,224,253,20,222,61,248,219,136,78,247,97,80,131,232,34,243,201,34,191,79,19,117,120,95,216,155,20,139,65,166,83,154,78,36,195,101,226,213,228,239,177,100,18,149,133,224,84,236,57,6,106,201,
155,190,85,183,84,88,7,252,62,193,129,198,52,34,91,123,227,48,232,236,95,25,218,157,63,44,42,13,213,208,151,71,155,65,22,26,122,58,70,11,43,164,168,255,104,142,239,76,162,178,39,21,155,161,24,43,156,106,
104,95,88,130,121,104,67,180,101,186,14,221,132,82,225,74,190,153,240,251,185,131,232,168,255,149,34,140,223,68,58,123,132,223,98,187,104,12,178,148,115,11,247,49,52,238,98,18,123,56,24,160,146,100,140,
72,29,36,21,105,100,18,88,28,14,18,146,104,250,13,207,107,65,236,192,53,156,77,71,191,38,29,36,195,85,175,116,189,150,237,8,111,92,40,68,16,89,175,83,36,167,245,75,207,140,105,196,241,166,115,140,65,162,
210,232,124,135,162,251,155,164,77,239,15,152,35,203,192,136,108,149,132,151,81,203,234,75,240,252,211,16,30,188,15,33,220,184,38,104,146,106,217,195,132,47,181,254,14,34,3,249,201,144,231,191,195,224,
216,35,82,98,134,102,16,16,181,7,55,72,67,59,147,22,237,202,213,77,135,89,42,12,38,215,159,133,107,82,47,209,39,245,230,180,66,136,113,132,107,116,62,250,65,62,16,185,90,139,17,17,86,211,168,108,144,206,
62,1,253,148,249,195,12,38,112,206,43,225,34,17,65,116,166,217,98,160,102,101,112,2,17,8,124,0,17,75,10,115,239,239,34,220,191,97,136,215,164,219,201,107,12,221,206,207,104,160,45,136,212,140,239,75,67,
245,58,169,107,174,30,129,213,236,174,28,222,144,123,201,239,98,204,69,152,215,231,89,177,103,34,124,246,31,52,80,47,151,73,6,169,71,191,94,194,111,51,228,194,12,244,107,225,247,141,146,129,14,34,251,
246,111,144,77,183,13,209,47,37,208,62,68,243,233,48,106,210,221,228,222,202,46,232,189,153,244,110,30,86,12,198,111,131,52,35,2,70,55,73,46,253,48,34,145,239,96,17,245,94,63,46,46,194,195,122,114,37,
254,8,133,19,247,252,152,174,72,49,147,168,108,80,209,255,28,244,203,125,213,13,124,76,178,83,91,165,163,224,117,121,141,189,132,243,245,95,203,240,26,194,125,13,145,206,18,102,123,130,15,97,230,141,202,
72,231,153,6,199,239,45,38,131,248,197,232,15,17,221,74,150,35,58,129,127,143,144,73,95,146,168,154,115,216,2,38,171,65,208,54,0,61,152,149,85,86,43,170,141,110,84,182,133,194,165,190,166,42,192,6,101,
46,86,24,156,247,45,132,107,61,243,185,88,190,167,175,26,50,202,44,195,251,230,194,3,114,49,117,67,16,251,29,134,231,76,55,144,206,58,181,250,161,25,68,69,23,194,61,250,231,114,50,223,141,8,30,237,50,
184,215,78,134,166,102,204,195,44,56,183,175,136,207,132,66,72,38,94,184,67,26,4,168,91,172,213,173,72,188,153,152,247,3,246,228,199,149,99,106,148,43,250,221,134,116,48,147,225,227,33,68,75,90,83,188,
23,179,140,142,149,6,239,248,4,33,138,164,194,18,83,6,41,68,36,250,179,114,229,186,70,190,148,160,32,210,243,57,254,183,10,253,214,154,221,4,39,190,217,152,165,105,180,134,240,96,5,149,250,198,12,108,
137,22,101,12,179,12,230,162,147,194,113,152,199,208,111,155,3,197,75,57,250,46,162,163,191,9,150,25,170,89,38,101,17,65,181,250,35,62,49,9,68,205,192,11,210,80,187,20,225,130,187,30,209,172,65,189,126,
174,29,132,76,140,210,163,4,39,156,93,96,56,217,251,164,106,101,82,255,253,178,198,24,166,26,188,192,129,16,246,199,65,10,119,49,73,200,235,234,190,223,94,101,53,31,71,176,11,251,56,67,19,61,51,248,50,
98,147,34,221,57,136,202,99,117,109,5,147,120,213,250,225,114,124,49,147,21,93,41,69,54,34,182,19,88,34,153,229,118,68,127,167,195,195,100,144,93,4,247,52,90,101,96,108,247,75,6,153,130,89,247,147,160,
32,217,108,244,179,10,26,67,26,232,7,2,136,184,198,64,26,121,82,50,143,151,106,180,78,150,244,154,2,12,114,76,58,118,62,103,240,60,49,131,227,76,106,245,183,157,77,12,146,203,230,216,137,240,181,79,38,
247,62,235,38,43,183,78,193,139,73,154,70,70,63,125,167,1,49,233,68,101,77,212,53,181,254,219,164,72,42,200,17,49,29,125,47,90,171,36,164,107,13,8,53,168,31,128,105,238,147,174,7,108,1,197,173,213,31,
85,6,241,19,163,31,19,13,87,3,29,239,148,137,68,202,52,105,51,141,202,6,165,152,232,186,173,211,202,10,55,14,179,20,147,32,59,200,68,13,105,146,146,249,162,34,190,139,78,67,250,56,173,121,220,114,3,38,
238,34,187,58,178,100,70,122,177,176,146,194,91,74,251,137,73,103,53,48,81,83,50,18,105,105,8,166,42,4,221,36,197,54,69,26,205,49,208,217,117,250,59,153,212,181,236,53,148,96,30,193,222,196,137,6,247,
239,97,48,213,166,152,11,224,81,178,171,69,207,57,6,49,137,21,52,17,236,193,186,192,112,21,204,168,9,38,46,206,160,148,140,90,244,227,58,7,148,149,214,36,14,115,148,194,177,40,7,179,184,198,110,101,12,
58,232,32,56,24,107,162,234,110,69,63,153,208,132,65,222,192,204,147,119,214,49,136,201,106,191,133,96,119,221,71,209,79,141,73,34,220,164,54,250,13,30,208,88,233,174,53,48,248,159,82,116,111,19,251,227,
80,192,92,212,99,182,125,245,110,195,133,226,52,133,155,229,57,136,60,45,93,188,100,96,131,204,51,188,46,231,50,131,44,53,100,144,66,248,35,68,79,38,93,252,86,174,224,149,152,109,113,86,232,5,85,35,226,
65,186,80,55,113,49,217,73,42,200,254,48,73,155,25,144,146,52,130,126,186,73,3,133,99,77,159,64,127,55,41,15,253,140,222,58,204,178,46,26,139,65,164,145,81,98,142,201,134,106,192,44,196,198,142,126,230,
158,132,240,26,153,110,3,247,51,229,5,153,116,229,254,99,68,251,76,213,197,105,33,186,120,124,3,253,140,224,189,10,211,199,9,223,191,55,31,19,235,170,107,77,114,44,54,133,27,129,171,168,66,108,241,253,
121,159,218,59,11,209,114,233,243,134,234,149,110,239,173,229,134,54,235,193,115,153,65,230,24,170,54,31,37,119,21,96,24,236,5,30,149,191,39,48,107,71,57,25,209,132,96,51,194,61,106,73,219,103,25,102,
123,145,220,203,96,177,210,100,67,149,40,104,101,52,73,254,60,40,137,41,67,80,186,42,204,251,17,89,223,141,82,221,171,145,206,137,58,195,119,241,3,244,243,183,150,24,62,215,161,115,153,65,230,51,122,248,
91,133,41,92,132,103,202,68,154,89,152,109,72,233,199,126,224,39,190,149,87,87,189,233,209,80,55,77,226,48,170,55,106,135,180,161,116,49,1,179,206,34,126,236,0,254,223,8,217,172,175,97,214,87,248,172,
179,65,22,143,210,125,31,68,116,216,80,241,72,9,239,239,33,18,62,187,67,46,22,7,41,236,219,175,52,212,211,95,205,99,19,149,98,30,62,99,72,196,38,158,177,198,98,13,116,44,49,200,83,136,238,227,126,60,202,
48,107,6,12,240,5,169,162,169,184,212,144,65,10,169,36,245,152,21,185,169,181,40,191,166,116,77,167,239,98,112,207,24,29,152,214,234,239,62,151,25,164,130,210,52,38,80,241,11,169,55,231,114,143,246,49,
116,43,233,145,192,189,12,109,190,150,49,240,139,101,160,55,24,168,107,126,251,43,141,232,56,146,30,225,121,248,58,34,235,215,4,179,48,203,210,222,119,46,51,200,108,67,53,96,56,104,69,164,229,127,192,
167,214,228,146,34,127,63,66,99,232,1,62,77,238,228,189,113,152,213,195,108,8,248,62,110,240,78,93,134,6,210,158,65,184,105,189,17,152,135,118,121,237,47,135,56,215,196,51,215,77,145,60,88,163,197,32,
115,75,224,28,56,130,40,232,90,41,127,234,224,110,73,200,167,139,56,142,103,17,49,142,124,43,230,116,131,149,49,73,112,53,167,201,14,174,149,228,78,9,249,30,162,174,255,88,17,231,225,49,68,147,140,251,
75,160,146,111,67,63,117,37,16,163,225,197,90,49,66,171,211,1,57,57,235,164,68,8,179,103,251,119,229,249,159,65,212,52,132,105,90,209,38,175,241,99,224,87,26,47,94,215,61,220,171,65,180,205,136,120,134,
78,66,159,37,25,225,181,60,42,233,171,114,193,184,5,243,186,241,204,34,245,28,34,245,253,153,97,190,95,147,182,182,111,22,83,2,90,139,22,45,42,53,131,92,139,216,181,40,236,67,120,146,8,18,136,92,166,22,
68,173,200,177,34,143,115,166,100,146,75,17,57,64,147,17,17,234,152,50,142,94,201,156,199,16,17,238,205,146,24,116,115,139,150,1,239,210,152,139,76,145,82,80,15,43,27,209,137,189,94,243,154,77,136,61,
65,10,97,28,162,93,235,101,146,161,167,200,121,168,80,230,161,79,218,51,205,210,131,180,73,50,71,123,145,222,197,251,228,251,208,121,166,23,139,233,108,248,223,1,0,105,129,248,219,92,123,139,7,0,0,0,0,
73,69,78,68,174,66,96,130,0,0};

const char* Interface::cloudburstlogosmall_png = (const char*) resource_Interface_cloudburstlogosmall_png;
const int Interface::cloudburstlogosmall_pngSize = 8950;


//[EndFile] You can add extra defines here...
//[/EndFile]
