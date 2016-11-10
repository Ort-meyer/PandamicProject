#pragma once
#include <SDL\SDL.h>


#pragma once
/**
Struct to set parameters when creating a window*/
struct WindowParams
{
   int argc;
   char* argv;
   const char* windowName;
   float winSizeX;
   float winSizeY;
   float winPosX;
   float winPosY;
};

enum class InputKey
{
   W = 0x01,
   S = 0x02,
   A = 0x04,
   D = 0x08,
   Up = 0x10,
   Down = 0x20,
};


class OSManager
{
public:
   
   static OSManager* Get();
   void CreateWindow(WindowParams p_params);

   void Update();
   bool KeysDown(int p_keys);
   void GetMouseMovement(int& o_x, int& o_y);

private:

   OSManager();
   ~OSManager();

   static OSManager* m_singleton;

   void UpdateInput();
   void UpdateMouseInput();

   int m_keysPressed;

   int m_deltaX;
   int m_deltaY;

   SDL_Window* m_window;
   SDL_GLContext m_glContext;
   
};


