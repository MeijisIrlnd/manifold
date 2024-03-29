/*
  ==============================================================================

    This file contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include <JuceHeader.h>
#include "UI/MainWindowComponent.h"
#include "Macros.h"
#include "Audio/ManifoldEngine.h"
#include "Testing/ChannelTester.h"
#include "Testing/CacheTester.h"

using namespace Manifold;
using namespace Manifold::UI;
using namespace Manifold::Audio;
//==============================================================================
class manifoldApplication  : public juce::JUCEApplication
{
public:
    //==============================================================================
    manifoldApplication() {}

    const juce::String getApplicationName() override       { return ProjectInfo::projectName; }
    const juce::String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override             { return true; }

    //==============================================================================
    void initialise (MANIFOLD_UNUSED const juce::String& commandLine) override
    {
        // This method is where you should put your application's initialisation code..

        GET_POSITION_TRACKER()->startup();
        auto instance = ManifoldEngine::getInstance();
        mainWindow.reset (new MainWindow (getApplicationName(), instance->getUIListener()));
        //Manifold::Testing::ChannelTester tester;
#ifdef ENABLE_TESTS
            Manifold::Testing::testCache();
#endif
    }

    void shutdown() override
    {
        // Add your application's shutdown code here..
        mainWindow = nullptr; // (deletes our window)
        WindowManager::shutdown();
        ManifoldEngine::shutdown();
        PositionTracker::shutdown();
        AudioCache::shutdown();
    }

    //==============================================================================
    void systemRequestedQuit() override
    {
        // This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        quit();
    }

    void anotherInstanceStarted (MANIFOLD_UNUSED const juce::String& commandLine) override
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
    }

    //==============================================================================
    /*
        This class implements the desktop window that contains an instance of
        our MainComponent class.
    */
    class MainWindow    : public juce::DocumentWindow
    {
    public:
        MainWindow (juce::String name, UIListener* uiListener)
            : DocumentWindow (name,
                              juce::Desktop::getInstance().getDefaultLookAndFeel()
                                                          .findColour (juce::ResizableWindow::backgroundColourId),
                              DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar (true);
            setContentOwned (new MainWindowComponent(uiListener), true);

           #if JUCE_IOS || JUCE_ANDROID
            setFullScreen (true);
           #else
            setFullScreen(true);
           #endif

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
    std::unique_ptr<MainWindow> mainWindow;
    // Need an instance of the audio engine as well...

};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (manifoldApplication)
