#include <iostream>
#include "AneuMeshLoader.h"
#include "Types.h"

int main()
{
    MeshLoader* My = new AneuMeshLoader; //!!! Утечка памяти
    std::string name;
    std::cout << "Enter file name ";
    std::cin >> name;
    My->LoadMesh(name);

    std::vector<Node> nodes = My->get_node();
    std::vector<FiniteElement> finite_elements = My->get_finite_elems();
    std::vector<BoundaryFiniteElement> boundaries = My->get_boundary();

    std::vector<int> elems_by_id = My->find_elem_id(1, 2, 3); //!!! Лишнее копирование
    std::vector<int> elems_by_edge= My->find_elem_edge(1, 2); //!!! Лишнее копирование

    std::vector<int> node_by_boundary = My->get_node_by_boundary(1);  //!!! Лишнее копирование
    std::vector<int> node_by_finite = My->get_node_by_finite(1); //!!! Лишнее копирование
    std::vector<int> f_node_by_boundary = My->get_f_node_by_boundary(1); //!!! Лишнее копирование

    My->insert_middle();
}

