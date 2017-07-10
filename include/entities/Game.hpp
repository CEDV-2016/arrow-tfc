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

  void complete_Forgotten_Forest();
  void complete_Frozen_Ashes();
  bool game_completed();
  
private:

  std::string _player_name;

  bool forgotten_forest_completed, frozen_ashes_completed;
};
