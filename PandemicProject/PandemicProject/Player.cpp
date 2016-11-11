#include "Player.h"
#include "GraphicsManager.h"
#include <glm\gtx\transform.hpp>

Player::Player()
{
   m_movementSpeed = 0.001f;
   m_turnSpeed = 0.001f;
}


Player::~Player()
{
}

void Player::Update(float p_dt)
{
   /// Translation
   vec3 t_movement;
   // Forward and back
   if (OSManager::Get()->KeysDown((int)InputKey::W))
      t_movement += m_target * m_movementSpeed * p_dt;
   if (OSManager::Get()->KeysDown((int)InputKey::S))
      t_movement -= m_target * m_movementSpeed * p_dt;

   // Right and left
   // Compute right vector
   vec3 t_right = cross(m_up, m_target);
   if (OSManager::Get()->KeysDown((int)InputKey::D))
      t_movement -= t_right * m_movementSpeed * p_dt;
   if (OSManager::Get()->KeysDown((int)InputKey::A))
      t_movement += t_right * m_movementSpeed * p_dt;

   // Up and down
   if (OSManager::Get()->KeysDown((int)InputKey::Up))
      t_movement += m_up * m_movementSpeed * p_dt;
   if (OSManager::Get()->KeysDown((int)InputKey::Down))
      t_movement -= m_up * m_movementSpeed * p_dt;

   m_position += t_movement;

   /// Rotation
   // Get deltas and convert to floats
   int t_dx;
   int t_dy;
   OSManager::Get()->GetMouseMovement(t_dx, t_dy);
   /* Might actually be an idea to normalize the deltas
   since y moves slower than x due to x being more pixels.*/
   float t_rotationX = (float)t_dx * m_turnSpeed;
   float t_rotationY = (float)t_dy * m_turnSpeed;
   // Get vec4s so we can make algebra magic
   vec4 t_up4 = vec4(normalize(m_up), 0);
   vec4 t_target4 = vec4(normalize(m_target), 0);
   vec4 t_right4 = vec4(cross(m_target, m_up), 0); // Might be wrong order of cross

   // Rotate around right vector
   mat4x4 t_rightRotateMat = rotate(-t_rotationY, vec3(t_right4));
   t_target4 = t_rightRotateMat * t_target4;
   //t_up4 = t_rightRotateMat * t_up4;

   // Rotate around up vector
   //mat4x4 t_upRotateMat = rotate(t_rotationX, vec3(t_up4));
   mat4x4 t_upRotateMat = rotate(-t_rotationX, vec3(0, 1, 0));
   t_target4 = t_upRotateMat * t_target4;

   // Store results
   m_target = vec3(t_target4);
   m_up = vec3(t_up4);

   Graphics::GraphicsManager::Get()->SetCameraMatrix(m_position, m_target, m_up);

}
