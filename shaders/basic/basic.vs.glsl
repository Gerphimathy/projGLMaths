#version 120

attribute vec2 a_Position;
attribute vec3 a_Color;

uniform float u_Time;

varying vec4 v_Color;
// varying vec4 gl_Position; // predefini

void main(void)
{
	vec2 movement = vec2(sin(u_Time), 0.0);

	vec2 pos = a_Position + movement;

	v_Color = vec4(a_Color.rgb, 1.0);

	gl_Position = vec4(pos, 0.0, 1.0);
}