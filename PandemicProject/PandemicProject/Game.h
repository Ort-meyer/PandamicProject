#pragma once
#include "GraphicsManager.h"
#include "OSManager.h"
#include "Player.h"
class Game
{
public:
   Game();
   ~Game();

   void Run();
   void Startup();

private:
   Player* m_player;
};

