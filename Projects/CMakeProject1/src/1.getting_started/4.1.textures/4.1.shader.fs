#version 330 core
out vec4 FragColor;
in vec4 vertexColor;
in vec2 vertexCoord;
uniform sampler2D textureSampler;
uniform sampler2D textureSampler1;
void main(){
    FragColor = mix(texture(textureSampler,vertexCoord),texture(textureSampler1,vertexCoord),0.2);
}