#pragma once
#include <iostream>
#include "MeshLoader.h"

class AneuMeshLoader : public MeshLoader {
	~AneuMeshLoader() {};
public:
	void LoadMesh(const std::string&) override;
};