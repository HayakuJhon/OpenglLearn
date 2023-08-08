#version 330 core
out vec4 FragColor;
uniform vec3 ambientColor;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform float Shininess;	//反光度，越大光点越小

in vec3 Normal;
in vec3 FragPos;

void main(){
	//diffuse
	vec3 lightDir = normalize(lightPos - FragPos);
	float dotValue = max(dot(normalize(Normal),lightDir),0.0);
	vec3 diffuseColor = lightColor * dotValue;

	//specular
	float specularStrength = 0.5;	//光照强度
	vec3 reflectDir = normalize(reflect(-lightDir,Normal));
	vec3 viewDir = normalize(viewPos - FragPos);
	float dotSpecular = pow(max(dot(reflectDir,viewDir),0.0),Shininess);
	vec3 specularColor = specularStrength * dotSpecular * lightColor;

	//result
	vec3 result = (ambientColor + diffuseColor + specularColor) * objectColor;
	FragColor = vec4(result,1.0);
	//FragColor = vec4(Normal,1.0);
}