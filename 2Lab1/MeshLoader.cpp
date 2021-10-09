#include "MeshLoader.h"
#include <algorithm>
#include <vector>

const std::vector<Node>& MeshLoader::get_node() const
{
	return m_nodes;
}

const std::vector<FiniteElement>& MeshLoader::get_finite_elems() const
{
	return m_finite_elems;
}

const std::vector<BoundaryFiniteElement>& MeshLoader::get_boundary() const
{
	return m_boundary;
}

std::vector<int> MeshLoader::find_elem_id(int p_node_id_1, int p_node_id_2, int p_node_id_3) const
{
	std::vector<int> res;

	auto first_to_find = m_finite_elems.begin();
	auto last_to_find = m_finite_elems.end();
	//InputIterator find_if (InputIterator first, InputIterator last, UnaryPredicate pred);
	while (first_to_find != last_to_find) {
		auto found_elem = std::find_if(first_to_find, last_to_find,
			[p_node_id_1, p_node_id_2, p_node_id_3](const FiniteElement& elem) {
				return std::find(elem.m_node_id.begin(), elem.m_node_id.end(), p_node_id_1) != elem.m_node_id.end()
					&& std::find(elem.m_node_id.begin(), elem.m_node_id.end(), p_node_id_2) != elem.m_node_id.end()
					&& std::find(elem.m_node_id.begin(), elem.m_node_id.end(), p_node_id_3) != elem.m_node_id.end();
			});


        //!!! Ниже что-то сложное - упростите
		first_to_find = found_elem;
		if (found_elem != last_to_find) {
			res.push_back(found_elem->m_element_id);
			++first_to_find;
		}
	}
	return res;
}

std::vector<int> MeshLoader::find_elem_edge(int p_node_id_1, int p_node_id_2) const
{
	std::vector<int> res;

	auto first_to_find = m_finite_elems.begin();
	auto last_to_find = m_finite_elems.end();

	while (first_to_find != last_to_find) {
		auto found_elem = std::find_if(first_to_find, last_to_find,
			[p_node_id_1, p_node_id_2](const FiniteElement& elem) {
				return std::find(elem.m_node_id.begin(), elem.m_node_id.end(), p_node_id_1) != elem.m_node_id.end()
					&& std::find(elem.m_node_id.begin(), elem.m_node_id.end(), p_node_id_2) != elem.m_node_id.end();
			});

        //!!! Ниже что-то сложное - упростите
		first_to_find = found_elem;
		if (found_elem != last_to_find) {
			res.push_back(found_elem->m_element_id);
			++first_to_find;
		}
	}

	return res;
}

std::vector<int> MeshLoader::get_node_by_boundary(int p_boundary_id) const
{
	std::vector<int> res;

	auto first_to_find = m_boundary.begin();
	auto last_to_find = m_boundary.end();

	while (first_to_find != last_to_find) {
		auto found_boundary = std::find_if(first_to_find, last_to_find,
			[p_boundary_id](const BoundaryFiniteElement& cur_boundary) {
				return cur_boundary.m_boundary_id == p_boundary_id;
			});

        //!!! Ниже что-то сложное - упростите
		first_to_find = found_boundary;
		if (found_boundary != last_to_find) {
			for (const auto& node_in_boundary : found_boundary->m_node_id)
				res.push_back(node_in_boundary);                //!!! Где гарантия, что ID не будут дублироваться в res? Тип контейнера выбран неверно.
			++first_to_find;
		}
	}
	return res;
}

std::vector<int> MeshLoader::get_node_by_finite(int p_material_id) const
{
	std::vector<int> res;

	auto first_to_find = m_finite_elems.begin();
	auto last_to_find = m_finite_elems.end();

	while (first_to_find != last_to_find) {
		auto found_finite_elem = std::find_if(first_to_find, last_to_find,
			[p_material_id](const FiniteElement& cur_finite) {
				return cur_finite.m_material_id == p_material_id;
			});

        //!!! Ниже что-то сложное - упростите
		first_to_find = found_finite_elem;
		if (found_finite_elem != last_to_find) {
			for (const auto& node_in_finite_elem : found_finite_elem->m_node_id)
				res.push_back(node_in_finite_elem);     //!!! Где гарантия, что ID не будут дублироваться в res? Тип контейнера выбран неверно.
			++first_to_find;
		}
	}
	return res;
}


