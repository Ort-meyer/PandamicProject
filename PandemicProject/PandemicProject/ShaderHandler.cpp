// This class
#include "ShaderHandler.h"

// Standard libraries
#include <fstream>
#include <iostream>

using namespace std;
namespace GraphicsInternal
{


   ShaderHandler::ShaderHandler()
   {
      CreateAllShaderPrograms();
   }

   ShaderHandler::~ShaderHandler()
   {
   }

   GLuint ShaderHandler::GetShaderProgram(ShaderProgram p_shaderProgram)
   {
      return m_shaderPrograms[p_shaderProgram]; // Somewhat unsafe but cba
   }

   std::string ShaderHandler::ReadShader(string p_fileName)
   {
      ifstream t_infile{ p_fileName.c_str() };
      string r_fileString{ istreambuf_iterator<char>(t_infile), istreambuf_iterator<char>() };
      return r_fileString;
   }

   GLuint ShaderHandler::LoadShader(ShaderInfo p_info)
   {
      // Create the shader
      GLuint r_shader = glCreateShader(p_info.shaderType);
      // Read shader text
      string t_shaderText = ReadShader(p_info.fileName);
      // Compile shader
      const GLchar* t_shaderTextChar = t_shaderText.c_str();
      glShaderSource(r_shader, 1, &t_shaderTextChar, NULL);
      glCompileShader(r_shader);
      // Check that it worked
      GLint t_compiled;
      glGetShaderiv(r_shader, GL_COMPILE_STATUS, &t_compiled);
      if (!t_compiled)
      {
         GLsizei t_len;
         glGetShaderiv(r_shader, GL_INFO_LOG_LENGTH, &t_len);

         GLchar* t_log = new GLchar[t_len + 1];
         glGetShaderInfoLog(r_shader, t_len, &t_len, t_log);
         cout << "Shader compilation failed: " << t_log << endl;

         return 0;
      }
      return r_shader;
   }

   GLuint ShaderHandler::CreateShaderProgram(std::vector<ShaderInfo> p_programShaders)
   {
      // Create program
      GLuint r_programHandle = glCreateProgram();
      // Iterate through all shaders
      for (size_t i = 0; i < p_programShaders.size(); i++)
      {
         GLuint t_shader = LoadShader(p_programShaders[i]);
         // Attack loaded shader to program
         glAttachShader(r_programHandle, t_shader);
      }

      glLinkProgram(r_programHandle);
      // Verify linking worked
      GLint t_linked;
      glGetProgramiv(r_programHandle, GL_LINK_STATUS, &t_linked);
      if (!t_linked)
      {
         GLsizei t_len;
         glGetProgramiv(r_programHandle, GL_INFO_LOG_LENGTH, &t_len);
         GLchar* t_log = new GLchar[t_len + 1];
         glGetProgramInfoLog(r_programHandle, t_len, &t_len, t_log);
         cout << "Shader linking failed: " << t_log << endl;
         return 0;
      }


      return r_programHandle;
   }

   void ShaderHandler::CreateAllShaderPrograms()
   {
      // Create default shader
      vector<ShaderInfo> t_shaderProgramInfo;
      t_shaderProgramInfo.push_back(ShaderInfo(GL_VERTEX_SHADER, "../Shaders/simpleVertexShader.glsl"));
      t_shaderProgramInfo.push_back(ShaderInfo(GL_FRAGMENT_SHADER, "../Shaders/simpleFragmentShader.glsl"));
      GLuint t_shaderProgram = CreateShaderProgram(t_shaderProgramInfo);
      m_shaderPrograms[ShaderProgram::DefaultShader] = t_shaderProgram;
   }

}