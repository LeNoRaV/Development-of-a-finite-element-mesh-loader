#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Types.h"
#include "AneuMeshLoader.h"

class MeshLoader{
	//MeshLoader();
	//virtual ~MeshLoader();
public:
	virtual void LoadMesh(const std::string&) = 0;

protected:
	std::vector<Node> nodes;
	std::vector<FiniteElement> finite_elems;
	std::vector<BoundaryFiniteElement> boundary;

public:
	const std::vector<Node>& get_node() const;
	const std::vector<FiniteElement>& get_finite_elems() const;
	const std::vector<BoundaryFiniteElement>& get_boundary() const;

	std::vector<int> find_elem_id(int p_node_id_1, int p_node_id_2, int p_node_id_3) const;
	std::vector<int> find_elem_edge(int p_node_id_1, int p_node_id_2) const;

	get_c_node_border(); //�����, ������������ ��������� ��������� ����� �� ID �������;
	get_c_range(); //�����, ������������ ��������� �� � �������� ID �������;
	get_c_ke_border(); //�����, ������������ ��������� ��������� �� � �������� ID �������;
	insert_middle(); //�����, ������������ ������� ����� ����� � �������� ����� ������������ �� (������� ��������� ��).
	                 //������, ��� ����������� ��� ������ ����� ������� ��, ��� ����� ������ ����� �����;
	make_c_n(); //�����, ��������� ���������, n-�� ������� �������� ������ ��������� ���� �������� �� ������ ��� ���� n;
	print_node();
	print_finite_element();
	print_boundary_finite_element();

};