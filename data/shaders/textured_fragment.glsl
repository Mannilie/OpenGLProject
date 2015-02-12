#version 410

in vec2 fragTexCoord;
out vec4 fragColor;
uniform sampler2D diffuse;

void main() 			
{ 						
	vec4 White = vec4(1, 1, 1, 1);
	fragColor = White - texture(diffuse, fragTexCoord); 
}						