#include "Types.h"
#include <optional>
#include <array>
#include <vector>
#include <iostream>

Node::Node(int p_node_id, const std::array<double, 3>& p_XYZ, bool p_flag)
	: m_node_id(p_node_id), m_XYZ(p_XYZ), m_flag(p_flag)
{}

Node::Node(const Node& p_node)
	: m_node_id(p_node.m_node_id), m_XYZ(p_node.m_XYZ), m_flag(p_node.m_flag)
{}

std::istream& operator >> (std::istream& p_in, Node& p_node)
{
	p_in >> p_node.m_node_id;
	p_in >> p_node.m_XYZ.at(0) >> p_node.m_XYZ.at(1) >> p_node.m_XYZ.at(2); //fill array in
	p_in >> p_node.m_flag;
	return p_in;
}

std::ostream& operator << (std::ostream& p_out, const Node& p_node)
{
	p_out << p_node.m_node_id << std::endl;
	p_out << p_node.m_XYZ.at(0) << " " << p_node.m_XYZ.at(1) << " " << p_node.m_XYZ.at(2);
	p_out << p_node.m_flag << std::endl;
	return p_out;
}

FiniteElement::FiniteElement(int p_element_id, int p_material_id, const std::vector<int>& p_node_id)
	: m_element_id(p_element_id), m_material_id(p_material_id), m_node_id(p_node_id)
{}

std::optional<bool> read_node_id(std::istream& p_in) { // flag yes or no ( new node )
	int i;
	if (p_in >> i) return { i };
	else return { };
}

std::istream& operator>>(std::istream& p_in, FiniteElement& p_finite_elem)
{
	p_in >> p_finite_elem.m_element_id >> p_finite_elem.m_material_id;

	std::optional<bool> local_node_id;  // fill vector in
	local_node_id = read_node_id(p_in);
	while (local_node_id) {
		p_finite_elem.m_node_id.push_back(*local_node_id);
		local_node_id = read_node_id(p_in);
	}

	return p_in;
}

std::ostream& operator<<(std::ostream& p_out, const FiniteElement& p_finite_elem)
{
	p_out << p_finite_elem.element_id << std::endl << p_finite_elem.material_id << std::endl;
	p_out << "[ ";
	for (const auto& node : p_finite_elem.m_node_id) p_out << node << ", "; //vector
	p_out << "]";
	return p_out;
}

BoundaryFiniteElement::BoundaryFiniteElement(int p_element_id, int p_bound_id, const std::vector<int>& p_node_id)
	: m_element_id(p_element_id), m_boundary_id(p_bound_id), m_node_id(p_node_id)
{}

std::istream& operator >> (std::istream& p_in, BoundaryFiniteElement& p_boundary_finite_elem)
{
	p_in >> p_boundary_finite_elem.m_element_id >> p_boundary_finite_elem.m_boundary_id;

	std::optional<bool> local_node_id;  // fill vector in
	local_node_id = read_node_id(p_in);
	while (local_node_id) {
		p_boundary_finite_elem.m_node_id.push_back(*local_node_id);
		local_node_id = read_node_id(p_in);
	}

	return p_in;
}

std::ostream& operator << (std::ostream& p_out, const BoundaryFiniteElement& p_boundary_finite_elem)
{
	p_out << p_boundary_finite_elem.m_element_id << std::endl << p_boundary_finite_elem.m_boundary_id << std::endl;
	p_out << "[ ";
	for (const auto& node : p_boundary_finite_elem.m_node_id) p_out << node << ", ";
	p_out << "]";
	return p_out;
}
