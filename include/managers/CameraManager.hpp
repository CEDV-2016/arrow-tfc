#pragma once

#include <Ogre.h>
#include <OIS/OIS.h>
#include <CEGUI.h>

class CameraManager : public Ogre::Singleton<CameraManager>
{
public:
  CameraManager( Ogre::SceneManager * sceneMgr );

  static CameraManager& getSingleton ();
  static CameraManager* getSingletonPtr ();

  void keyPressed (const OIS::KeyEvent &e);
  void keyReleased (const OIS::KeyEvent &e);

  void mouseMoved (const OIS::MouseEvent &e);

  void initCamera();
  void moveCamera(Ogre::Real deltaT);

  Ogre::Vector3 getPosition();
  Ogre::SceneNode * getSceneNode();

private:
  Ogre::SceneManager* _sceneMgr;
  Ogre::SceneNode *cameraNode;
  Ogre::SceneNode *cameraYawNode;
  Ogre::SceneNode *cameraPitchNode;
  Ogre::SceneNode *cameraRollNode;
  Ogre::Vector3 translateVector;
  Ogre::Radian rotateScale;
  float moveScale;
  Ogre::Radian rotX;
  Ogre::Radian rotY;

  Ogre::Real _last_deltaT;

  bool _w_pressed, _a_pressed, _s_pressed, _d_pressed;
};
