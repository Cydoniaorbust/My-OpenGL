#version 400 core

out vec4 FragColor;

struct Material {
	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
	float shininess;
};
struct Light_Direct {
	vec3 direction;
	vec3 diffuse;
};
struct Light_Spot {
	vec3 position;
	vec3 direction;
	vec3 diffuse;
	float inner;
	float outer;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 ViewPos;
uniform vec3 Ambient;
uniform Material material;
uniform Light_Direct DirLight;
uniform Light_Spot SpotLight;

vec3 CalcDirLight(Light_Direct l, vec3 normal, vec3 ViewDir) {
	vec3 LightDir = normalize(-l.direction);
	vec3 ReflectDir = reflect(-LightDir, normal);
	
	float diff = max(dot(normal, LightDir), 0.0);
	float spec = pow(max(dot(ViewDir, ReflectDir), 0.0), material.shininess);

	vec3 diffuse  = l.diffuse * diff * vec3(texture(material.texture_diffuse1, TexCoords));
	vec3 specular = l.diffuse * spec * vec3(texture(material.texture_specular1, TexCoords));

	return (diffuse + specular);
}
vec3 CalcSpotLight(Light_Spot l, vec3 normal, vec3 ViewDir) {
	vec3 LightDir = normalize(l.position - FragPos);
	vec3 ReflectDir = reflect(-LightDir, normal);

	float diff = max(dot(normal, LightDir), 0.0);
	float spec = pow(max(dot(ViewDir, ReflectDir), 0.0), material.shininess);

	float distance = length(l.position - FragPos);
	float attenuation = 1.0 / (1.0 + 0.09 * distance + 0.032 * distance * distance);

	float theta = dot(LightDir, normalize(-l.direction)); 
	float epsilon = l.inner - l.outer;
	float intensity = clamp((theta - l.outer) / epsilon, 0.0, 1.0);

	vec3 diffuse = l.diffuse * diff * vec3(texture(material.texture_diffuse1, TexCoords));
	vec3 specular = l.diffuse * spec * vec3(texture(material.texture_specular1, TexCoords));
    
	diffuse *= attenuation * intensity;
	specular *= attenuation * intensity;
	
	return (diffuse + specular);
}

void main() {
	vec3 Norm = normalize(Normal);
	vec3 ViewDir = normalize(ViewPos - FragPos);
	
	vec3 result = CalcDirLight(DirLight, Norm, ViewDir);
	result += CalcSpotLight(SpotLight, Norm, ViewDir);

	result += Ambient * vec3(texture(material.texture_diffuse1, TexCoords));

	FragColor = vec4(result, 1.0);
}