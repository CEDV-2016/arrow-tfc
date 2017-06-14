#include "MainState.hpp"
#include "NewGameState.hpp"
#include "CreditsState.hpp"
#include "RankingState.hpp"
#include "InformationState.hpp"
#include "SoundFXManager.hpp"
#include "MapManager.hpp"

template<> MainState* Ogre::Singleton<MainState>::msSingleton = 0;

MainState* MainState::getSingletonPtr () {
  return msSingleton;
}

MainState& MainState::getSingleton () {
  assert (msSingleton);
  return *msSingleton;
}

void MainState::enter () {
  _root = Ogre::Root::getSingletonPtr();

  _sceneManager = _root->getSceneManager("SceneManager");
  _camera = _sceneManager->getCamera("MainCamera");
  _viewport = _root->getAutoCreatedWindow()->getViewport(0);

  SoundFXManager::getSingletonPtr()->load("menu_item.wav")->play();

  createGUI();

  _exit = false;
}

void MainState::exit() {
  _sceneManager->clearScene();
  _root->getAutoCreatedWindow()->removeAllViewports();
}

void MainState::pause () {
  _main->hide();
}

void MainState::resume () {
  _main->show();
}

bool MainState::frameStarted (const Ogre::FrameEvent &evt)
{
  MapManager::getSingletonPtr()->update( evt.timeSinceLastFrame );
  CEGUI::System::getSingleton().injectTimePulse( evt.timeSinceLastFrame );

  return true;
}

bool MainState::frameEnded (const Ogre::FrameEvent &evt)
{
  if (_exit) return false;

  return true;
}

void MainState::keyPressed (const OIS::KeyEvent &e) {}

void MainState::keyReleased (const OIS::KeyEvent &e)
{
  if (e.key == OIS::KC_ESCAPE)
  {
    _exit = true;
  }
}

void MainState::mouseMoved (const OIS::MouseEvent &e) {}

void MainState::mousePressed (const OIS::MouseEvent &e, OIS::MouseButtonID id) {}

void MainState::mouseReleased (const OIS::MouseEvent &e, OIS::MouseButtonID id) {}

void MainState::createGUI()
{
  if(_main == NULL)
  {
    //Config Window
    _main = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("main.layout");
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(_main);

    //Config Buttons
    CEGUI::Window* aux_button;

    _btNew = _main->getChild("NewButton");
    _btNew->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainState::newGame, this));

    _btCredits= _main->getChild("CreditsButton");
    _btCredits->subscribeEvent(CEGUI::PushButton::EventClicked,  CEGUI::Event::Subscriber(&MainState::navigateToCredits, this));

    _btRanking = _main->getChild("RankingButton");
    _btRanking->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainState::navigateToRanking, this));

    _btInfo = _main->getChild("InformationButton");
    _btInfo->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainState::navigateToInformation, this));

    _btExit = _main->getChild("ExitButton");
    _btExit->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainState::quit, this));
  }
  else
  {
    _main->show();
  }

  //setupAnimations();
}

void MainState::setupAnimations() {
  CEGUI::AnimationManager& animMgr = CEGUI::AnimationManager::getSingleton();
  animMgr.loadAnimationsFromXML("Menu.anims");

  CEGUI::Animation* startRotateAnim = animMgr.getAnimation("TravelRotateIn");
  _animRotate = animMgr.instantiateAnimation(startRotateAnim);
  _animRotate->setTargetWindow(_btNew);

  CEGUI::Animation* startMoveAnim = animMgr.getAnimation("BotBarDialogoMoveInAnimation");
  CEGUI::AnimationInstance* startButtAnimInstance = animMgr.instantiateAnimation(startMoveAnim);
  startButtAnimInstance->setTargetWindow(_btNew);
  startButtAnimInstance->start();
}


bool MainState::newGame(const CEGUI::EventArgs &e)
{
  pushState(NewGameState::getSingletonPtr());
  return true;
}

bool MainState::navigateToCredits(const CEGUI::EventArgs &e)
{
  //pushState(CreditsState::getSingletonPtr());
  CEGUI::EventArgs args;
  _btNew->fireEvent("StartRotate", args);
  return true;
}

bool MainState::navigateToRanking(const CEGUI::EventArgs &e)
{
  pushState(RankingState::getSingletonPtr());
  return true;
}

bool MainState::navigateToInformation(const CEGUI::EventArgs &e)
{
  pushState(InformationState::getSingletonPtr());
  return true;
}

bool MainState::quit(const CEGUI::EventArgs &e)
{
  _exit = true;
  return true;
}
