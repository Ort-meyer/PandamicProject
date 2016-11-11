#pragma once
#include <glm\glm.hpp>
#include <GL2\glew.h>
#include <unordered_map>
#include <vector>

#include "ShaderHandler.h"
#include "Vertex.h"
using namespace std;
using namespace glm;


namespace Graphics
{
   struct DrawObject
   {
      DrawObject(mat4x4 p_world, GLuint p_textureHandle)
         :world(p_world), textureHandle(p_textureHandle)
      {
      
      }
         mat4x4 world;
         GLuint textureHandle;
   };

   class GraphicsManager
   {
   public:
      static GraphicsManager* Get();

      void Update(float p_dt);
      void DrawMesh(unsigned int p_meshID, mat4x4 p_worldMatrix, unsigned int p_textureID);
      GLuint CreateMesh(vector<Vertex> p_vertices);
      GLuint CreateMesh(const char* p_fileName);
      GLuint CreateTexture(const char* p_fileName);
      void SetCameraMatrix(mat4x4 p_newMatrix);
      void SetCameraMatrix(vec3 p_position, vec3 p_target, vec3 p_up);
      void SetCameraProjection(mat4x4 p_projection);

   private:
      GraphicsManager();
      ~GraphicsManager();

      static GraphicsManager* m_singleton;

      GraphicsInternal::ShaderHandler* m_shaderHandler;

      mat4x4 m_cameraMatrix;
      mat4x4 m_projectionMatrix;
      unordered_map<unsigned int, unsigned int> m_meshSizes;
      unordered_map<unsigned int, vector<DrawObject>> m_meshDrawLists;
   };

}