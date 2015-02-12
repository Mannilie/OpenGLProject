#version 410								

in vec4 position; 								
in vec2 texCoord; 	
								
out vec2 fragTexCoord; 								

uniform mat4 projView; 			
				
void main() 									
{ 												
	fragTexCoord = texCoord; 							
	gl_Position = projView * position; 				
}