std::vector<int> MeshLoader::get_f_node_by_boundary(int p_boundary_id) const
{
	std::vector<int> res;

	auto first_to_find = m_boundary.begin();
	auto last_to_find = m_boundary.end();

	while (first_to_find != last_to_find) {
		auto found_boundary = std::find_if(first_to_find, last_to_find,
			[p_boundary_id](const BoundaryFiniteElement& cur_boundary) {
				return cur_boundary.m_boundary_id == p_boundary_id;
			});

		first_to_find = found_boundary;
		if (found_boundary != last_to_find) {
			for (const auto& node_in_boundary : found_boundary->m_node_id) {
				if (m_nodes.at(node_in_boundary).m_flag == 0)
					res.push_back(node_in_boundary);      //!!! Где гарантия, что ID не будут дублироваться в res? Тип контейнера выбран неверно.
			}
			++first_to_find;
		}
	}
	return res;
}

void MeshLoader::insert_middle() 
{
    //!!! Что не понятное тут проиходит...
    
	for (auto& elem : m_finite_elems) {
		std::vector<int> cur_nodes_id = elem.m_node_id;
		for (auto first_node = 0; first_node < 4; ++first_node)
			for (auto second_node = first_node + 1; second_node < 4; ++second_node) {
			    
				Edge cur_edge(cur_nodes_id[first_node], cur_nodes_id[second_node]);
				
				if (cur_edge.m_middle_node==-1) { //!!! Не очень понятно, у только что созданного ребра может быть не -1 ?
					Node new_node = get_middle_node(cur_edge);
					cur_edge.update_mid(new_node.m_node_id); //!!! И какой смысл? В конце итерации cur_edge удаляется.
					m_nodes.push_back(new_node);
				}
				else {
					elem.m_node_id.push_back(cur_edge.m_middle_node); //!!! А кто инициализировал m_middle_node и когда?
				}
			}
	}

	for (auto& elem : m_boundary) {
		std::vector<int> cur_nodes_id = elem.m_node_id;
		for (auto first_node = 0; first_node < 3; ++first_node)
			for (auto second_node = first_node + 1; second_node < 3; ++second_node) {
				Edge cur_edge(cur_nodes_id[first_node], cur_nodes_id[second_node]);
				if (cur_edge.m_middle_node == -1) {
					Node new_node = get_middle_node(cur_edge);
					cur_edge.update_mid(new_node.m_node_id);
					m_nodes.push_back(new_node);
				}
				else {
					elem.m_node_id.push_back(cur_edge.m_middle_node);
				}
			}
	}
}

std::vector<std::vector<int>> MeshLoader::get_adjacent_nodes() const
{
	std::vector<std::vector<int>> res(m_nodes.size() + 1);

	for (const auto& cur_elem : m_finite_elems) {
		for (auto cur_node_id : cur_elem.m_node_id)
			for (auto adj_node_id : cur_elem.m_node_id)
				if (cur_node_id != adj_node_id)
					res[cur_node_id].push_back(adj_node_id); //!!! Где гарантия, что ID не дублируются? Контейнер выбран неверно.
	}

	return res;
}

std::ostream& operator << (std::ostream& p_out, const std::vector<Node>& node)
{
	for (const auto& i : node) p_out << i;
	return p_out;
}
std::ostream& operator << (std::ostream& p_out, const std::vector<FiniteElement>& f_el)
{
	for (const auto& i : f_el) p_out << i;
	return p_out;
}
std::ostream& operator << (std::ostream& p_out, const std::vector<BoundaryFiniteElement>& bound)
{
	for (const auto& i : bound) p_out << i;
	return p_out;
}

Node& MeshLoader::get_node_by_id(int p_id)
{
	return m_nodes.at(p_id);
}

std::array<double, 3> MeshLoader::get_middle_of_edge(const Edge& p_edge)
{
	std::array<double, 3> arr;
	arr.at(0) = ((m_nodes.at(p_edge.m_nodes.first-1).m_XYZ.at(0)) + (m_nodes.at(p_edge.m_nodes.second - 1).m_XYZ.at(0))) / 2;
	arr.at(1) = ((m_nodes.at(p_edge.m_nodes.first-1).m_XYZ.at(1)) + (m_nodes.at(p_edge.m_nodes.second - 1).m_XYZ.at(1))) / 2;
	arr.at(2) = ((m_nodes.at(p_edge.m_nodes.first-1).m_XYZ.at(2)) + (m_nodes.at(p_edge.m_nodes.second - 1).m_XYZ.at(2))) / 2;
	return arr;
}

Node MeshLoader::get_middle_node(const Edge& cur_edge)
{
	Node new_node(m_nodes.size() + 1, get_middle_of_edge(cur_edge), 1);

	return new_node;
}
