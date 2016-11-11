#version 430
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

uniform mat4 MVP;

out vec4 posF;
out vec2 texCoordF;
out vec4 normalF;

void main() 
{
	posF = MVP * vec4(position, 1.0);
	normalF = vec4(normal, 0); //multiply with world matrix to get rotation right
	texCoordF = texCoord;
	gl_Position = posF;
}