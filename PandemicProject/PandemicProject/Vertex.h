#pragma once
#include <glm\glm.hpp>
using namespace glm;

/**
Struct for vertex.*/
struct Vertex
{
   Vertex(vec3 p_pos, vec3 p_norm, vec2 p_tex)
      :position(p_pos), normal(p_norm), texCoord(p_tex) {}
   vec3 position;
   vec3 normal;
   vec2 texCoord;
};