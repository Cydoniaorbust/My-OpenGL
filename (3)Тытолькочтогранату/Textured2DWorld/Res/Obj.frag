#version 400 core

out vec4 FragColor;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};
struct Light_Direct {
	vec3 direction;
	vec3 diffuse;
};
struct Light_Point {
	vec3 position;	
	vec3 diffuse;
};
struct Light_Spot {
	vec3 position;
	vec3 direction;
	vec3 diffuse;
	float inner;
	float outer;
};

#define POINT_LIGHTS 4

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 ViewPos;
uniform vec3 Ambient;
uniform float time;
uniform Material material;
uniform Light_Direct DirLight;
uniform Light_Point PointLights[POINT_LIGHTS];
uniform Light_Spot SpotLight;

vec3 CalcDirLight(Light_Direct l, vec3 normal, vec3 ViewDir) {
	vec3 LightDir = normalize(-l.direction);
    vec3 ReflectDir = reflect(-LightDir, normal);
	
    float diff = max(dot(normal, LightDir), 0.0);
    float spec = pow(max(dot(ViewDir, ReflectDir), 0.0), material.shininess);

    vec3 diffuse  = l.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = l.diffuse * spec * vec3(texture(material.specular, TexCoords));

    return (diffuse + specular);
}
vec3 CalcPointLight(Light_Point l, vec3 normal, vec3 ViewDir) {
	vec3 LightDir = normalize(l.position - FragPos);
    vec3 ReflectDir = reflect(-LightDir, normal);

	float diff = max(dot(normal, LightDir), 0.0);
    float spec = pow(max(dot(ViewDir, ReflectDir), 0.0), material.shininess);
		
	float distance = length(l.position - FragPos);
	float attenuation = 1.0 / (1.0 + 0.09 * distance + 0.032 * distance * distance);

    vec3 diffuse = l.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = l.diffuse * spec * vec3(texture(material.specular, TexCoords));

    diffuse *= attenuation;
    specular *= attenuation;

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

	vec3 diffuse = l.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = l.diffuse * spec * vec3(texture(material.specular, TexCoords));
    
	diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
	
	return (diffuse + specular);
}
vec3 CalcEmission() {
	vec3 emission;
	//if (texture(material.specular, TexCoords).r == 0.0) 
	//emission = texture(material.emission, TexCoords + vec2(0.0,time)).rgb;
	return emission;
}

void main() {
	vec3 Norm = normalize(Normal);
	vec3 ViewDir = normalize(ViewPos - FragPos);
	
	vec3 result = CalcDirLight(DirLight, Norm, ViewDir);
	for(int i = 0; i < POINT_LIGHTS; i++) 
	result += CalcPointLight(PointLights[i], Norm, ViewDir);    
	result += CalcSpotLight(SpotLight, Norm, ViewDir);    
	result += CalcEmission();

	result += Ambient * vec3(texture(material.diffuse, TexCoords));

	FragColor = vec4(result, 1.0);
}