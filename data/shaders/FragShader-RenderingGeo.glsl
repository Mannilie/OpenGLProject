#version 410
in vec4 outColor; 		
out vec4 fragColor; 
	
in float fragTime;

void main() 			
{ 						
	vec4 inverse = vec4(sin(outColor.x),
						cos(outColor.y), 
						tan(outColor.z), 1);
	fragColor = inverse; 
}						