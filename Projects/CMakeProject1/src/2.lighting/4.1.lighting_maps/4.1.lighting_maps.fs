#version 330 core
out vec4 FragColor;
struct Material{
	sampler2D diffuse;
    sampler2D specular;
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
in vec2 TexCoord;

void main(){
	vec3 diffuse = vec3(texture(material.diffuse,TexCoord));
	vec3 specular = vec3(texture(material.specular,TexCoord));
	//diffuse
	vec3 lightDir = normalize(light.lightPos - FragPos);
	float dotValue = max(dot(normalize(Normal),lightDir),0.0);
	vec3 diffuseColor = light.diffuse * dotValue * diffuse;

	//specular
	vec3 reflectDir = normalize(reflect(-lightDir,Normal));
	vec3 viewDir = normalize(viewPos - FragPos);
	float dotSpecular = pow(max(dot(reflectDir,viewDir),0.0),material.shininess);
	vec3 specularColor = dotSpecular * light.specular * specular;

	//result
	vec3 result = diffuseColor + specularColor;
	FragColor = vec4(result,1.0);
	//FragColor = vec4(Normal,1.0);
}