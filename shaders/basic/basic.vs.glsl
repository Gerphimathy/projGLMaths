#version 330 core

in vec3 a_position;
in vec3 a_color;
in vec2 a_texCoord;

out vec4 v_color;

uniform vec3 u_scale;
uniform vec3 u_meshPosition;
uniform vec4 u_rotationMatrix;
uniform mat4 u_projectionMatrix;
uniform vec3 camPos;
uniform vec4 camRot;


out vec2 f_texCoord;

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
}

void main(void)
{
	f_texCoord = a_texCoord;
	v_color = vec4(a_color, 1.0);

	vec3 machin = vec3(
	a_position.x * u_scale.x,
	a_position.y * u_scale.y,
	a_position.z * u_scale.z
	);
	machin = rotate(u_rotationMatrix, machin);
	machin += u_meshPosition;
	machin -= camPos;
	machin = rotate(-camRot, machin);
	gl_Position = u_projectionMatrix * vec4(machin, 1);
}