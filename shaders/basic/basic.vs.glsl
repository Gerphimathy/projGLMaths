#version 120

attribute vec3 a_Position;
attribute vec3 a_Color;

varying vec4 v_Color;
// varying vec4 gl_Position; // predefini

void main(void)
{
	v_Color = vec4(a_Color.rgb, 1.0);

	gl_Position = vec4(a_Position, 1.0);
}