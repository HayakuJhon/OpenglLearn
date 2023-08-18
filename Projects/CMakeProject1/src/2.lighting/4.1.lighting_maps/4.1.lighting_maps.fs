#version 330 core
out vec4 FragColor;
struct Material{
	sampler2D diffuse;
    sampler2D specular;
	sampler2D emission;
    float shininess;
};
struct Light{
	vec3 lightPos;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec3 lightDir;
};
uniform Material material;
uniform Light light;
uniform vec3 viewPos;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

void main(){
	// ambient
    vec3 ambient = light.ambient.rgb * texture(material.diffuse, TexCoord).rgb;

	//diffuse
	vec3 diffuse = vec3(texture(material.diffuse,TexCoord));
	vec3 lightDir = normalize(-light.lightDir);//normalize(light.lightPos - FragPos);
	float dotValue = max(dot(normalize(Normal),lightDir),0.0);
	vec3 diffuseColor = vec3(light.diffuse) * dotValue * diffuse;

	//specular
	vec3 specular = vec3(texture(material.specular,TexCoord));
	vec3 reflectDir = normalize(reflect(-lightDir,Normal));
	vec3 viewDir = normalize(viewPos - FragPos);
	float dotSpecular = pow(max(dot(reflectDir,viewDir),0.0),material.shininess);
	vec3 specularColor = dotSpecular * vec3(light.specular) * specular;

	//emission
	vec3 emission = vec3(texture(material.emission,TexCoord));

	//result
	vec3 result = diffuseColor + specularColor + emission;
	FragColor = vec4(result,1.0);
	//FragColor = vec4(Normal,1.0);
}