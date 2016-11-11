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
   Graphics::GraphicsManager::Get()->SetCameraProjection(perspectiveFov(45, 1920, 1080, 1, 1000));

   m_player = new Player();

   /// Load a bunch of resources
   // Models
   unsigned int modelID = Graphics::GraphicsManager::Get()->CreateMesh("../resources/models/one.model");
   // Textures
   unsigned int textureID = Graphics::GraphicsManager::Get()->CreateTexture("../resources/textures/one.jpg");

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


      /// End by drawing stuff
      Graphics::GraphicsManager::Get()->Update(t_dt); 

   }
}
