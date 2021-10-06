#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Types.h"

class MeshLoader{

	Node& get_node_by_id(int);

public:
	virtual void LoadMesh(const std::string&) = 0;
	MeshLoader() = default;
	virtual ~MeshLoader() {};

protected:
	std::vector<Node> m_nodes;
	std::vector<FiniteElement> m_finite_elems;
	std::vector<BoundaryFiniteElement> m_boundary;

public:
	const std::vector<Node>& get_node() const;
	const std::vector<FiniteElement>& get_finite_elems() const;
	const std::vector<BoundaryFiniteElement>& get_boundary() const;

	std::vector<int> find_elem_id(int p_node_id_1, int p_node_id_2, int p_node_id_3) const;
	std::vector<int> find_elem_edge(int p_node_id_1, int p_node_id_2) const;

	std::vector<int> get_node_by_boundary(int p_boundary_id) const; 
	std::vector<int> get_node_by_finite(int p_material_id) const;
	std::vector<int> get_f_node_by_boundary(int p_boundary_id) const;
	
	void insert_middle(); //метод, производ€щий вставку новых узлов в середины ребер существующих  Ё (включа€ граничные  Ё).
	                 //”честь, что обновл€ютс€ как списки узлов каждого  Ё, так общий список узлов сетки;
	//make_c_n(); //метод, создающий контейнер, n-ый элемент которого хранит контейнер всех Ђсоседейї по ребрам дл€ узла n;

	friend std::ostream& operator << (std::ostream&, const std::vector<Node>&);
	friend std::ostream& operator << (std::ostream&, const std::vector<FiniteElement>&);
	friend std::ostream& operator << (std::ostream&, const std::vector<BoundaryFiniteElement>&);
};