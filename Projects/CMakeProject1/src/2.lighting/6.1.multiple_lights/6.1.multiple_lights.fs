#version 330 core
out vec4 FragColor;
struct Material{
	sampler2D ambient;
	sampler2D diffuse;
    sampler2D specular;
	sampler2D emission;
    float shininess;
};
struct PointLight{
	vec3 position;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float constant;
	float linear;
	float quadratic;
};
struct DirectionLight{
	vec3 direction;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};
struct SpotLight{
	vec3 position;
	vec3 direction;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float cutOff;
	float outerCutOff;
};
uniform Material material;
//uniform PointLight pointLight;
#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform DirectionLight dirLight;
uniform SpotLight spotLight;
uniform vec3 viewPos;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

vec3 combineLightAndMaterial(vec3 ambient,vec3 diffuse,vec3 specular);
vec3 CalcPointLight(PointLight light,vec3 normal,vec3 fragPos,vec3 viewDir);
vec3 CalcDirectionLight(DirectionLight light,vec3 normal,vec3 viewDir);
vec3 CalcSpotLight(SpotLight light,vec3 normal,vec3 fragPos,vec3 viewDir);

void main(){
//	// ambient
//    vec3 ambient = (pointLight.ambient.rgb + dirLight.ambient.rgb + spotLight.ambient.rgb) * texture(material.diffuse, TexCoord).rgb;
//
//	//diffuse
//	vec3 diffuse = vec3(texture(material.diffuse,TexCoord));
//		//point light diffuse
//		float dis = length(FragPos - pointLight.position);
//		vec3 lightDir = normalize(pointLight.position - FragPos);
//		float pointDotDiffuse = max(dot(normalize(Normal),lightDir),0.0);
//		pointDotDiffuse *= 1.0/(pointLight.constant + pointLight.linear * dis + pointLight.quadratic *
//		pointLight.quadratic * dis);
//		//direction light diffuse
//		lightDir = normalize(-dirLight.direction);
//		float dirDotDiffuse = max(dot(normalize(Normal),lightDir),0.0);
//		//spot light diffuse
//		lightDir = normalize((FragPos - spotLight.position));	//不用取反，因为我们拿的是聚光灯射出的方向，示例用的是聚光灯射出方向的反方向
//		float spotDotDiffuse = dot(lightDir,spotLight.direction);
//		float epsilon = spotLight.cutOff - spotLight.outerCutOff;
//		float intensity = clamp((spotDotDiffuse - spotLight.outerCutOff)/epsilon,0.0,1.0);
////		vec3 spotColor = vec3(spotLight.lightColor) * intensity;
//	vec3 diffuseColor = vec3(pointLight.diffuse) * (pointDotDiffuse + dirDotDiffuse + intensity) * diffuse;
//
//	//specular
//	vec3 specular = vec3(texture(material.specular,TexCoord));
//	vec3 viewDir = normalize(viewPos - FragPos);
//		//point light specular
//		
//		vec3 reflectPointDir = normalize(reflect(FragPos - pointLight.position,Normal));
//		float pointDotSpecular = pow(max(dot(reflectPointDir,viewDir),0.0),material.shininess);
//		//direction light specular
//		vec3 reflectDirDir = normalize(reflect(-dirLight.direction,Normal));
//		float dirDotSpecular = pow(max(dot(reflectDirDir,viewDir),0.0),material.shininess);
//	vec3 specularColor = (pointDotSpecular + dirDotSpecular + intensity) * vec3(pointLight.specular) * specular;
//
//	//emission
//	vec3 emission = vec3(texture(material.emission,TexCoord));
//
//	//result
//	vec3 result = diffuseColor + specularColor + emission;
	vec3 normal = normalize(Normal);
	vec3 viewDir = normalize(FragPos - viewPos);
	vec3 pointColor = vec3(0.0f);
	for(int i;i < NR_POINT_LIGHTS;i++){
		pointColor += CalcPointLight(pointLights[i],normal,FragPos,viewDir);
	}
//	vec3 pointColor = CalcPointLight(pointLight,normal,FragPos,viewDir);
	vec3 directionColor = CalcDirectionLight(dirLight,normal,viewDir);
	vec3 spotColor = CalcSpotLight(spotLight,normal,FragPos,viewDir);
	vec3 result = pointColor + directionColor + spotColor;
	FragColor = vec4(result,1.0);
	//FragColor = vec4(Normal,1.0);
}

vec3 CalcPointLight(PointLight light,vec3 normal,vec3 fragPos,vec3 viewDir){
	vec3 result;
	//ambient
	vec3 ambient = light.ambient.rgb;
	//diffuse
	vec3 lightDir = normalize(light.position - fragPos);
	float dotValue = max(dot(normal,lightDir),0.0);
	vec3 diffuse = light.diffuse.rgb * dotValue;
	//specular
	vec3 reflectDir = normalize(reflect(-lightDir,normal));
	dotValue = max(dot(reflectDir,-viewDir),0.0);
	float spec = pow(dotValue,material.shininess);
	vec3 specular = light.specular.rgb * spec;

	//attenuation
	float dis = length(light.position - fragPos);
	float attenuation = 1.0/(light.constant + light.linear * dis + light.quadratic * dis * dis);

	//result
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= 1.0;
	result = combineLightAndMaterial(ambient,diffuse,specular);

	return result;
}

vec3 CalcDirectionLight(DirectionLight light,vec3 normal,vec3 viewDir){
	vec3 result;
	//ambient
	vec3 ambient = light.ambient.rgb;
	//diffuse
	float dotValue = max(dot(normal,-light.direction),0.0);
	vec3 diffuse = light.diffuse.rgb * dotValue;
	//specular
	vec3 reflectDir = normalize(reflect(light.direction,normal));
	dotValue = max(dot(-viewDir,reflectDir),0.0);
	float spec = pow(dotValue,material.shininess);
	vec3 specular = light.specular.rgb * spec;

	//result
	result = combineLightAndMaterial(ambient,diffuse,specular);
	return result;
}

vec3 CalcSpotLight(SpotLight light,vec3 normal,vec3 fragPos,vec3 viewDir){
	vec3 result;
	//ambient
	vec3 ambient = light.ambient.rgb;
	//diffuse
	vec3 lightDir = normalize(fragPos - light.position);
	float dotValue = max(dot(normal,-lightDir),0.0);
	vec3 diffuse = light.diffuse.rgb * dotValue;
	//specular
	vec3 reflectDir = normalize(reflect(lightDir,normal));
	dotValue = pow(max(dot(reflectDir,-viewDir),0.0),material.shininess);
	vec3 specular = light.specular.rgb * dotValue;

	//spotlight intensity
	dotValue = dot(normalize(light.direction),lightDir);
	float intensity = clamp((dotValue-light.outerCutOff)/(light.cutOff - light.outerCutOff),0.0,1.0);

	//result
	ambient *= intensity;
	diffuse *= intensity;
	specular *= intensity;
	result = combineLightAndMaterial(ambient,diffuse,specular);

	return result;
}

vec3 combineLightAndMaterial(vec3 ambient,vec3 diffuse,vec3 specular){
	return  ambient * vec3(texture(material.ambient,TexCoord)) + 
			diffuse * vec3(texture(material.diffuse,TexCoord)) + 
			specular * vec3(texture(material.specular,TexCoord));
}