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
#include "Interface.h"
#include "Logger.h"

//==============================================================================
class CloudBurstApplication  : public JUCEApplication
{
public:
	ScopedPointer<ErrorLogger> logger;
	//==============================================================================
    CloudBurstApplication()
	{
		File logfile(File::getSpecialLocation(File::SpecialLocationType::userDocumentsDirectory).getChildFile("CloudBurst").getChildFile("LOG.txt"));

		logger = new ErrorLogger(logfile, ("Log initialized"));
		ErrorLogger::setCurrentLogger(logger);
		ToLog(String(ProjectInfo::projectName) + " " + String(ProjectInfo::versionString));
		ToLog(SystemStats::getOperatingSystemName());
		ToLog(SystemStats::isOperatingSystem64Bit() ? "64bit" : "32bit");
		ToLog(String("UserLanguage ") + SystemStats::getUserLanguage());
		ToLog(String("DisplayLanguage ") + SystemStats::getDisplayLanguage());
	}
	~CloudBurstApplication()
	{
		ErrorLogger::setCurrentLogger(nullptr);
	}

    const String getApplicationName() override       { return ProjectInfo::projectName; }
    const String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override       { 
		return false; 
	}

    //==============================================================================
    void initialise (const String& /*commandLine*/) override
    {
        mainWindow = new MainWindow (getApplicationName());
    }

    void shutdown() override
    {
        mainWindow = nullptr; // (deletes our window)
    }

    //==============================================================================
    void systemRequestedQuit() override
    {
		quit();
    }

    void anotherInstanceStarted (const String& commandLine) override
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
		StringArray sa(StringArray::fromTokens(commandLine, " ", "\"'"));
		mainWindow->interf->parseCommands(sa);
	}

    //==============================================================================
    /*
        This class implements the desktop window that contains an instance of
        our Interface class.
    */
    class MainWindow    : public DocumentWindow
    {
    public:
		Interface *interf;

        MainWindow (String name)  : DocumentWindow (name,
                                                    Colours::lightgrey,
													DocumentWindow::TitleBarButtons::closeButton | DocumentWindow::TitleBarButtons::minimiseButton)
        {
			interf = new Interface();
            setUsingNativeTitleBar (true);
			setContentOwned(interf, true);

            centreWithSize (getWidth(), getHeight());
            setVisible (true);
        }

        void closeButtonPressed() override
        {
            // This is called when the user tries to close this window. Here, we'll just
            // ask the app to quit when this happens, but you can change this to do
            // whatever you need.
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

        /* Note: Be careful if you override any DocumentWindow methods - the base
           class uses a lot of them, so by overriding you might break its functionality.
           It's best to do all your work in your content component instead, but if
           you really have to override any DocumentWindow methods, make sure your
           subclass also calls the superclass's method.
        */

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    ScopedPointer<MainWindow> mainWindow;
	TooltipWindow tooltipWindow;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (CloudBurstApplication)
