#pragma once

#include <Ogre.h>
#include <OIS/OIS.h>
#include <CEGUI.h>
#include <RendererModules/Ogre/Renderer.h>
#include "GameState.hpp"
#include "DialogManager.hpp"
#include "TrackManager.hpp"


class DialogState : public Ogre::Singleton<DialogState>, public GameState {
public:
    /// Constructor
    DialogState();
    /// Destructor
    ~DialogState();

    static DialogState& getSingleton ();
    static DialogState* getSingletonPtr ();

    virtual void enter ();
    virtual void exit ();
    virtual void pause ();
    virtual void resume ();

    virtual void keyPressed (const OIS::KeyEvent &e);
    virtual void keyReleased (const OIS::KeyEvent &e);
    virtual void mouseMoved (const OIS::MouseEvent &e);
    virtual void mousePressed (const OIS::MouseEvent &e, OIS::MouseButtonID id);
    virtual void mouseReleased (const OIS::MouseEvent &e, OIS::MouseButtonID id);

    virtual bool povMoved( const OIS::JoyStickEvent &e, int pov );
    virtual bool axisMoved( const OIS::JoyStickEvent &e, int axis );
    virtual bool sliderMoved( const OIS::JoyStickEvent &e, int sliderID );
    virtual bool buttonPressed( const OIS::JoyStickEvent &e, int button );
    virtual bool buttonReleased ( const OIS::JoyStickEvent &e, int button);

    virtual bool frameStarted (const Ogre::FrameEvent &e);
    virtual bool frameEnded (const Ogre::FrameEvent &e);

    /// This method sets the value of phase and dialogue
    void setDialogue(int phase, int dialogue) { _phase = phase; _dialogue = dialogue; };



private:
    /* data */
    Ogre::Root *_root;
    Ogre::SceneManager *_sceneMgr;
    Ogre::Camera *_camera;
    Ogre::Viewport *_viewport;
    Ogre::SceneNode *_node;
    Ogre::Entity *_entity;
    bool _exit;
    /// Variables that indicate number of phase and dialogue, in order to load the right message
    int _phase, _dialogue;
    /// This variable indicates the action to be performed according to the number of clics
    int _clic;

    // Managers
    /// This is necessary to get the next dialogue
    DialogManager *_dialogueMgr;

    TrackManager *_trackMgr;
    /// They are gamepad button
    enum Constants
        {
            JOYSTICK_BUTTON_1 = 0,
            JOYSTICK_BUTTON_2 = 2
        };
};
