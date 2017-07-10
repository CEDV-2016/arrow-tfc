#pragma once

#include <Ogre.h>
#include <OIS/OIS.h>
#include <CEGUI.h>
#include <RendererModules/Ogre/Renderer.h>
#include <iostream>
#include <string>

#include "Game.hpp"
#include "GameState.hpp"
#include "MetaManager.hpp"

class PlayState : public Ogre::Singleton<PlayState>, public GameState
{
public:
  PlayState ();

  void enter ();
  void exit ();
  void pause ();
  void resume ();

  void keyPressed(const OIS::KeyEvent &e);
  void keyReleased(const OIS::KeyEvent &e);

  void mouseMoved(const OIS::MouseEvent &e);
  void mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
  void mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);

  bool frameStarted(const Ogre::FrameEvent& evt);
  bool frameEnded(const Ogre::FrameEvent& evt);

  void setPlayerName(std::string name);
  Game* getGame();
  
  // Inherited from Ogre::Singleton.
  static PlayState& getSingleton ();
  static PlayState* getSingletonPtr ();

private:
  Ogre::Root* _root;
  Ogre::SceneManager* _sceneMgr;
  Ogre::Camera* _camera;
  Game *_game;

  MetaManager* _metaMgr;

  bool _exitGame;

  void goToEndGame(bool win);
};
