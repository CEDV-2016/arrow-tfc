#pragma once

/*
  One manager to rule them all,
   one manager to find them,
    one manager to bring them all,
     and in darkness bind them.
*/

#include <OIS/OIS.h>

#include "SoundFXManager.hpp"
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

#include "MyTimer.hpp"

class MetaManager : public Ogre::Singleton<MetaManager>
{
public:
  MetaManager(Ogre::SceneManager* sceneMgr);
  ~MetaManager();

  void update(Ogre::Real deltaT);

  void keyPressed(const OIS::KeyEvent &e);
  void keyReleased(const OIS::KeyEvent &e);
  void mouseMoved(const OIS::MouseEvent &e);
  void mousePressed(const OIS::MouseEvent &e);
  void mouseReleased(const OIS::MouseEvent &e);

  void start( std::string player_name );
  void pause();
  void resume();
  void finish();

  MyPhysicsManager* getPhysicManager();
  MapManager* getMapManager();
  MyOverlayManager* getOverlayManager();
  CameraManager* getCameraManager();
  ShootManager* getShootManager();
  MyCollisionManager* getCollitionManager();
  CharacterManager* getCharacterManager();
  DialogManager* getDialogManager();
  EnemyManager* getEnemyManager();
  ParticlesManager* getParticlesManager();
  SoundFXManager* getSoundManager();

  static MetaManager& getSingleton();
  static MetaManager* getSingletonPtr();

  void setPlayerPosition(double x, double y, double z);
  
private:
  MyPhysicsManager* _physicsMgr;
  MapManager* _mapMgr;
  MyOverlayManager* _overlayMgr;
  CameraManager* _cameraMgr;
  ShootManager* _shootMgr;
  MyCollisionManager* _collitionMgr;
  CharacterManager* _characterMgr;
  DialogManager* _dialogMgr;
  EnemyManager* _enemyMgr;
  ParticlesManager* _particlesMgr;
  SoundFXManager* _soundMgr;
  MyTimer* _timer;
};
