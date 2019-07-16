#pragma once

#include "Mesh.h"

#include <Assimp/Importer.hpp>
#include <Assimp/scene.h>
#include <Assimp/postprocess.h>

class Model {
private:
	vector<My::Mesh> meshes;
	string dir;	
public:
	void Draw(GLuint shader) { for (GLuint i = 0; i < meshes.size(); i++) meshes[i].Draw(shader); }
	void DrawOther(GLuint shader) { for (GLuint i = 0; i < meshes.size(); i++) meshes[i].DrawOther(shader); }

	Model() {};
	Model(string const &path) { loadModel(path); }
private:
	void loadModel(string const &path) {
		Assimp::Importer importer;
		
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs); // | aiProcess_GenNormals | aiProcess_CalcTangentSpace);
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
	My::Mesh processMesh(aiMesh *mesh, const aiScene *scene) {
		vector<Vertex> vertices;
		vector<GLuint> indices;
		vector<Texture> texs;

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

		vector<Texture> diffuseMaps = loadTexs(mat, aiTextureType_DIFFUSE, "tex_diffuse"); texs.insert(texs.end(), diffuseMaps.begin(), diffuseMaps.end());
		vector<Texture> specularMaps = loadTexs(mat, aiTextureType_SPECULAR, "tex_specular"); texs.insert(texs.end(), specularMaps.begin(), specularMaps.end());
		vector<Texture> normalMaps = loadTexs(mat, aiTextureType_NORMALS, "tex_normal"); texs.insert(texs.end(), normalMaps.begin(), normalMaps.end());
		vector<Texture> heightMaps = loadTexs(mat, aiTextureType_HEIGHT, "tex_height"); texs.insert(texs.end(), heightMaps.begin(), heightMaps.end());
		vector<Texture> opacityMaps = loadTexs(mat, aiTextureType_OPACITY, "tex_opacity"); texs.insert(texs.end(), opacityMaps.begin(), opacityMaps.end());

		return My::Mesh(vertices, indices, texs);
	}
	vector<Texture> loadTexs(aiMaterial *mat, aiTextureType type, const string& typeName) {
		vector<Texture> texs;

		for (GLuint i = 0; i < mat->GetTextureCount(type); i++) {
			aiString str;

			mat->GetTexture(type, i, &str);
			texs.push_back(Texture(dir +'/'+ str.C_Str(), typeName));
		}
		
		return texs;
	}
};