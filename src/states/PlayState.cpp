#include "PlayState.hpp"
#include "PauseState.hpp"
#include "EndState.hpp"
#include "SoundFXManager.hpp"

#include <OgreBulletDynamicsRigidBody.h>
#include <Shapes/OgreBulletCollisionsStaticPlaneShape.h>
#include <Shapes/OgreBulletCollisionsBoxShape.h>
#include "Shapes/OgreBulletCollisionsTrimeshShape.h"
#include "Shapes/OgreBulletCollisionsSphereShape.h"
#include "Utils/OgreBulletCollisionsMeshToShapeConverter.h"

#include <iostream>

template<> PlayState* Ogre::Singleton<PlayState>::msSingleton = 0;

PlayState::PlayState()
{
  _game = new Game();
  _timer = new MyTimer();
}

void
PlayState::enter ()
{
  _timer->start();

  _root = Ogre::Root::getSingletonPtr();
  CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().hide();

  _sceneMgr = _root->getSceneManager("SceneManager");
  _camera = _sceneMgr->getCamera("MainCamera");

  _mapManager = MapManager::getSingletonPtr();
  _overlayManager = MyOverlayManager::getSingletonPtr();
  _physicsManager = MyPhysicsManager::getSingletonPtr();
  _camManager = CameraManager::getSingletonPtr();
  _shootManager = ShootManager::getSingletonPtr();
  _collisionManager = MyCollisionManager::getSingletonPtr();
  _characterManager = CharacterManager::getSingletonPtr();

  _sceneMgr->clearScene(); //deleting background image
  Ogre::Camera* cam = _sceneMgr->getCamera("MainCamera");
  cam->setPosition( Ogre::Vector3(0, 0, 0) );
  //_sceneMgr->getCamera("MainCamera")->lookAt( Ogre::Vector3(-5, 5, -9) );
  cam->setNearClipDistance(0.001);
  cam->setFarClipDistance(10000);

  createScene();
  createHUD();

  _camManager->initCamera();
  _shootManager->initWorld();

  _exitGame = false;
}

void
PlayState::exit ()
{
  _mapManager->destroyAllMaps();
  _overlayManager->hideHUD();
  _sceneMgr->clearScene();
  _root->getAutoCreatedWindow()->removeAllViewports();
}

void
PlayState::pause()
{
  _timer->pause();
  CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().show();
}

void
PlayState::resume()
{
  _timer->resume();
  CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().hide();
}

bool
PlayState::frameStarted
(const Ogre::FrameEvent& evt)
{
  Ogre::Real deltaT = evt.timeSinceLastFrame;
  updateManagers(deltaT);

  return true;
}

void PlayState::updateManagers(Ogre::Real deltaT)
{
  _mapManager->update( deltaT );
  _camManager->moveCamera( deltaT );
  _physicsManager->update( deltaT );
  _collisionManager->update( deltaT);
  _characterManager->update( deltaT );

  _overlayManager->setTime( _timer->getGameplayTime() );
}


bool
PlayState::frameEnded
(const Ogre::FrameEvent& evt)
{
  if (_exitGame)
  {
    return false;
  }
  else
  {
    return true;
  }
}

void
PlayState::keyPressed
(const OIS::KeyEvent &e)
{
  _camManager->keyPressed(e);
}

void
PlayState::keyReleased
(const OIS::KeyEvent &e)
{
  if (e.key == OIS::KC_ESCAPE) pushState(PauseState::getSingletonPtr());

  _camManager->keyReleased(e);
}

void
PlayState::mouseMoved
(const OIS::MouseEvent &e)
{
  _camManager->mouseMoved(e);
}

void
PlayState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
  //if (e.key == OIS::MB_Left) {
  _shootManager->shootBall();
  //}
}

void
PlayState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

PlayState*
PlayState::getSingletonPtr ()
{
  return msSingleton;
}

PlayState&
PlayState::getSingleton ()
{
  assert(msSingleton);
  return *msSingleton;
}

void PlayState::createScene()
{
  _mapManager->changeMap( enumerations::Maps::ROOM, false );

  CharacterManager::getSingletonPtr()->loadCharacter();
}

void PlayState::createHUD()
{
  _overlayManager->createHUD();
  _overlayManager->setPlayerName( _game->getPlayerName() );
  _overlayManager->setDartboardsLeft( _game->getDartboartdsLeft() );
  _overlayManager->setBallsLeft( _game->getBallsLeft() );
}

void PlayState::setPlayerName(std::string name)
{
  _game->setPlayerName( name );
}

void PlayState::updateDartboards()
{
  _game->hitDartboard();
  _overlayManager->setDartboardsLeft(_game->getDartboartdsLeft());
  if ( _game->getDartboartdsLeft() == 0)
  {
    goToEndGame(true);
  }
}

void PlayState::updateBalls()
{
  if ( _game->getBallsLeft() == 0)
  {
    goToEndGame(false);
  }else
  {
    _game->shootBall();
    _overlayManager->setBallsLeft( _game->getBallsLeft());
  }
}

void PlayState::goToEndGame(bool win)
{

  if (win)
  {
    SoundFXManager::getSingletonPtr()->load("arrow_yes.wav")->play();
  }
  else
  {
    SoundFXManager::getSingletonPtr()->load("arrow_ouch.wav")->play();
  }

  EndState* endState = EndState::getSingletonPtr();
  int points = 5 - _game->getDartboartdsLeft();
  endState-> setData(win, _game->getPlayerName(), points);
  pushState(endState);
}
