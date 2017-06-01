#include "GameStatesManager.hpp"
#include "IntroState.hpp"
#include "MainState.hpp"
#include "NewGameState.hpp"
#include "PlayState.hpp"
#include "PauseState.hpp"
#include "CreditsState.hpp"
#include "InformationState.hpp"
#include "RankingState.hpp"
#include "EndState.hpp"
#include "DialogState.hpp"

#include <iostream>

int main () {

  GameStatesManager* game = new GameStatesManager();
  new IntroState();
  new MainState();
  new NewGameState();
  new PlayState();
  new PauseState();
  new CreditsState();
  new RankingState();
  new InformationState();
  new EndState();
  new DialogState();

  try
  {
    game->start(IntroState::getSingletonPtr());
  }
  catch (Ogre::Exception& e)
  {
    std::cerr << "Exception detected: " << e.getFullDescription();
  }

  delete game;

  return 0;
}
