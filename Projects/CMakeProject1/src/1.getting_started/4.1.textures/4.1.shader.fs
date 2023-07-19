#version 330 core
out vec4 FragColor;
in vec4 vertexColor;
in vec2 vertexCoord;
uniform sampler2D textureSampler;
uniform sampler2D textureSampler1;

uniform float mixRate;

vec2 tempVec2;
void main(){
    tempVec2 = vec2(1.0-vertexCoord.x,vertexCoord.y);
    FragColor = mix(texture(textureSampler,vertexCoord),texture(textureSampler1,tempVec2),mixRate);
}