#version 120

varying vec4 v_color;

uniform float u_time;

void main(void)
{
	gl_FragColor = v_color;
}