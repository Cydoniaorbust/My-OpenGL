#version 400 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texcoords;
out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main() {
	FragPos = vec3(model * vec4(pos, 1.0f));
	Normal = mat3(transpose(inverse(model))) * normal;
	TexCoords = texcoords;
	gl_Position = projection * view * vec4(FragPos, 1.0f);
}