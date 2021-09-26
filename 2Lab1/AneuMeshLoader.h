#pragma once
#include <iostream>
#include "MeshLoader"

class AneuMeshLoader : public MeshLoader {
public:
	void LoadMesh(const std::string&) override;
};