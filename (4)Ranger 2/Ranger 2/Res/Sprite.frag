#version 400 core

in vec2 TexCoord;
out vec4 Color;
uniform sampler2D Texture;

void main() { 
	Color = vec4(1.0) * texture(Texture, TexCoord); 
}