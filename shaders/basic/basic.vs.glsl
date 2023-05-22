#version 330 core

attribute vec3 a_position;
attribute vec3 a_color;
attribute vec2 a_texCoord;

varying vec4 v_color;

uniform mat4 u_rotationMatrix;
uniform mat4 u_projectionMatrix;

out vec2 f_texCoord;

void main(void)
{
	gl_Position = u_projectionMatrix * u_rotationMatrix * vec4(a_position, 1.0);

	f_texCoord = a_texCoord;

	v_color = vec4(a_color, 1.0);
}