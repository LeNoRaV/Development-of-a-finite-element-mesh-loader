#include "AneuMeshLoader.h"
#include "Exceptions.h"
#include <iostream>
#include <fstream>

void AneuMeshLoader::LoadMesh(const std::string& filename)
{
	std::ifstream file(filename);

	if (!file) {
		throw FileIsNotFound(filename);
	}

    //!!! Где чтение файла??
}