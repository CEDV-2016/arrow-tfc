#include "Game.hpp"
#include "SoundFXManager.hpp"

Game::Game()
{
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

void Game::win()
{
  SoundFXManager::getSingletonPtr()->load("arrow_giggle.wav")->play();
}

void Game::lose()
{
  SoundFXManager::getSingletonPtr()->load("arrow_ouch.wav")->play();
}
