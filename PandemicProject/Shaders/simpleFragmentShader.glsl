#version 430
in vec4 posF;
in vec2 texCoordF;
in vec4 normalF;

out vec4 color;

//vec3 lightDir = vec3(1, -1, 1);
vec3 lightDir = vec3(0.5, -1, 1);

uniform sampler2D sampler;

void main() 
{
	// Debug red color
	//color = vec4(1,0,0,0);

	// Calculate light factor
	float ambientFactor = 0.1f;
	float diffuseFactor = dot(normalize(-lightDir), normalize(normalF.xyz));
	// Clamp to avoid negative values
	diffuseFactor = clamp(diffuseFactor, 0, 1);
	// Get final color by samply and multiplying with total light factor
	color = texture2D(sampler, texCoordF) * (diffuseFactor + ambientFactor);
}