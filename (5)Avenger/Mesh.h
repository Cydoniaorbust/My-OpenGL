#pragma once

#include <Assimp/Importer.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

namespace My {
	class Mesh {
	public:
		GLuint VAO, VBO, EBO;
		vector<Vertex> Vertices;
		vector<GLuint> Indices;
		vector<Texture> Textures;

		Mesh(vector<Vertex> ver, vector<GLuint> ind, vector<Texture> tex) : Vertices(ver), Indices(ind), Textures(tex) {
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);

			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), &Vertices[0], GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(GLuint), &Indices[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(0); glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
			glEnableVertexAttribArray(1); glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
			glEnableVertexAttribArray(2); glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
			glEnableVertexAttribArray(3); glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
			glEnableVertexAttribArray(4); glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent)); //-V112

			glBindVertexArray(0);
		}

		void Draw(GLuint shader) {
			GLuint diffuseNr = 1;
			GLuint specularNr = 1;

			for (GLuint i = 0; i < Textures.size(); i++) {
				glActiveTexture(GL_TEXTURE0 + i);
				string name = Textures[i].Type;
				string number = (name == "texture_diffuse") ? to_string(diffuseNr++) : to_string(specularNr++);
				Shader::SetInt(shader, "material." + name + number, i);
				Textures[i].Bind();
			}

			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			glActiveTexture(GL_TEXTURE0);
		}
		void DrawOther(GLuint shader) {
			glActiveTexture(GL_TEXTURE0 + 2);
			Shader::SetInt(shader, "Texture", 2);
			Textures[0].Bind();

			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			glActiveTexture(GL_TEXTURE0);
		}
	};
}