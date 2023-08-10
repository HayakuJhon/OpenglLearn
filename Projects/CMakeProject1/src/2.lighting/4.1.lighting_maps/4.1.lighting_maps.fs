#version 330 core
out vec4 FragColor;
struct Material{
	vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
struct Light{
	vec3 lightPos;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform Material material;
uniform Light light;
uniform vec3 viewPos;

in vec3 Normal;
in vec3 FragPos;

void main(){
	//ambient
	vec3 ambientColor = material.ambient * light.ambient;
	//diffuse
	vec3 lightDir = normalize(light.lightPos - FragPos);
	float dotValue = max(dot(normalize(Normal),lightDir),0.0);
	vec3 diffuseColor = light.diffuse * dotValue * material.diffuse;

	//specular
	vec3 reflectDir = normalize(reflect(-lightDir,Normal));
	vec3 viewDir = normalize(viewPos - FragPos);
	float dotSpecular = pow(max(dot(reflectDir,viewDir),0.0),material.shininess);
	vec3 specularColor = dotSpecular * light.specular * material.specular;

	//result
	vec3 result = ambientColor + diffuseColor + specularColor;
	FragColor = vec4(result,1.0);
	//FragColor = vec4(Normal,1.0);
}