#include <Ogre.h>

#include "GameStatesManager.hpp"
#include "GameState.hpp"
#include "MapManager.hpp"

template<> GameStatesManager* Ogre::Singleton<GameStatesManager>::msSingleton = 0;

GameStatesManager::GameStatesManager ()
{
  _root = 0;
}

GameStatesManager::~GameStatesManager ()
{
  while (!_states.empty())
  {
    _states.top()->exit();
    _states.pop();
  }

  if (_root)
  {
    delete _root;
  }

  // OGRE_DELETE _trackManager;
  // OGRE_DELETE _pSoundFXManager;
}

void
GameStatesManager::start
(GameState* state)
{
  // Creación del objeto Ogre::Root.
  _root = new Ogre::Root();
  _trackManager = OGRE_NEW TrackManager;
  _pSoundFXManager = OGRE_NEW SoundFXManager;

  loadResources();
  initSDL();


  if (!configure())
  return;

  _inputMgr = new InputManager;
  _inputMgr->initialise(_renderWindow);

  _mainTrack = _trackManager->load("Winding-Down.ogg");
  _mainTrack->play();

  // Registro como key y mouse listener...
  _inputMgr->addKeyListener(this, "GameStatesManager");
  _inputMgr->addMouseListener(this, "GameStatesManager");

  // El GameStatesManager es un FrameListener.
  _root->addFrameListener(this);

  //CEGUI
  CEGUI::OgreRenderer::bootstrapSystem();
  CEGUI::Scheme::setDefaultResourceGroup("Schemes");
  CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
  CEGUI::Font::setDefaultResourceGroup("Fonts");
  CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
  CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");

  CEGUI::SchemeManager::getSingleton().createFromFile("VanillaSkin.scheme");
  CEGUI::SchemeManager::getSingleton().createFromFile("Generic.scheme");
  CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("Vanilla-Images/MouseArrow");

  // Let's make the OS and the CEGUI cursor be in the same place
  CEGUI::Vector2f mousePos = CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().getPosition();
  CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(-mousePos.d_x,-mousePos.d_y);

  CEGUI::FontManager::getSingleton().createAll("*.font", "Fonts");

  //Sheet
  CEGUI::Window* sheet = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow","Sheet");
  CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);

  // Transición al estado inicial.
  changeState(state);

  // Bucle de rendering.
  _root->startRendering();
}

void
GameStatesManager::changeState
(GameState* state)
{
  // Limpieza del estado actual.
  if (!_states.empty()) {
    // exit() sobre el último estado.
    _states.top()->exit();
    // Elimina el último estado.
    _states.pop();
  }

  // Transición al nuevo estado.
  _states.push(state);
  // enter() sobre el nuevo estado.
  _states.top()->enter();
}

void
GameStatesManager::pushState
(GameState* state)
{
  // Pausa del estado actual.
  if (!_states.empty())
  _states.top()->pause();

  // Transición al nuevo estado.
  _states.push(state);
  // enter() sobre el nuevo estado.
  _states.top()->enter();
}

void
GameStatesManager::popState ()
{
  // Limpieza del estado actual.
  if (!_states.empty()) {
    _states.top()->exit();
    _states.pop();
  }

  // Vuelta al estado anterior.
  if (!_states.empty())
  _states.top()->resume();
}

void
GameStatesManager::restartState
(GameState* state)
{
  // Limpieza de la pila
  while (!_states.empty()) {
    _states.top()->exit();
    _states.pop();
  }

  // Transición al nuevo estado.
  _states.push(state);
  // enter() sobre el nuevo estado.
  _states.top()->enter();
}

void
GameStatesManager::loadResources ()
{
  Ogre::ConfigFile cf;
  cf.load("resources.cfg");

  Ogre::ConfigFile::SectionIterator sI = cf.getSectionIterator();
  Ogre::String sectionstr, typestr, datastr;
  while (sI.hasMoreElements()) {
    sectionstr = sI.peekNextKey();
    Ogre::ConfigFile::SettingsMultiMap *settings = sI.getNext();
    Ogre::ConfigFile::SettingsMultiMap::iterator i;
    for (i = settings->begin(); i != settings->end(); ++i) {
      typestr = i->first;
      datastr = i->second;
      Ogre::ResourceGroupManager::getSingleton().addResourceLocation(datastr, typestr, sectionstr);
    }
  }
}

bool
GameStatesManager::configure ()
{
  if (!_root->restoreConfig()) {
    if (!_root->showConfigDialog()) {
      return false;
    }
  }

  _renderWindow = _root->initialise(true, "Arrow");

  _sceneManager = _root->createSceneManager(Ogre::ST_GENERIC, "SceneManager");

  _sceneManager->addRenderQueueListener( new Ogre::OverlaySystem() );
  Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
  _overlayManager = Ogre::OverlayManager::getSingletonPtr();

  return true;
}

GameStatesManager*
GameStatesManager::getSingletonPtr ()
{
  return msSingleton;
}

GameStatesManager&
GameStatesManager::getSingleton ()
{
  assert(msSingleton);
  return *msSingleton;
}

// Las siguientes funciones miembro delegan
// el evento en el estado actual.
bool
GameStatesManager::frameStarted
(const Ogre::FrameEvent& evt)
{
  _inputMgr->capture();
  return _states.top()->frameStarted(evt);
}

bool
GameStatesManager::frameEnded
(const Ogre::FrameEvent& evt)
{
  return _states.top()->frameEnded(evt);
}

bool
GameStatesManager::keyPressed
(const OIS::KeyEvent &e)
{
  _states.top()->keyPressed(e);
  return true;
}

bool
GameStatesManager::keyReleased
(const OIS::KeyEvent &e)
{
  _states.top()->keyReleased(e);
  return true;
}

bool
GameStatesManager::mouseMoved
(const OIS::MouseEvent &e)
{
  _states.top()->mouseMoved(e);
  return true;
}

bool
GameStatesManager::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
  _states.top()->mousePressed(e, id);
  return true;
}

bool
GameStatesManager::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
  _states.top()->mouseReleased(e, id);
  return true;
}

bool
GameStatesManager::initSDL () {
  if (SDL_Init(SDL_INIT_AUDIO) < 0)
  {
    return false;
  }
  // Llamar a  SDL_Quit al terminar.
  atexit(SDL_Quit);

  // Inicializando SDL mixer...
  if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS, 4096) < 0)
  {
    return false;
  }

  // Llamar a Mix_CloseAudio al terminar.
  atexit(Mix_CloseAudio);

  return true;
}
