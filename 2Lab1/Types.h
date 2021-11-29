#pragma once
#include <iostream>
#include <vector>
#include <array>

struct Node {
	std::array<double, 3> m_XYZ;
	int m_node_id;
	bool m_flag = 0; //0-not middle, 1-it is

	Node() = default;
	Node(int, const std::array<double, 3>&, bool);
	Node(const Node&);

	friend std::istream& operator >> (std::istream&, Node&);
	friend std::ostream& operator << (std::ostream&, const Node&);
};

struct FiniteElement {
	int m_element_id;
	int m_material_id;
	std::vector<int> m_node_id;

	FiniteElement() = default;
	FiniteElement(int, int, const std::vector<int>&);

	friend std::istream& operator >> (std::istream&, FiniteElement&);
	friend std::ostream& operator << (std::ostream&, const FiniteElement&);
};

struct BoundaryFiniteElement {
	int m_element_id;
	int m_boundary_id;
	std::vector<int> m_node_id;

	BoundaryFiniteElement() = default;
	BoundaryFiniteElement(int, int, const std::vector<int>&);

	friend std::istream& operator >> (std::istream&, BoundaryFiniteElement&);
	friend std::ostream& operator << (std::ostream&, const BoundaryFiniteElement&);
};

struct Edge {
	std::pair<int, int> m_nodes;
	int m_middle_node=-1;

	Edge() = default;
	Edge(int, int);
	
	bool operator == (const Edge&) const;
	
	void update_mid(int);
};

class Hash
{
public:
	std::size_t operator() (const Edge& _p) const
	{
		std::size_t o_seed = 0;
		if (_p.m_nodes.first > _p.m_nodes.second)
		{
			o_seed ^= std::hash<int>() (_p.m_nodes.first) + 0x9e3779b9 + (o_seed << 6) + (o_seed >> 2);
			o_seed ^= std::hash<int>() (_p.m_nodes.second) + 0x9e3779b9 + (o_seed << 6) + (o_seed >> 2);
		}
		else
		{
			o_seed ^= std::hash<int>() (_p.m_nodes.second) + 0x9e3779b9 + (o_seed << 6) + (o_seed >> 2);
			o_seed ^= std::hash<int>() (_p.m_nodes.first) + 0x9e3779b9 + (o_seed << 6) + (o_seed >> 2);
		}

		return o_seed;
	};
};

namespace std {
	std::ostream& operator << (std::ostream& out, const std::vector <int>& elem);
}

