#pragma once

#include <Ogre.h>
#include <OIS/OIS.h>
#include <CEGUI.h>
#include <RendererModules/Ogre/Renderer.h>

class DialogManager : public Ogre::Singleton<DialogManager>
{
    public:
        /// Constructor
        DialogManager ();
        /// Destructor
        ~DialogManager () {};

        static DialogManager& getSingleton ();
        static DialogManager* getSingletonPtr ();

        void update (float delta);
        /// This method processes a text file, and stores the information obtained in vector _data
        void loadDialogue();
        /// Initializes animations that will be used in the DialogueState
        void setupAnimations();
        /// This method update dialogue's elements (name, image and text)
        void setDialogue(float delta);
        /// Updates the text dialogue for show the message keyed
        void updateText(float delta);
        /// Load visual resources of dialogues
        void initCEGUI();
        /// Initializes variables and necessary methods to load a new dialogue
        void chargeDialogue();
        /// Loads the next intervention of a dialogue
        void newIntervention(std::string dialogText);
        /// Speeds the apparition of a message
        void passMessage();
        /// Reset state variables
        void resetDialogue();
        /// Hides CEGUI windows
        void hide();

    private:
        /// CEGUI Windows which they are the visual part
        CEGUI::Window* _dialogGUI, *_fps, *_botBarLabel, *_botBar, *_botNameLabel;
        /// Instance that allows to do animations
        CEGUI::AnimationInstance* _inAnim, *_outAnim;
        bool _exitAnim, _next_dialogue, _finish_dialogue, _message, _speed;
        std::string _text;

        int _dialogue_cont, _phase, _moveOut;
        std::string _dialogText;

        float _timeSinceStart;
        /// Seconds to wait for the first message
        const float _firstStartDelay = 0.0f;
        /// Seconds to wait for the first message
        float _secondStartDelay = 1.75f;
        /// Maximum number of characters per line
        const int _limit_letter = 50;
        /// Message playback speed
        float VELOCITY = 0.08f;
        /// Vector that stores the information read from a file
        std::vector<std::string> _data;
        /// Character that delimits the dialogues
        const static char DELIM = ':';
};
