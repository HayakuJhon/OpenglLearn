#version 330 core
out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D texture1;

float near = 0.1; 
float far  = 100.0; 

float LinearizeDepth(float depth){
	float z = depth * 2.0 - 1.0;
	return (2.0 * near * far) / (far + near - z * (far - near));
}

void main(){
	FragColor = texture(texture1,TexCoord);
//	float depth = LinearizeDepth(gl_FragCoord.z) / far; // Ϊ����ʾ���� far
//    FragColor = vec4(vec3(depth), 1.0);
}