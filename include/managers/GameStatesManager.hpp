#pragma once

#include <stack>
#include <Ogre.h>
#include <OgreOverlaySystem.h>
#include <OgreOverlayElement.h>
#include <OgreOverlayManager.h>
#include <OgreSingleton.h>
#include <OIS/OIS.h>
#include <CEGUI.h>
#include <RendererModules/Ogre/Renderer.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "InputManager.hpp"
#include "Track.hpp"
#include "TrackManager.hpp"
#include "SoundFX.hpp"
#include "SoundFXManager.hpp"

class GameState;

class GameStatesManager : public Ogre::FrameListener, public Ogre::Singleton<GameStatesManager>, public OIS::KeyListener, public OIS::MouseListener
{
public:
  GameStatesManager ();
  ~GameStatesManager (); // Limpieza de todos los estados.

  // Para el estado inicial.
  void start (GameState* state);

  // Funcionalidad para transiciones de estados.
  void changeState (GameState* state);
  void pushState (GameState* state);
  void popState ();
  void restartState (GameState* state);

  // Heredados de Ogre::Singleton.
  static GameStatesManager& getSingleton ();
  static GameStatesManager* getSingletonPtr ();

protected:
  Ogre::Root* _root;
  Ogre::SceneManager* _sceneManager;
  Ogre::RenderWindow* _renderWindow;
  TrackManager* _trackManager;
  TrackPtr _mainTrack;
  SoundFXManager* _pSoundFXManager;
  Ogre::OverlayManager* _overlayManager;

  // Funciones de configuración.
  void loadResources ();
  bool configure ();

  // Heredados de FrameListener.
  bool frameStarted (const Ogre::FrameEvent& evt);
  bool frameEnded (const Ogre::FrameEvent& evt);

  bool initSDL();

private:
  // Funciones para delegar eventos de teclado
  // y ratón en el estado actual.
  bool keyPressed (const OIS::KeyEvent &e);
  bool keyReleased (const OIS::KeyEvent &e);

  bool mouseMoved (const OIS::MouseEvent &e);
  bool mousePressed (const OIS::MouseEvent &e, OIS::MouseButtonID id);
  bool mouseReleased (const OIS::MouseEvent &e, OIS::MouseButtonID id);

  // Gestor de eventos de entrada.
  InputManager *_inputMgr;
  // Estados del juego.
  std::stack<GameState*> _states;
};
