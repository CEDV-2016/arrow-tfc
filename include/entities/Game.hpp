#pragma once

#include <string>

class Game
{
public:

  Game();
  ~Game ();

  void setPlayerName(std::string name);
  std::string getPlayerName();

  void win();
  void lose();

private:

  std::string _player_name;
};
