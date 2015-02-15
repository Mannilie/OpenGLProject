#version 410								
in vec4 Position; 								
in vec4 Color; 									
out vec4 outColor; 								

uniform mat4 projView; 							
uniform float time;							
uniform float heightScale;		
				
out float fragTime;

void main() 									
{ 				
	fragTime = time;								
	outColor = Color; 							
	vec4 P = Position;			
	P.y += sin(time + sqrt(Position.x));
	gl_Position = projView * P; 				
}