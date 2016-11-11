#pragma once

// Standard libraries
#include <string>
#include <vector>
#include <unordered_map>

// Third party
#include <GL2\glew.h>

namespace GraphicsInternal
{
   struct ShaderInfo
   {
      ShaderInfo(GLenum p_type, std::string p_fileName)
         :shaderType(p_type), fileName(p_fileName) {}
      GLenum shaderType;
      std::string fileName;
   };

   /**
   Lists all available shader programs.
   If we want to expand with more shader programs,
   they have to be included here, and loading has to
   be made. The idea is to mape a ShaderProgram enum to
   a GLuint or something*/
   enum class ShaderProgram
   {
      DefaultShader,
   };

   /**
   Class to handle shader loading and shader storage.
   CBA to make it a singleton: it will only be instantiated
   by a singleton anyways*/
   class ShaderHandler
   {
   public:
      ShaderHandler();
      ~ShaderHandler();
      GLuint GetShaderProgram(ShaderProgram p_shaderProgram);

   private:
      // Help methods to get a shader program up and running
      std::string ReadShader(std::string);
      GLuint LoadShader(ShaderInfo p_info);
      GLuint CreateShaderProgram(std::vector<ShaderInfo> p_programShaders);
      void CreateAllShaderPrograms();

      // Map of all shader program handles to each enum
      std::unordered_map<ShaderProgram, GLuint> m_shaderPrograms;
   };
}