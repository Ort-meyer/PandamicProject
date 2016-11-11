#pragma once
#include "Vertex.h"
#include <vector>
using namespace std;
namespace GraphicsInternal
{
   class ObjLoader
   {
   public:
      ObjLoader();
      ~ObjLoader();

      vector<Vertex> LoadModel(const char*);

   };

}