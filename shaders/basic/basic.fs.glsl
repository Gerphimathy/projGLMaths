#version 330 core

uniform float u_time;

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

uniform Material u_material;

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 color;
};
uniform Light u_light;

varying vec3 f_normal;
in vec3 FragPos;
in vec2 f_texCoords;
in vec3 v_camPos;

uniform sampler2D u_texture;
in float f_usetexture;

void main(void)
{


	// ambient
	vec3 ambient = u_light.color * u_material.ambient;

	// diffuse
	vec3 norm = normalize(f_normal);

	vec3 lightDir = normalize(u_light.position - FragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = u_light.color * (diff * u_material.diffuse);

	// specular
	vec3 viewDir = normalize(v_camPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
	vec3 specular = u_light.color * (spec * u_material.specular);

	if(f_usetexture > 0.5)gl_FragColor = texture2D(u_texture, f_texCoords) * vec4(ambient + diffuse + specular, 1.0);
	else gl_FragColor = vec4(ambient + diffuse + specular, 1.0);
}
