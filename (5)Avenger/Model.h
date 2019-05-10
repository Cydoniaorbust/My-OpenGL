#pragma once

#include "Mesh.h"

#include <Assimp/Importer.hpp>
#include <Assimp/scene.h>
#include <Assimp/postprocess.h>

class model {
public:
	vector<Texture> textures_loaded;
	vector<My::mesh> meshes;
	string dir;

	float Step_Move;
	float Step_Rotate;
	mat4 position;

	model() : dir(""), Step_Move(1.0f), Step_Rotate(1.0f) {};
	model(string const &path) : model() {
		loadModel(path);
	}

	void Draw(GLuint shader) { 
		for (GLuint i = 0; i < meshes.size(); i++) meshes[i].Draw(shader); 
	}
	void DrawOther(GLuint shader) {
		for (GLuint i = 0; i < meshes.size(); i++) meshes[i].DrawOther(shader);
	}
	
	void MoveX(float delta) {
		position = translate(position, vec3(delta * Step_Move, 0, 0));
	}
	void MoveY(float delta) {
		position = translate(position, vec3(0, delta * Step_Move, 0));
	}
	void MoveZ(float delta) {
		position = translate(position, vec3(0, 0, delta * Step_Move));
	}
	
	void ScaleAll(float delta) {
		position = scale(position, vec3(delta));
		Step_Move = 5 / delta;
		Step_Rotate = 100;
	}

	void RotateX(float degrees) { 
		position = rotate(position, radians(degrees * Step_Rotate), vec3(1, 0, 0));
	}
	void RotateY(float degrees) {
		position = rotate(position, radians(degrees * Step_Rotate), vec3(0, 1, 0));
	}
	void RotateZ(float degrees) {
		position = rotate(position, radians(degrees * Step_Rotate), vec3(0, 0, 1));
	}

private:
	void loadModel(string const &path) {
		Assimp::Importer importer;
		
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs); //  | aiProcess_GenNormals| aiProcess_CalcTangentSpace );
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
			return;
		}
		dir = path.substr(0, path.find_last_of('/'));
		AI_MATKEY_TEXFLAGS(aiTextureFlags::aiTextureFlags_UseAlpha, 1);
		processNode(scene->mRootNode, scene);
	}
	void processNode(aiNode *node, const aiScene *scene) {
		for (GLuint i = 0; i < node->mNumMeshes; i++) {
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(processMesh(mesh, scene));
		}
		for (GLuint i = 0; i < node->mNumChildren; i++) processNode(node->mChildren[i], scene);
	}
	My::mesh processMesh(aiMesh *mesh, const aiScene *scene) {
		vector<Vertex> vertices;
		vector<GLuint> indices;
		vector<Texture> textures;

		for (GLuint i = 0; i < mesh->mNumVertices; i++) {
			Vertex vertex;
			vec3 vector; 
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.Position = vector;
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.Normal = vector;
			if (mesh->mTextureCoords[0]) {
				vec2 vec;
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.TexCoords = vec;
			}
			else vertex.TexCoords = vec2(0.0f, 0.0f);
			//vector.x = mesh->mTangents[i].x;
			//vector.y = mesh->mTangents[i].y;
			//vector.z = mesh->mTangents[i].z;
			//vertex.Tangent = vector;
			//vector.x = mesh->mBitangents[i].x;
			//vector.y = mesh->mBitangents[i].y;
			//vector.z = mesh->mBitangents[i].z;
			//vertex.Bitangent = vector;
			vertices.push_back(vertex);
		}
		for (GLuint i = 0; i < mesh->mNumFaces; i++) {
			aiFace face = mesh->mFaces[i];
			for (GLuint j = 0; j < face.mNumIndices; j++) indices.push_back(face.mIndices[j]);
		}
		
		aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
		vector<Texture> diffuseMaps = loadMaterialTextures(mat, aiTextureType_DIFFUSE, "texture_diffuse"); textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		vector<Texture> specularMaps = loadMaterialTextures(mat, aiTextureType_SPECULAR, "texture_specular"); textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		vector<Texture> normalMaps = loadMaterialTextures(mat, aiTextureType_NORMALS, "texture_normal"); textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
		vector<Texture> heightMaps = loadMaterialTextures(mat, aiTextureType_HEIGHT, "texture_height"); textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
		vector<Texture> opacityMaps = loadMaterialTextures(mat, aiTextureType_OPACITY, "texture_opacity"); textures.insert(textures.end(), opacityMaps.begin(), opacityMaps.end());

		return My::mesh(vertices, indices, textures);
	}
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName) {
		vector<Texture> textures;
		for (GLuint i = 0; i < mat->GetTextureCount(type); i++) {
			aiString str;
			mat->GetTexture(type, i, &str);
			bool skip = false;
			for (GLuint j = 0; j < textures_loaded.size(); j++)
				if (strcmp(textures_loaded[j].Path.C_Str(), str.C_Str()) == 0) {
					textures.push_back(textures_loaded[j]);
					skip = true;
					break;
				}
			if (!skip) {
				Texture texture(dir, typeName, str);
				textures.push_back(texture);
				textures_loaded.push_back(texture);
			}
		}
		return textures;
	}
};