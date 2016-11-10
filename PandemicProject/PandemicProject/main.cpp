#include <iostream>
#include "OSManager.h"
#include <SDL\SDL.h>

using namespace std;

int main(int numArgs, char * args[])
{
   WindowParams t_params;
   t_params.windowName = "Pandemic";
   t_params.argc = 0;
   t_params.argv = "";
   t_params.winPosX = 100;
   t_params.winPosY = 100;
   t_params.winSizeX = 1920;
   t_params.winSizeY = 1080;

   OSManager::Get()->CreateWindow(t_params);

   return 0;
}