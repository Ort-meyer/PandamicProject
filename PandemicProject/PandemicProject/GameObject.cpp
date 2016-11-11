#include "GameObject.h"
#include "GraphicsManager.h"
#include <glm\gtx\transform.hpp>

GameObject::GameObject()
{
}


GameObject::GameObject(vec3 p_position, vec3 p_target, vec3 p_up, unsigned int p_modelID, unsigned int p_textureID)
   :m_position(p_position), m_target(p_target), m_up(p_up), m_modelID(p_modelID), m_textureID(p_textureID)
{

}



GameObject::~GameObject()
{
}

void GameObject::Draw()
{
   mat4x4 t_world = lookAt(m_position, m_position + m_target, m_up);
   Graphics::GraphicsManager::Get()->DrawMesh(m_modelID, t_world, m_textureID);
}
