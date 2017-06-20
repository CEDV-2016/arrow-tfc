#include "DialogState.hpp"
#include "PlayState.hpp"
#include "SoundFXManager.hpp"

template<> DialogState* Ogre::Singleton<DialogState>::msSingleton = nullptr;

DialogState::DialogState () : _root(nullptr), _sceneMgr(nullptr), _camera(nullptr),
_node(nullptr), _entity(nullptr), _exit(false), _phase(1), _dialogue(1), _clic(0),
_dialogueMgr(nullptr)
{
}

DialogState::~DialogState () {
}

DialogState* DialogState::getSingletonPtr () {
    return msSingleton;
}

DialogState& DialogState::getSingleton () {
    assert (msSingleton);
    return *msSingleton;
}

void DialogState::enter () {
    _root = Ogre::Root::getSingletonPtr();
    _sceneMgr = _root->getSceneManager("SceneManager");
    _camera = _sceneMgr->getCamera("MainCamera");
    _dialogueMgr = DialogManager::getSingletonPtr();
    _dialogueMgr->newIntervention(_phase, _dialogue);
}

void DialogState::exit () {
}

void DialogState::pause () {
}

void DialogState::resume () {
}

bool DialogState::frameStarted (const Ogre::FrameEvent &evt) {
    Ogre::Real delta = evt.timeSinceLastFrame;
    CEGUI::System::getSingleton().injectTimePulse(evt.timeSinceLastFrame);
    _dialogueMgr->update(delta);

    return !_exit;
}

bool DialogState::frameEnded (const Ogre::FrameEvent &evt) {
    return !_exit;
}

void DialogState::keyPressed (const OIS::KeyEvent &e) {
}

void DialogState::keyReleased (const OIS::KeyEvent &e) {
    switch (e.key) {
        case OIS::KC_ESCAPE:
          _exit = true;
          break;
        default:
          break;
    }
}

void DialogState::mouseMoved (const OIS::MouseEvent &e) {
    CEGUI::System::getSingleton().getDefaultGUIContext().injectMousePosition(e.state.X.abs, e.state.Y.abs);
}

void DialogState::mousePressed (const OIS::MouseEvent &e, OIS::MouseButtonID id) {
  return;
}

void DialogState::mouseReleased (const OIS::MouseEvent &e, OIS::MouseButtonID id) {
    switch (id) {
      case OIS::MB_Left:
        _clic++;
        if((_clic%2)==0)
            _dialogueMgr->chargeDialogue();
        else
            _dialogueMgr->passMessage();
        break;
      default:
        break;
    }
};

bool DialogState::povMoved(const OIS::JoyStickEvent &e, int pov) {
  return true;
}

bool DialogState::axisMoved(const OIS::JoyStickEvent &e, int axis) {
  return true;
}

bool DialogState::sliderMoved(const OIS::JoyStickEvent &e, int sliderID) {
  return true;
}

bool DialogState::buttonPressed(const OIS::JoyStickEvent &e, int button) {
  switch (button) {
      case JOYSTICK_BUTTON_1:
        _clic++;
        if((_clic%2)==0)
            _dialogueMgr->chargeDialogue();
        else
            _dialogueMgr->passMessage();
        break;
      default:
        break;
  }
  return true;
}

bool DialogState::buttonReleased(const OIS::JoyStickEvent &e, int button) {
  return true;
}
