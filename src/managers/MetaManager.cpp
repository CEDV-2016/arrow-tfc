#include "MetaManager.hpp"

template<> MetaManager* Ogre::Singleton<MetaManager>::msSingleton = 0;

MetaManager::MetaManager(Ogre::SceneManager * sceneMgr)
{
  _physicsMgr = new MyPhysicsManager( sceneMgr );
  _mapMgr = new MapManager( sceneMgr, _physicsMgr->getPhysicWorld() );
  _overlayMgr = new MyOverlayManager();
  _cameraMgr = new CameraManager( sceneMgr );
  // _shootMgr = new ShootManager( sceneMgr );
  _collitionMgr = new MyCollisionManager( sceneMgr );
  _characterMgr = new CharacterManager( sceneMgr );
  _dialogMgr = new DialogManager();
  _enemyMgr = new EnemyManager();
  _timer = new MyTimer();
  _soundMgr = SoundFXManager::getSingletonPtr();
}

void MetaManager::update(Ogre::Real deltaT)
{
  _physicsMgr->update( deltaT );
  _mapMgr->update( deltaT );
  _cameraMgr->moveCamera( deltaT );
  _collitionMgr->update( deltaT);
  _characterMgr->update( deltaT );
  _overlayMgr->setTime( _timer->getGameplayTime() );
}

void MetaManager::start()
{
  _mapMgr->changeMap( enumerations::Maps::CITADEL, false );
  _characterMgr->loadCharacter();

  _overlayMgr->createHUD();
  _overlayMgr->setTime( _timer->getGameplayTime() );

  _cameraMgr->initCamera();
  _shootMgr->initWorld();

  _timer->start();
}

void MetaManager::pause()
{
  _timer->pause();
}

void MetaManager::resume()
{
  _timer->resume();
}

void MetaManager::finish()
{
  _timer->stop();
  _mapMgr->destroyAllMaps();
  _overlayMgr->hideHUD();
}

void MetaManager::keyPressed(const OIS::KeyEvent &e)
{
  _cameraMgr->keyPressed(e);
}

void MetaManager::keyReleased(const OIS::KeyEvent &e)
{
  _cameraMgr->keyReleased(e);
}

void MetaManager::mouseMoved(const OIS::MouseEvent &e)
{
  _cameraMgr->mouseMoved(e);
}

void MetaManager::mousePressed(const OIS::MouseEvent &e)
{
}

void MetaManager::mouseReleased(const OIS::MouseEvent &e)
{
}

MyPhysicsManager* MetaManager::getPhysicManager() { return _physicsMgr; }

MapManager* MetaManager::getMapManager() { return _mapMgr; }

MyOverlayManager* MetaManager::getOverlayManager() { return _overlayMgr; }

CameraManager* MetaManager::getCameraManager() { return _cameraMgr; }

ShootManager* MetaManager::getShootManager() { return _shootMgr; }

MyCollisionManager* MetaManager::getCollitionManager() { return _collitionMgr; }

CharacterManager* MetaManager::getCharacterManager() { return _characterMgr; }

DialogManager* MetaManager::getDialogManager() { return _dialogMgr; }

EnemyManager* MetaManager::getEnemyManager() { return _enemyMgr; }

SoundFXManager* MetaManager::getSoundManager() { return _soundMgr; }

MetaManager* MetaManager::getSingletonPtr () { return msSingleton; }

MetaManager& MetaManager::getSingleton () { assert(msSingleton); return *msSingleton; }

/*
MetaManager::~MetaManager(Ogre::SceneManager * sceneMgr)
{
  delete _physicsMgr;
  delete _mapMgr;
  delete _overlayMgr;
  delete _cameraMgr;
  delete _shootMgr;
  delete _collisionMgr;
  delete _characterMgr;
  delete _dialogMgr;
  delete _enemyMgr;
  delete _timer;
  delete _soundMgr;
}
*/
