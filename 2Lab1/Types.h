#pragma once
struct Node {
	std::array<double, double, double> XYZ;
	int node_id;
	bool flag = 0;

	Node(int, const std::array<double, double, double>&, bool);
	Node(const Node&);

	friend std::istream& operator >> (std::istream&, Node&);
	friend std::ostream& operator << (std::ostream&, const Node&);
}

struct FiniteElement {

};

struct BoundaryFiniteElement {

};