#pragma once
#include <iostream>
#include <vector>
#include <array>

struct Node {
	std::array<double, 3> XYZ;
	int node_id;
	bool flag = 0;

	Node(int, const std::array<double, 3>&, bool);
	Node(const Node&);

	friend std::istream& operator >> (std::istream&, Node&);
	friend std::ostream& operator << (std::ostream&, const Node&);
};

struct FiniteElement {
	int element_id;
	int material_id;
	std::vector<int> node_id;

	FiniteElement(int, int, const std::vector<int>&);

	friend std::istream& operator >> (std::istream&, FiniteElement&);
	friend std::ostream& operator << (std::ostream&, const FiniteElement&);
};

struct BoundaryFiniteElement {
	int element_id;
	int boundary_id;
	std::vector<int> node_id;

	BoundaryFiniteElement(int, int, const std::vector<int>&);

	friend std::istream& operator >> (std::istream&, BoundaryFiniteElement&);
	friend std::ostream& operator << (std::ostream&, const BoundaryFiniteElement&);
};
