#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMat;

out vec3 Normal;
out vec3 FragPos;

uniform vec3 ambientColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform float Shininess;	//反光度，越大光点越小

out vec3 resultColor;

void main(){
	gl_Position = projection * view * model * vec4(aPos,1.0);
	Normal = normalMat * aNormal;
	//Normal = mat3(transpose(inverse(model))) * aNormal; 
	
	//ambient
	vec3 ambient = ambientColor;

	//diffuse
	vec3 lightDir = normalize(lightPos - aPos);
	float diffuseDot = max(0.0,dot(lightDir,Normal));
	vec3 diffuseColor = lightColor * diffuseDot;

	//specular
	float specularStrength = 0.5;	//光照强度
	vec3 viewDir = normalize(viewPos - aPos);
	float specularDot = max(0.0,dot(viewDir,reflect(-lightDir,Normal)));
	specularDot = pow(specularDot,Shininess);
	vec3 specularColor = lightColor * specularStrength * specularDot;

	resultColor = ambient + diffuseColor + specularColor;

	FragPos = vec3(model * vec4(aPos,1.0));
}