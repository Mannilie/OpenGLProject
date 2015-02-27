//GEOMETRY SHADER
#version 410

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

in vec3  geomPosition[];
in float geomLifetime[];
in float geomLifespan[];

out vec4 fragColor;

uniform mat4 projView;
uniform mat4 cameraWorld;

uniform float startSize;
uniform float endSize;

uniform vec4 startColor;
uniform vec4 endColor;

void main()
{
	//calculate a 0-1 value for the interpolation 
	//of start/end pairs
	float t = geomLifetime[0] / geomLifespan[0];
	
	//interpolate to find the correct color
	fragColor = mix(startColor, endColor, t);

	//half the size so that the total width of the
	//quad will be correct
	float halfSize = mix(startSize, endSize, t) * 0.5f;

	//create scaled local-space verticies
	vec3 corners[4];
	corners[0] = vec3(halfSize, -halfSize, 0);
	corners[1] = vec3(halfSize, halfSize, 0);
	corners[2] = vec3(-halfSize, -halfSize, 0);
	corners[3] = vec3(-halfSize, halfSize, 0);

	//build the 3 axis of the rotation matrix
	vec3 forward = normalize(cameraWorld[3].xyz - geomPosition[0]);
	vec3 right = cross(cameraWorld[1].xyz, forward);
	vec3 up = cross(forward, right);

	//combine axies into matrix
	mat3 billboardRot = mat3(right, up, forward);

	//rotate the verts
	corners[0] = billboardRot * corners[0];
	corners[1] = billboardRot * corners[1];
	corners[2] = billboardRot * corners[2];
	corners[3] = billboardRot * corners[3];

	//translate the verts
	corners[0] += geomPosition[0];
	corners[1] += geomPosition[0];
	corners[2] += geomPosition[0];
	corners[3] += geomPosition[0];

	//transform verts by the projection view and output them
	gl_Position = projView * vec4(corners[0], 1);
	EmitVertex();
	gl_Position = projView * vec4(corners[1], 1);
	EmitVertex();
	gl_Position = projView * vec4(corners[2], 1);
	EmitVertex();
	gl_Position = projView * vec4(corners[3], 1);
	EmitVertex();
}