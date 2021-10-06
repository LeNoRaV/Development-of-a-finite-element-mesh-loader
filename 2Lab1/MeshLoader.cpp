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

		first_to_find = found_boundary;
		if (found_boundary != last_to_find) {
			for (const auto& node_in_boundary : found_boundary->m_node_id)
				res.push_back(node_in_boundary);
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

		first_to_find = found_finite_elem;
		if (found_finite_elem != last_to_find) {
			for (const auto& node_in_finite_elem : found_finite_elem->m_node_id)
				res.push_back(node_in_finite_elem);
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
					res.push_back(node_in_boundary);
			}
			++first_to_find;
		}
	}
	return res;
}

void MeshLoader::insert_middle() 
{

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