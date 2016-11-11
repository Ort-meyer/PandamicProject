#pragma once
#include <vector>
#include "GraphicsManager.h"
#include "OSManager.h"
#include "Player.h"
#include "GameObject.h"
#include "PhysXManager.h"

using namespace std;
using namespace physx;
class Game
{
public:
   Game();
   ~Game();

   void Run();
   void Startup();

private:
   Player* m_player;
   vector<GameObject> m_gameObjects;

   // Uper physx stuff

   
};

