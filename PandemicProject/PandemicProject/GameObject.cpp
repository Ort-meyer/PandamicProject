#include "GameObject.h"
#include "GraphicsManager.h"
#include <glm\gtx\transform.hpp>
#include <glm\gtc\quaternion.hpp>
#include "PhysXManager.h"
GameObject::GameObject()
{
}


GameObject::GameObject(vec3 p_position, vec3 p_target, vec3 p_up, unsigned int p_modelID, unsigned int p_textureID)
   :m_position(p_position), m_target(p_target), m_up(p_up), m_modelID(p_modelID), m_textureID(p_textureID)
{
   // Hax things into physx datatypes
   using namespace Physics;
   PxVec3* t_posPx = reinterpret_cast<PxVec3*>(&m_position);
   mat4x4 t_rotMat = lookAt(vec3(0), m_target, m_up);
   //PxQuat* t_oriPx = reinterpret_cast<PxQuat*>(&quat_cast(t_rotMat));
   PxQuat* t_oriPx= new PxQuat(0, 0, 0, 1);

   PxTransform t_trans = PxTransform(*t_posPx, *t_oriPx);
   PxMaterial* t_groundMaterial = PhysXManager::Get()->m_physics->createMaterial(0.5, 0.5, 0.6);
   m_physicsBody = PxCreateDynamic(*PhysXManager::Get()->m_physics, t_trans, PxBoxGeometry(PxVec3(0.5, 0.5, 0.5)),*t_groundMaterial, 10.0f);
   PhysXManager::Get()->m_worldScene->addActor(*m_physicsBody);
}



GameObject::~GameObject()
{
}

void GameObject::UpdatePositionFromPhysics()
{
   // This seems overly unnecessary
   PxVec3 t_posPx = m_physicsBody->getGlobalPose().p;
   PxQuat t_oriPx = m_physicsBody->getGlobalPose().q;

   vec3* t_pos = reinterpret_cast<vec3*>(&t_posPx);
   quat* t_ori = reinterpret_cast<quat*>(&t_oriPx);

   mat4x4 t_rotMat = mat4_cast(*t_ori);
   mat4x4 t_transMat = translate(*t_pos);

   m_position = *t_pos;
   m_target = vec3(t_rotMat * vec4(0, 0, 1, 0));
   m_up = vec3(t_rotMat * vec4(0, 1, 0, 0));

}

void GameObject::Draw()
{
   mat4x4 t_world = lookAt(m_position, m_position + m_target, m_up);
   Graphics::GraphicsManager::Get()->DrawMesh(m_modelID, t_world, m_textureID);
}
