#ifndef MODEL_H
#define MODEL_H

#include <glm/glm.hpp>
#include <iostream>
#include <learnopengl/mesh.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <learnopengl/material.h>

unsigned int TextureFromFile(const char* path, const string& directory);

class Model
{
public:
	vector<Texture> textures_loaded;
	Model(const char* path) {
		loadModel(path);
	}
	void Draw(Shader shader);
private:
	vector<Mesh> meshes;
	string directory;
	void loadModel(string const& path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};
void Model::Draw(Shader shader) {
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw(shader);
	}
}
void Model::loadModel(string const&  path) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "加载模型出错:" << importer.GetErrorString() << std::endl;
		return;
	}
	directory = path.substr(0, path.find_last_of("/"));
	processNode(scene->mRootNode, scene);
}
void Model::processNode(aiNode* node,const aiScene* scene) {
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}
Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
	//vertices
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		
		Vertex vertex;
		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;
		//vertices[i].Position.x = mesh->mVertices[i].x;
		//vertices[i].Position.y = mesh->mVertices[i].y;
		//vertices[i].Position.z = mesh->mVertices[i].z;

		if (mesh->HasNormals()) {
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.Normal = vector;
			//vertices[i].Normal.x = mesh->mNormals[i].x;
			//vertices[i].Normal.y = mesh->mNormals[i].y;
			//vertices[i].Normal.z = mesh->mNormals[i].z;
		}

		if (mesh->mTextureCoords[0]) {
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
			//vertices[i].TexCoords.x = mesh->mTextureCoords[0][i].x;
			//vertices[i].TexCoords.y = mesh->mTextureCoords[0][i].y;
		}
		else {
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}
		vertices.push_back(vertex);
	}

	//indices
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; j++)
		{
			unsigned int index = mesh->mFaces[i].mIndices[j];
			indices.push_back(index);
		}
	}

	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

	vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

	vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

	return Mesh(vertices,indices,textures);
}

vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName) {
	vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		Texture texture;
		mat->GetTexture(type, i, &str);
		bool isSkip = false;
		for (unsigned int j = 0; j < textures_loaded.size(); j++)
		{
			if (std::strcmp(str.C_Str(), textures_loaded[i].path.c_str()) == 0) {
				textures.push_back(textures_loaded[i]);
				isSkip = true;
				break;
			}
		}

		if (!isSkip) {
			texture.id = TextureFromFile(str.C_Str(), directory);
			texture.path = str.C_Str();
			texture.type = typeName;
			textures.push_back(texture);
			textures_loaded.push_back(texture);
		}
		
	}
	return textures;
}

unsigned int TextureFromFile(const char* path, const string& directory) {
	string fileName = string(path);
	fileName = directory + '/' + fileName;
	unsigned int textureID;
	glGenTextures(1, &textureID);
	int width, height, channel;
	unsigned char* data = stbi_load(fileName.c_str(), &width, &height, &channel, 0);
	if (data) {
		GLenum format;
		if (channel == 1) {
			format = GL_RED;
		}
		else if (channel == 3) {
			format = GL_RGB;
		}
		else if (channel == 4) {
			format = GL_RGBA;
		}
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else {
		std::cout << "fail to load texture,path:" << path << std::endl;
		stbi_image_free(data);
	}
	return textureID;
}
#endif // !MODEL_H
