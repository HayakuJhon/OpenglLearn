#version 330 core
out vec4 FragColor;
uniform vec3 ambientColor;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightPos;

in vec3 Normal;
in vec3 FragPos;

void main(){
	vec3 lightDir = normalize(lightPos - FragPos);
	float dotValue = max(dot(normalize(Normal),lightDir),0.0);
	vec3 diffuseColor = lightColor * dotValue;
	vec3 result = (ambientColor + diffuseColor) * objectColor;
	FragColor = vec4((diffuseColor + ambientColor) * objectColor,1.0);
	//FragColor = vec4(Normal,1.0);
}