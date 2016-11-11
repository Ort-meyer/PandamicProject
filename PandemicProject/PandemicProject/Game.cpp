#include "Game.h"

#include <glm\gtx\transform.hpp>


Game::Game()
{
}


Game::~Game()
{
}


void Game::Startup()
{
   // Create hard coded projection matrix
   Graphics::GraphicsManager::Get()->SetCameraProjection(perspective(radians(45.0f), 16.0f / 9.0f, 0.1f, 1000.0f));


   /// Create PhysX
   static PxDefaultErrorCallback gDefaultErrorCallback;
   static PxDefaultAllocator gDefaultAllocatorCallback;
   m_physxFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gDefaultAllocatorCallback, gDefaultErrorCallback);
   m_physics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_physxFoundation, PxTolerancesScale());
   m_cpuDispatcher = PxDefaultCpuDispatcherCreate(2); // This, I don't remember
   // Create world scene
   PxSceneDesc t_sceneDesc(m_physics->getTolerancesScale());
   t_sceneDesc.gravity = PxVec3(0, -9.81, 0);
   t_sceneDesc.cpuDispatcher = m_cpuDispatcher;
   t_sceneDesc.filterShader = PxDefaultSimulationFilterShader;
   m_worldScene = m_physics->createScene(t_sceneDesc);

   PxMaterial* t_groundMaterial = m_physics->createMaterial(0.5, 0.5, 0.6);
   PxRigidStatic* t_groundPlane = PxCreatePlane(*m_physics, PxPlane(0, 1, 0, 0), *t_groundMaterial);
   m_worldScene->addActor(*t_groundPlane);;


   m_player = new Player();

   /// Load a bunch of resources
   // Models
   unsigned int modelID = Graphics::GraphicsManager::Get()->CreateMesh("../resources/models/two.model");
   // Textures
   unsigned int textureID = Graphics::GraphicsManager::Get()->CreateTexture("../resources/textures/one.jpg");

   /// Create some world objects
   m_gameObjects.push_back(GameObject(vec3(0, 0, 100), vec3(0, 0, 1), vec3(0, 1, 0), 1, 1));
}


void Game::Run()
{
   while (true)
   {
      float t_dt = 0.017;// Hardcoded update frequency, so far


      /// Update the OS thingies. Events and such
      OSManager::Get()->Update();


      /// Update the game
      m_player->Update(t_dt);


      /// Simulate physics
      m_worldScene->simulate(t_dt);
      m_worldScene->fetchResults(true);


      for (size_t i = 0; i < m_gameObjects.size(); i++)
      {
         m_gameObjects.at(i).Draw();
      }


      /// End by drawing stuff
      Graphics::GraphicsManager::Get()->Update(t_dt); 

   }
}
