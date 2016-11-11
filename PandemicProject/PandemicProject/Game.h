#pragma once
#include <vector>
#include "GraphicsManager.h"
#include "OSManager.h"
#include "Player.h"
#include "GameObject.h"

// The fun stuff
#include <PhysX\PxPhysicsAPI.h>

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
   PxFoundation* m_physxFoundation;
   PxPhysics* m_physics;
   PxScene* m_worldScene;
   PxDefaultCpuDispatcher* m_cpuDispatcher;
   
   
};

