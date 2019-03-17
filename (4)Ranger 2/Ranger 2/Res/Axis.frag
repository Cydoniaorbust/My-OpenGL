#version 400 core


out vec4 Color;
uniform vec3 _color;

void main() { 
	Color = vec4(_color, 1.0); 
}