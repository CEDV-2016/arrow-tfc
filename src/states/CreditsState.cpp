#include "CreditsState.hpp"
#include "SoundFXManager.hpp"

template<> CreditsState* Ogre::Singleton<CreditsState>::msSingleton = 0;

CreditsState::CreditsState() {
  _creditsGUI = NULL;
}

void
CreditsState::enter ()
{
  _root = Ogre::Root::getSingletonPtr();

  _sceneMgr = _root->getSceneManager("SceneManager");
  _camera = _sceneMgr->getCamera("MainCamera");
  createGUI();

  SoundFXManager::getSingletonPtr()->load("menu_item.wav")->play();

  _exitGame = false;
}

void
CreditsState::exit ()
{
  _creditsGUI->hide();
}

void
CreditsState::pause ()
{
}

void
CreditsState::resume ()
{
}

bool
CreditsState::frameStarted
(const Ogre::FrameEvent& evt)
{
  CEGUI::System::getSingleton().injectTimePulse( evt.timeSinceLastFrame );
  return true;
}

bool
CreditsState::frameEnded
(const Ogre::FrameEvent& evt)
{
  if (_exitGame)
  return false;

  return true;
}

void
CreditsState::keyPressed
(const OIS::KeyEvent &e)
{
}

void
CreditsState::keyReleased
(const OIS::KeyEvent &e)
{
  if (e.key == OIS::KC_ESCAPE)
  {
    popState();
  }
}

void
CreditsState::mouseMoved
(const OIS::MouseEvent &e)
{
}

void
CreditsState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

void
CreditsState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

CreditsState*
CreditsState::getSingletonPtr ()
{
  return msSingleton;
}

CreditsState&
CreditsState::getSingleton ()
{
  assert(msSingleton);
  return *msSingleton;
}

void CreditsState::createGUI()
{
  if(_creditsGUI == NULL)
  {
    //Config Window
    _creditsGUI = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("credits.layout");
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(_creditsGUI);

    //Config buttons
    CEGUI::Window* backButton = _creditsGUI->getChild("BackButton");
    backButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CreditsState::back, this));
    _title = _creditsGUI->getChild("Create");
    _component1 = _creditsGUI->getChild("Pedro");
    _component2 = _creditsGUI->getChild("JJ");
  }
  else
  {
    _creditsGUI->show();
  }
  setupAnimations();
}

void CreditsState::setupAnimations() {
  CEGUI::AnimationManager& animMgr = CEGUI::AnimationManager::getSingleton();

  CEGUI::Animation* titleAnim = animMgr.getAnimation("RingsContainerSizeIn");
  CEGUI::AnimationInstance* titleAnimInstance = animMgr.instantiateAnimation(titleAnim);
  titleAnimInstance->setTargetWindow(_title);
  titleAnimInstance->start();

  CEGUI::Animation* component1Anim = animMgr.getAnimation("RingsContainerSizeIn");
  CEGUI::AnimationInstance* comp1AnimInstance = animMgr.instantiateAnimation(component1Anim);
  comp1AnimInstance->setTargetWindow(_component1);
  comp1AnimInstance->start();

  CEGUI::Animation* component2Anim = animMgr.getAnimation("RingsContainerSizeIn");
  CEGUI::AnimationInstance* comp2AnimInstance = animMgr.instantiateAnimation(component2Anim);
  comp2AnimInstance->setTargetWindow(_component2);
  comp2AnimInstance->start();
}

bool CreditsState::back(const CEGUI::EventArgs &e)
{
  popState();
  return true;
}
