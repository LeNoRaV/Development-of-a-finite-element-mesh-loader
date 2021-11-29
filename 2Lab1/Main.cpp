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


// angle is less than 30 if cos is greater than sqrt (3) / 2

void Triangle_with_angle_less_then_30(const MeshLoader& My, const std::string& filename) {
    int id;
	std::cout << "Enter border ID:" << std::endl;
	std::cin >> id;
	
	
	std::set<FiniteElement> Container = My.get_f_node_by_boundary(id);

	std::ofstream file(filename);
	if (!file.is_open()) 
		throw FileIsNotFound(filename);
	else {
	     auto good_f_elem = [&](FiniteElement f_elem) { //!!! Почему f_elem передается по значению?
            auto good_angle = [&](int node1, int node2, int node3) {
                double AB = sqrt((My.get_node()[node1].m_XYZ.at(0) - My.get_node()[node2].m_XYZ.at(0)) * (My.get_node()[node1].m_XYZ.at(0) - My.get_node()[node2].m_XYZ.at(0)) +
                    (My.get_node()[node1].m_XYZ.at(1) - My.get_node()[node2].m_XYZ.at(1)) * (My.get_node()[node1].m_XYZ.at(1) - My.get_node()[node2].m_XYZ.at(1)) +
                    (My.get_node()[node1].m_XYZ.at(2) - My.get_node()[node2].m_XYZ.at(2)) * (My.get_node()[node1].m_XYZ.at(2) - My.get_node()[node2].m_XYZ.at(2)));
                double BC = sqrt((My.get_node()[node2].m_XYZ.at(0) - My.get_node()[node3].m_XYZ.at(0)) * (My.get_node()[node2].m_XYZ.at(0) - My.get_node()[node3].m_XYZ.at(0)) +
                    (My.get_node()[node2].m_XYZ.at(1) - My.get_node()[node3].m_XYZ.at(1)) * (My.get_node()[node2].m_XYZ.at(1) - My.get_node()[node3].m_XYZ.at(1)) +
                    (My.get_node()[node2].m_XYZ.at(2) - My.get_node()[node3].m_XYZ.at(2)) * (My.get_node()[node2].m_XYZ.at(2) - My.get_node()[node3].m_XYZ.at(2)));
                double CA = sqrt((My.get_node()[node1].m_XYZ.at(0) - My.get_node()[node3].m_XYZ.at(0)) * (My.get_node()[node1].m_XYZ.at(0) - My.get_node()[node3].m_XYZ.at(0)) +
                    (My.get_node()[node1].m_XYZ.at(1) - My.get_node()[node3].m_XYZ.at(1)) * (My.get_node()[node1].m_XYZ.at(1) - My.get_node()[node3].m_XYZ.at(1)) +
                    (My.get_node()[node1].m_XYZ.at(2) - My.get_node()[node3].m_XYZ.at(2)) * (My.get_node()[node1].m_XYZ.at(2) - My.get_node()[node3].m_XYZ.at(2)));
                double max_cos = std::max(
                    std::max(
                        (AB * AB + BC * BC - CA * CA) / (2 * AB * BC),
                        (AB * AB - BC * BC + CA * CA) / (2 * AB * CA)),
                    (BC * BC + CA * CA - AB * AB) / (2 * CA * BC)
                );
                return (max_cos <= 1 && max_cos >= sqrt(3) / 2);
            };
            return good_angle(f_elem.m_node_id.at(0), f_elem.m_node_id.at(1), f_elem.m_node_id.at(2));
        };

        auto transform = [&](FiniteElement f_elem) { //!!! Почему f_elem передается по значению?
            return My.get_finite_elems()[f_elem.m_element_id].m_node_id; //!!! ЗАЧЕМ ИСКАТЬ ЭЛЕМЕНТ, ЕСЛИ СПИСОК ЕГО УЗЛОВ ВНУТРИ f_elem?
        };
        auto res = Container | std::ranges::views::filter(good_f_elem) | std::ranges::views::transform(transform);
        std::ranges::copy(res, std::ostream_iterator<std::vector<int>>(file, "\n"));
        //!!! Не нашел перегрузки << для std::vector<int>
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
    std::set<FiniteElement> f_node_by_boundary = std::move(My->get_f_node_by_boundary(1));

    My->insert_middle(2);
    Triangle_with_angle_less_then_30(*My, name);

    delete My;
}

