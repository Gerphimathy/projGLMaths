#version 120

varying vec4 v_color;

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

uniform mat4 u_rotationMatrix;
uniform mat4 u_projectionMatrix;

in vec3 FragPos;

void main(void)
{

	//TODO: Give camera position
	vec3 viewPos = vec3(0.0, 0.0, 0.0);

	// ambient
	vec3 ambient = u_light.color * u_material.ambient;

	// diffuse
	vec3 norm = normalize(f_normal);

	vec3 lightDir = normalize(u_light.position - FragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = u_light.color * (diff * u_material.diffuse);

	// specular
	vec3 viewDir = normalize(viewPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
	vec3 specular = u_light.color * (spec * u_material.specular);

	vec3 result = ambient + diffuse + specular;
	gl_FragColor = vec4(result, 1.0);
}