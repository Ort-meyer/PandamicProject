#include <iostream>
#include "OSManager.h"
#include "GraphicsManager.h"
#include <SDL\SDL.h>
#include "Game.h"
using namespace std;

int main(int numArgs, char * args[])
{
   WindowParams t_params;
   t_params.windowName = "Pandemic";
   t_params.argc = 0;
   t_params.argv = "";
   t_params.winPosX = 600;
   t_params.winPosY = 100;
   t_params.winSizeX = 1920;
   t_params.winSizeY = 1080;

   // This also initializes OSmanager by calling get. Important to do first
   OSManager::Get()->CreateWindow(t_params);
   // This inits graphics
   Graphics::GraphicsManager::Get();

   Game game;
   game.Startup();
   game.Run();

   int derp;
   cin >> derp;
   return 0;
}