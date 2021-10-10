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
	
	int nodes_number, dimension; 

	file >> nodes_number >> dimension;
	m_nodes.reserve(nodes_number);
	for (int i = 0; i < nodes_number; ++i) {
		Node cur_node;
		cur_node.m_node_id = i;
		file >> cur_node.m_XYZ.at(0) >> cur_node.m_XYZ.at(1) >> cur_node.m_XYZ.at(2);
		m_nodes.push_back(cur_node);
	}

	int finite_elems_number, number_of_nodes_in_finite_elem, number_of_bound, nodes_in_bound;

	file >> finite_elems_number >> number_of_nodes_in_finite_elem;
	m_finite_elems.reserve(finite_elems_number);
	for (int i = 0; i < finite_elems_number; ++i) {
		FiniteElement cur_f_elem;
		cur_f_elem.m_element_id = i;
		file >> cur_f_elem.m_material_id;
		cur_f_elem.m_node_id.reserve(number_of_nodes_in_finite_elem);
		for (int j = 0; j < number_of_nodes_in_finite_elem; ++j) {
			int node_id;
			file >> node_id;
			cur_f_elem.m_node_id.push_back(node_id);
		}
		m_finite_elems.push_back(cur_f_elem);
	}

	int boundary_number, nodes_in_boundary;

	file >> boundary_number >> nodes_in_boundary;
	m_finite_elems.reserve(boundary_number);
	for (int i = 0; i < boundary_number; ++i) {
		BoundaryFiniteElement cur_b_elem;
		cur_b_elem.m_element_id = i;
		file >> cur_b_elem.m_boundary_id;
		cur_b_elem.m_node_id.reserve(nodes_in_boundary);
		for (int j = 0; j < nodes_in_boundary; ++j) {
			int node_id;
			file >> node_id;
			cur_b_elem.m_node_id.push_back(node_id);
		}
		m_boundary.push_back(cur_b_elem);
	}
}