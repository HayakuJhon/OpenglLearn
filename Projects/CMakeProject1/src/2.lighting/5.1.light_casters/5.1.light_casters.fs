#version 330 core
out vec4 FragColor;
struct Material{
	sampler2D diffuse;
    sampler2D specular;
	sampler2D emission;
    float shininess;
};
struct DirectionLight{
	vec3 lightDir;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};
struct PointLight{
	vec3 lightPos;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float constant;
	float linear;
	float quadratic;
};
uniform Material material;
uniform PointLight pointLight;
uniform DirectionLight dirLight;
uniform vec3 viewPos;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

void main(){
	// ambient
    vec3 ambient = (pointLight.ambient.rgb + dirLight.ambient.rgb) * texture(material.diffuse, TexCoord).rgb;

	//diffuse
	vec3 diffuse = vec3(texture(material.diffuse,TexCoord));
		//point light diffuse
		float dis = length(FragPos - pointLight.lightPos);
		vec3 lightDir = normalize(pointLight.lightPos - FragPos);
		float pointDotDiffuse = max(dot(normalize(Normal),lightDir),0.0);
		pointDotDiffuse *= 1.0/(pointLight.constant + pointLight.linear * dis + pointLight.quadratic *
		pointLight.quadratic * dis);
		//direction light diffuse
		lightDir = normalize(-dirLight.lightDir);
		float dirDotDiffuse = max(dot(normalize(Normal),lightDir),0.0);
	vec3 diffuseColor = vec3(pointLight.diffuse) * (pointDotDiffuse+dirDotDiffuse) * diffuse;

	//specular
	vec3 specular = vec3(texture(material.specular,TexCoord));
	vec3 viewDir = normalize(viewPos - FragPos);
		//point light specular
		
		vec3 reflectPointDir = normalize(reflect(FragPos - pointLight.lightPos,Normal));
		float pointDotSpecular = pow(max(dot(reflectPointDir,viewDir),0.0),material.shininess);
		//direction light specular
		vec3 reflectDirDir = normalize(reflect(-dirLight.lightDir,Normal));
		float dirDotSpecular = pow(max(dot(reflectDirDir,viewDir),0.0),material.shininess);
	vec3 specularColor = (pointDotSpecular + dirDotSpecular) * vec3(pointLight.specular) * specular;

	//emission
	vec3 emission = vec3(texture(material.emission,TexCoord));

	//result
	vec3 result = diffuseColor + specularColor + emission;
	FragColor = vec4(result,1.0);
	//FragColor = vec4(Normal,1.0);
}