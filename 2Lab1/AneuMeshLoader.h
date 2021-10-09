#pragma once
#include <iostream>
#include "MeshLoader.h"

class AneuMeshLoader : public MeshLoader {
	~AneuMeshLoader() {}; //!!! Зачем нужен явный деструктор?
public:
	void LoadMesh(const std::string&) override;
};