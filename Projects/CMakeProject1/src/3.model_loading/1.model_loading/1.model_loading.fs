#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;

struct Material{
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
};
uniform Material material;

struct DirectionLight{
    vec3 direction;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};
uniform DirectionLight light;
uniform vec3 viewDir;

vec3 CalcDirectionLight(DirectionLight light,vec3 normal,vec3 viewDir);
void main()
{    
    vec4 diffuse = texture(material.texture_diffuse1, TexCoords);
    vec4 specular = vec4(CalcDirectionLight(light,Normal,viewDir),1.0) * vec4(texture(material.texture_specular1,TexCoords).rrr,1.0);

    FragColor = diffuse + specular;
}

vec3 CalcDirectionLight(DirectionLight light,vec3 normal,vec3 viewDir){
    //diffuse
//    normal = normalize(normal);
//    vec3 reflectDir = reflect(light.direction,normal);
//    float dotValue = dot(viewDir,reflectDir);
//    vec3 color = light.specular.rgb * dotValue;
    //specular
	vec3 reflectDir = normalize(reflect(light.direction,normal));
	float dotValue = max(dot(-viewDir,reflectDir),0.0);
	float spec = pow(dotValue,128.0*0.4);
	vec3 specular = light.specular.rgb * spec;
    return specular;
}