#pragma once
#include <glm\glm.hpp>
#include "OSManager.h"
using namespace glm;
class Player
{
public:
   Player();
   ~Player();

   void Update(float p_dt);

private:
   vec3 m_position;
   vec3 m_target;
   vec3 m_up;

   float m_movementSpeed;
   float m_turnSpeed;
};

