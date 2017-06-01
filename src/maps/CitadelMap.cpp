#include "CitadelMap.hpp"

#include <iostream>

CitadelMap::CitadelMap(Ogre::SceneManager * sceneMgr, OgreBulletDynamics::DynamicsWorld * world) :
_sceneMgr( sceneMgr ),
_world( world )
{
}

CitadelMap::~CitadelMap()
{
  destroy();
}

void CitadelMap::create()
{
}

void CitadelMap::destroy()
{
}
