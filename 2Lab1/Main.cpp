#include <iostream>
#include <ranges>
#include <fstream>
#include <algorithm>
#include "AneuMeshLoader.h"
#include "Types.h"
#include "Exceptions.h"

//!!! Задание на защиту (не удалять).
//!!! Реализовать на основе std::ranges
//!!! 1. Создать контейнер граничных КЭ с данной поверхности.
//!!! 2. С помощью потокового итератора вывести в файл списки узлов тех треугольников,
//!!! которые содержат минимальный угол от 0 до 30 градусов.



// using cosine theorem
// sides of a triangle

struct triangle
{
    double AB;
    double BC;
    double CA;

    triangle(const Node& node1, const Node& node2, const Node& node3)
    {
        AB = sqrt((node1.m_XYZ.at(0) - node2.m_XYZ.at(0)) * (node1.m_XYZ.at(0) - node2.m_XYZ.at(0)) +
            (node1.m_XYZ.at(1) - node2.m_XYZ.at(1)) * (node1.m_XYZ.at(1) - node2.m_XYZ.at(1)) +
            (node1.m_XYZ.at(2) - node2.m_XYZ.at(2)) * (node1.m_XYZ.at(2) - node2.m_XYZ.at(2)));
        BC = sqrt((node2.m_XYZ.at(0) - node3.m_XYZ.at(0)) * (node2.m_XYZ.at(0) - node3.m_XYZ.at(0)) +
            (node2.m_XYZ.at(1) - node3.m_XYZ.at(1)) * (node2.m_XYZ.at(1) - node3.m_XYZ.at(1)) +
            (node2.m_XYZ.at(2) - node3.m_XYZ.at(2)) * (node2.m_XYZ.at(2) - node3.m_XYZ.at(2)));
        CA = sqrt((node1.m_XYZ.at(0) - node3.m_XYZ.at(0)) * (node1.m_XYZ.at(0) - node3.m_XYZ.at(0)) +
            (node1.m_XYZ.at(1) - node3.m_XYZ.at(1)) * (node1.m_XYZ.at(1) - node3.m_XYZ.at(1)) +
            (node1.m_XYZ.at(2) - node3.m_XYZ.at(2)) * (node1.m_XYZ.at(2) - node3.m_XYZ.at(2)));
    }

    ~triangle() = default;
};

// angle is less than 30 if cos is greater than sqrt (3) / 2

void Function(MeshLoader& My, std::string filename) {
	int id;
	std::cout << "Enter border ID:" << std::endl;
	std::cin >> id;
	std::set<int> Container = My.get_f_node_by_boundary(id);

	std::ofstream file(filename);
	if (!file.is_open()) 
		throw FileIsNotFound(filename);
	else {
        auto good_nodes = [&](const int& f_node_from_container) {
            auto nodes = My[f_node_from_container].m_node_id;
            auto good_angle = [&](int& node1, int& node2, int& node3) {
                triangle tri(My.get_node().at(node1), My.get_node().at(node2), My.get_node().at(node3));
                double max_cos = std::max(
                    std::max(
                        (tri.AB * tri.AB + tri.BC * tri.BC - tri.CA * tri.CA) / (2 * tri.AB * tri.BC),
                        (tri.AB * tri.AB - tri.BC * tri.BC + tri.CA * tri.CA) / (2 * tri.AB * tri.CA)),
                    (tri.BC * tri.BC + tri.CA * tri.CA - tri.AB * tri.AB) / (2 * tri.CA * tri.BC)
                );
                return (max_cos <= 1 && max_cos >= sqrt(3) / 2);
            };
            return good_angle(nodes.at(0), nodes.at(1), nodes.at(2));
        };

        auto transform = [&](const int& f_node_from_container) {
            return My[f_node_from_container].m_node_id;
        };
        auto res = Container | std::ranges::views::filter(good_nodes) | std::ranges::views::transform(transform);
        std::ranges::copy(res, std::ostream_iterator<std::vector<int>>(file, "\n"));
	}
}


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
	Function(*My, name);

    delete My;
}

