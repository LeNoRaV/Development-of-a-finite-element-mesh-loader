#include <iostream>
#include "AneuMeshLoader.h"
#include "Types.h"

int main()
{
    /*MeshLoader* My = new AneuMeshLoader;
    std::string name;
    std::cout << "Enter file name ";
    std::cin >> name;
    My->LoadMesh(name);*/

    MeshLoader* My = new AneuMeshLoader;
    My->LoadMesh("1.neu");

    /*std::cout << "Nodes:" << std::endl;
    std::cout << My->get_node() << std::endl;

    std::cout << "Finite Elems:" << std::endl;
    std::cout << My->get_finite_elems() << std::endl;
    
    std::cout << "Boundaries:" << std::endl;
    std::cout << My->get_boundary() << std::endl;*/


}

