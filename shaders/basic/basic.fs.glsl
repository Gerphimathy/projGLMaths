#version 120 

varying vec4 v_Color;

// vec4 gl_FragColor; // predefinie

void main(void)
{
	gl_FragColor = v_Color;
}