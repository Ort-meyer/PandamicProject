#include "GraphicsManager.h"

#include <iostream>
#include <SOIL\SOIL.h>
#include "Vertex.h"
#include "ObjLoader.h"

#include <glm\gtx\transform.hpp>
namespace Graphics
{
   using namespace GraphicsInternal;
   GraphicsManager* GraphicsManager::m_singleton = nullptr;

   GraphicsManager * GraphicsManager::Get()
   {
      if (m_singleton == nullptr)
         m_singleton = new GraphicsManager();
      return m_singleton;
   }
   void GraphicsManager::Update(float p_dt)
   {
      glClearColor(0, 0, 1, 0);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // Get camera matrix

      // Start render with default shader
      GLuint t_shaderProgram = m_shaderHandler->GetShaderProgram(ShaderProgram::DefaultShader);
      glUseProgram(t_shaderProgram);

      // Iterate over all meshes to draw them
      for (auto it = m_meshDrawLists.begin(); it != m_meshDrawLists.end(); ++it)
      {
         // Iterate over all matrices for current mesh
         size_t t_numMatrices = it->second.size();
         for (size_t i = 0; i < t_numMatrices; i++)
         {
            mat4x4 mvp = m_projectionMatrix * m_cameraMatrix * it->second.at(i).world;
            GLuint mvpHandle = glGetUniformLocation(t_shaderProgram, "MVP");
            glUniformMatrix4fv(mvpHandle, 1, GL_FALSE, &mvp[0][0]);
            GLuint samplerHandle = glGetUniformLocation(t_shaderProgram, "sampler");
            glUniform1i(samplerHandle, 0); // 0 Is the gl texture's id (the 0 from GL_TEXTURE0) ... I think

                                           // Enable attribs
            glEnableVertexAttribArray(0); // Positions
            glEnableVertexAttribArray(1); // Normals
            glEnableVertexAttribArray(2); // Texture coordinates
                                          // Bind current buffer
            glBindBuffer(GL_ARRAY_BUFFER, it->first);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)24);

            // Activate texture
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, it->second.at(i).textureHandle);

            glDrawArrays(GL_TRIANGLES, 0, m_meshSizes[it->first]);
            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
            glDisableVertexAttribArray(2);
         }
         // Clear draw list for this mesh
         it->second.clear();
      }
   }

   void Graphics::GraphicsManager::DrawMesh(unsigned int p_meshID, mat4x4 p_worldMatrix, unsigned int p_textureID)
   {
      if (m_meshDrawLists.find(p_meshID) == m_meshDrawLists.end())
      {
         // Mesh didn't exist! We do nothing. This could be changed for debug assistance
         cout << "tried to load mesh that didn't exist" << endl;
         return;
      }

      m_meshDrawLists[p_meshID].push_back(DrawObject(p_worldMatrix, p_textureID));
   }

   GLuint GraphicsManager::CreateMesh(vector<Vertex> p_vertices)
   {
      GLuint r_positionBuffer;
      glGenBuffers(1, &r_positionBuffer);
      glBindBuffer(GL_ARRAY_BUFFER, r_positionBuffer);
      glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * p_vertices.size(), &p_vertices[0], GL_STATIC_DRAW);
      glFinish();
      // Create empty draw list for new mesh
      m_meshDrawLists[r_positionBuffer] = vector<DrawObject>();
      m_meshSizes[r_positionBuffer] = p_vertices.size();
      //SDLManager::Get()->SetLoadContext(false);
      return r_positionBuffer;
   }

   GLuint GraphicsManager::CreateMesh(const char * p_fileName)
   {
      ObjLoader objLoader;
      return CreateMesh(objLoader.LoadModel(p_fileName));
   }

   GLuint GraphicsManager::CreateTexture(const char * p_fileName)
   {
      // Let soil do all the work
      GLuint r_texturehandle = SOIL_load_OGL_texture(p_fileName, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
         SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
      if (0 == r_texturehandle)
      {
         // Shit went wrong. Error handling?
         printf("SOIL loading error: '%s'\n", SOIL_last_result());
         printf(p_fileName);
      }
      return r_texturehandle;
   }

   void GraphicsManager::SetCameraMatrix(mat4x4 p_newMatrix)
   {
      m_cameraMatrix = p_newMatrix;
   }

   void GraphicsManager::SetCameraMatrix(vec3 p_position, vec3 p_target, vec3 p_up)
   {
      m_cameraMatrix = lookAt(p_position, p_position + p_target, p_up);
   }

   void GraphicsManager::SetCameraProjection(mat4x4 p_projection)
   {
      m_projectionMatrix = p_projection;
   }


   GraphicsManager::GraphicsManager()
   {
      m_shaderHandler = new GraphicsInternal::ShaderHandler();
   }


   GraphicsManager::~GraphicsManager()
   {
   }
}