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

	Edge& operator = (const Edge&); //!!! Зачем нужен оператор присваивания? Среди полей нет указателей.
	
	bool operator == (const Edge&) const;
	void update_mid(int);
};
