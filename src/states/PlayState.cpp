#include "PlayState.hpp"

#include "PauseState.hpp"
#include "EndState.hpp"
#include "Enemy.hpp"

#include <iostream>

template<> PlayState* Ogre::Singleton<PlayState>::msSingleton = 0;

PlayState::PlayState()
{
  _game = new Game();
}

void
PlayState::enter ()
{
  _root = Ogre::Root::getSingletonPtr();
  CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().hide();

  _sceneMgr = _root->getSceneManager("SceneManager");
  _camera = _sceneMgr->getCamera("MainCamera");

  _sceneMgr->clearScene(); //deleting background image
  Ogre::Camera* cam = _sceneMgr->getCamera("MainCamera");
  cam->setPosition( Ogre::Vector3(0, 0, 0) );
  cam->setNearClipDistance(0.001);
  cam->setFarClipDistance(10000);

  _metaMgr = MetaManager::getSingletonPtr();
  _metaMgr->start();

  _exitGame = false;
}

void
PlayState::exit ()
{
  _metaMgr->finish();
  _sceneMgr->clearScene();
  _root->getAutoCreatedWindow()->removeAllViewports();
}

void
PlayState::pause()
{
  _metaMgr->pause();
  CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().show();
}

void
PlayState::resume()
{
  _metaMgr->resume();
  CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().hide();
}

bool
PlayState::frameStarted
(const Ogre::FrameEvent& evt)
{
  _metaMgr->update( evt.timeSinceLastFrame );

  return true;
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
  _metaMgr->keyPressed(e);
}

void
PlayState::keyReleased
(const OIS::KeyEvent &e)
{
  if (e.key == OIS::KC_ESCAPE)
  {
    pushState(PauseState::getSingletonPtr());
  }

  _metaMgr->keyReleased(e);
}

void
PlayState::mouseMoved
(const OIS::MouseEvent &e)
{
  _metaMgr->mouseMoved(e);
}

void
PlayState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
  _metaMgr->mousePressed(e);
}

void
PlayState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
  _metaMgr->mouseReleased(e);
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


void PlayState::setPlayerName(std::string name)
{
  _game->setPlayerName( name );
  _metaMgr->setPlayerName( name );
}

void PlayState::goToEndGame(bool win)
{
  EndState* endState = EndState::getSingletonPtr();
  int points = -1;
  endState->setData(win, _game->getPlayerName(), points);
  pushState(endState);
}
