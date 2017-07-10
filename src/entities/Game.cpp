#include "Game.hpp"
#include "SoundFXManager.hpp"

Game::Game()
{
  forgotten_forest_completed = frozen_ashes_completed = false;
}

Game::~Game()
{
}

void Game::setPlayerName(std::string name)
{
  _player_name = (name == "") ? "Arrow" : name;
}

std::string Game::getPlayerName()
{
  return _player_name;
}

void Game::complete_Forgotten_Forest()
{
  forgotten_forest_completed = true;

  if (frozen_ashes_completed)
  {
    win();
  }
}

void Game::complete_Frozen_Ashes()
{
  frozen_ashes_completed = true;

  if (forgotten_forest_completed)
  {
    win();
  }
}

void Game::win()
{
  SoundFXManager::getSingletonPtr()->load("arrow_giggle.wav")->play();
}

void Game::lose()
{
  SoundFXManager::getSingletonPtr()->load("arrow_ouch.wav")->play();
}

bool Game::game_completed()
{
  return forgotten_forest_completed && frozen_ashes_completed;
}
