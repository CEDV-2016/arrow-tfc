#pragma once

#include <Ogre.h>
#include <OgreOverlaySystem.h>
#include <OgreOverlayElement.h>
#include <OgreOverlayManager.h>
#include <OIS/OIS.h>
#include <CEGUI.h>
#include <RendererModules/Ogre/Renderer.h>

#include "MapManager.hpp"
#include "MyPhysicsManager.hpp"
#include "MyOverlayManager.hpp"
#include "CameraManager.hpp"
#include "ShootManager.hpp"
#include "MyCollisionManager.hpp"
#include "CharacterManager.hpp"
#include "DialogManager.hpp"
#include "EnemyManager.hpp"
#include "ParticlesManager.hpp"

#include "GameState.hpp"

class IntroState : public Ogre::Singleton<IntroState>, public GameState
{
 public:
  IntroState();

  void enter ();
  void exit ();
  void pause ();
  void resume ();

  void keyPressed (const OIS::KeyEvent &e);
  void keyReleased (const OIS::KeyEvent &e);

  void mouseMoved (const OIS::MouseEvent &e);
  void mousePressed (const OIS::MouseEvent &e, OIS::MouseButtonID id);
  void mouseReleased (const OIS::MouseEvent &e, OIS::MouseButtonID id);

  bool frameStarted (const Ogre::FrameEvent& evt);
  bool frameEnded (const Ogre::FrameEvent& evt);

  // Heredados de Ogre::Singleton.
  static IntroState& getSingleton ();
  static IntroState* getSingletonPtr ();

  void initializeManagers();

  void createGUI();
  void loadBackgroundImage();

 protected:
  Ogre::Root* _root;
  Ogre::SceneManager* _sceneMgr;
  Ogre::Viewport* _viewport;
  Ogre::Camera* _camera;
  Ogre::RaySceneQuery *_raySceneQuery;
  Ogre::SceneNode *_selectedNode;
  CEGUI::OgreRenderer* renderer;
  OIS::InputManager* _inputManager;
  OIS::Keyboard* _keyboard;
  OIS::Mouse* _mouse;
  CEGUI::Window* _intro;

  Ogre::SceneNode *_backgroundNode;
  Ogre::Rectangle2D *_rect;

  MyPhysicsManager* _physicsMgr;
  MapManager* _mapMgr;
  MyOverlayManager* _overlayMgr;
  CameraManager* _cameraMgr;
  ShootManager* _shootMgr;
  MyCollisionManager* _collisionMgr;
  CharacterManager* _characterMgr;
  DialogManager* _dialogueMgr;
  EnemyManager* _enemyMgr;
  ParticlesManager* _particlesMgr;

  bool _exitGame;
};
