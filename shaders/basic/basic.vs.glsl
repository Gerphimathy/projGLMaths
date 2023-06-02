#version 330 core

in vec3 a_position;
in vec3 a_normal;
in vec2 a_texCoord;

uniform float u_usetexture;
out float f_usetexture;


uniform vec3 u_scale;
uniform vec3 u_meshPosition;
uniform vec4 u_meshRotation;
uniform mat4 u_projectionMatrix;
uniform vec3 camPos;
uniform vec4 camRot;


out vec2 f_texCoords;
out vec3 FragPos;
out vec3 f_normal;
out vec3 v_camPos;

vec3 rotate(vec4 rotation, vec3 position) {

	vec3 u = rotation.xyz;

	vec3 temp = vec3(
		u.y * position.z - u.z * position.y,
		u.z * position.x - u.x * position.z,
		u.x * position.y - u.y * position.x
	) * 2.0;

	return position
	+ temp * rotation.w
	+ vec3(
		u.y * temp.z - u.z * temp.y,
		u.z * temp.x - u.x * temp.z,
		u.x * temp.y - u.y * temp.x
	);

	/*
	vec4 pos = vec4(position,0);
	vec4 conj = -rotation;
	pos = rotation * pos;
	pos = pos * conj;

	return (pos.xyz);
	*/

}

void main(void)
{
	f_usetexture = u_usetexture;

	//Output to fragment shader
	f_texCoords = a_texCoord;
	f_normal = rotate(u_meshRotation, a_normal);
	v_camPos = camPos;


	//Calculate position
	vec3 machin = vec3(
	a_position.x * u_scale.x,
	a_position.y * u_scale.y,
	a_position.z * u_scale.z
	);
	machin = rotate(u_meshRotation, machin);
	machin += u_meshPosition;
	FragPos = machin;
	machin -= camPos;
	machin = rotate(camRot, machin);
	gl_Position = u_projectionMatrix * vec4(machin, 1);


}
