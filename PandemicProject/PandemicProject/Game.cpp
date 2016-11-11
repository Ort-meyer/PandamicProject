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
      for (size_t i = 0; i < m_gameObjects.size(); i++)
      {
         m_gameObjects.at(i).Draw();
      }


      /// End by drawing stuff
      Graphics::GraphicsManager::Get()->Update(t_dt); 

   }
}
