#include <iostream>
#include "AneuMeshLoader.h"
#include "Types.h"

//!!! Задание на защиту (не удалять).
//!!! Реализовать на основе std::ranges
//!!! 1. Создать контейнер граничных КЭ с данной поверхности.
//!!! 2. С помощью потокового итератора вывести в файл списки узлов тех треугольников,
//!!! которые содержат минимальный угол от 0 до 30 градусов.



int main()
{
    MeshLoader* My = new AneuMeshLoader; //delete My below
    std::string name;
    std::cout << "Enter file name ";
    std::cin >> name;
    My->LoadMesh(name);

    std::vector<Node> nodes = std::move(My->get_node());
    std::vector<FiniteElement> finite_elements = std::move(My->get_finite_elems());
    std::vector<BoundaryFiniteElement> boundaries = std::move(My->get_boundary());

    std::vector<int> elems_by_id = std::move(My->find_elem_id(1, 2, 3));
    std::vector<int> elems_by_edge= std::move(My->find_elem_edge(1, 2)); 

    std::set<int> node_by_boundary = std::move(My->get_node_by_boundary(1)); 
    std::set<int> node_by_finite = std::move(My->get_node_by_finite(1)); 
    std::set<int> f_node_by_boundary = std::move(My->get_f_node_by_boundary(1)); 

    My->insert_middle(2);

    delete My;
}

