#pragma once

#ifndef _MODEL_H_
#define _MODEL_H_

#include <iostream>
#include <vector>
#include <map>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "stb_image.h"

#include "Mesh.h"

class Model
{
public:
	bool gammaCorrection;
	Model(const char * path, bool gamma = false);
	~Model();

	void draw(Shader &shader);

private:
	std::vector<Mesh> meshes;
	std::string directory;
	std::vector<Texture> texture_loaded;


	void loadModel(std::string path);
	void processNode(aiNode * node, const aiScene * scene);
	Mesh processMesh(aiMesh * mesh, const aiScene * scene);

	unsigned int TextureFromFile(std::string fileName, std::string directory);

	std::vector<Texture> loadMaterialTextures(aiMaterial * material, aiTextureType type, std::string typeName);
};

#endif
