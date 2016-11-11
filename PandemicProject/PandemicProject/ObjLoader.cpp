#include "ObjLoader.h"

#include <glm\glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
using namespace glm;
using namespace std;
namespace GraphicsInternal
{


   ObjLoader::ObjLoader()
   {
   }


   ObjLoader::~ObjLoader()
   {
   }

   vector<Vertex> ObjLoader::LoadModel(const char * p_fileName)
   {
      string line, text;
      ifstream in(p_fileName);
      std::vector<glm::vec3> vertexData;
      std::vector<glm::vec2> uvMappingData;
      std::vector<glm::vec3> normalData;
      std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
      while (getline(in, line))
      {
         text += line + "\n";
      }
      istringstream stream(text);

      while (!stream.eof())
      {
         std::string currentInstruction;
         stream >> currentInstruction;
         if (currentInstruction.compare("v") == 0)
         {
            // Vertex data found, make vec3
            float x, y, z;
            stream >> x >> y >> z;
            vertexData.push_back(glm::vec3(x, y, z));
         }
         else if (currentInstruction.compare("vt") == 0)
         {
            // uv data found, make vec2
            float u, v;
            stream >> u >> v;
            uvMappingData.push_back(glm::vec2(u, v));
         }
         else if (currentInstruction.compare("vn") == 0)
         {
            // normal data found, make vec3
            float nx, ny, nz;
            stream >> nx >> ny >> nz;
            normalData.push_back(glm::vec3(nx, ny, nz));
         }
         else if (currentInstruction.compare("f") == 0)
         {
            // Guessing its only three connected vertexpoints (No quads allowed here!)
            for (size_t i = 0; i < 3; i++)
            {
               // three ints for saving the connected vertex, normal and uvmap
               int vertexIndex, uvIndex, normalIndex;
               // Reading three connected things, v/u/n
               std::string connectedData;
               stream >> connectedData;
               // scan the given string since its in format v/u/n
               sscanf_s(connectedData.c_str(), "%i/%i/%i", &vertexIndex, &uvIndex, &normalIndex);
               // insert info into vectors
               vertexIndices.push_back(abs(vertexIndex));
               uvIndices.push_back(abs(uvIndex));
               normalIndices.push_back(abs(normalIndex));
            }
         }
      }
      // all data should now be read, processing starts here TODO could be done during reading of faces
      // go thorugh all the faces, doesnt matter which indices vector we take, they are all the same size
      size_t count = vertexIndices.size();
      // TODO should be a complete mesh data, not just pos
      std::vector<Vertex> completedVertices;
      for (size_t i = 0; i < count; i++)
      {
         // -1 cuz obj starts at 1 and c++ at 0. [] on the second vector access since we know the size of them and shouldnt miss
         glm::vec3 vertexPosition = vertexData.at(vertexIndices[i] - 1);
         glm::vec2 vertexUVMap = uvMappingData.at(uvIndices[i] - 1);
         glm::vec3 vertexNormal = normalData.at(normalIndices[i] - 1);
         // push the completed vertex TODO should be a complete mesh data, not just pos
         completedVertices.push_back(Vertex(vertexPosition, vertexNormal, vertexUVMap));
      }
      return completedVertices;

   }
}