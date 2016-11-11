#pragma once
#include <glm\glm.hpp>

#include <PhysX\PxPhysicsAPI.h>
using namespace physx;
using namespace glm;
class GameObject
{
public:
   GameObject(vec3 p_position, vec3 p_target, vec3 p_up, unsigned int p_modelID, unsigned int p_textureID);
   GameObject();
   ~GameObject();
   void UpdatePositionFromPhysics();
   void Draw();
private:
   vec3 m_position;
   vec3 m_target;
   vec3 m_up;

   unsigned int m_modelID;
   unsigned int m_textureID;

   PxRigidDynamic* m_physicsBody;

};

