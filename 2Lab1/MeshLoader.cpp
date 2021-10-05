#include "MeshLoader.h"

const std::vector<Node>& MeshLoader::get_node() const
{
	return nodes;
}

const std::vector<FiniteElement>& MeshLoader::get_finite_elems() const
{
	return finite_elems;
}

const std::vector<BoundaryFiniteElement>& MeshLoader::get_boundary() const
{
	return boundary;
}

std::vector<int> MeshLoader::find_elem_id(int p_node_id_1, int p_node_id_2, int p_node_id_3) const
{
	std::vector<int> res;

	auto first_to_find = finite_elems.begin();
	auto last_to_find = finite_elems.end();
	//InputIterator find_if (InputIterator first, InputIterator last, UnaryPredicate pred);
	while (first_to_find != last_to_find) {
		auto found_elem = std::find_if(first_to_find, last_to_find,
			[p_node_id_1, p_node_id_2, p_node_id_3](const FiniteElement& elem) { //lambda
				return std::find(elem.node_id.begin(), elem.node_id.end(), p_node_id_1) != elem.node_id.end()
					&& std::find(elem.node_id.begin(), elem.node_id.end(), p_node_id_2) != elem.node_id.end()
					&& std::find(elem.node_id.begin(), elem.node_id.end(), p_node_id_3) != elem.node_id.end();
			});

		first_to_find = found_elem;
		if (found_elem != last_to_find) {
			res.push_back(found_elem->element_id);
			++first_to_find;
		}
	}
	return res;
}

std::vector<int> MeshLoader::find_elem_edge(int p_node_id_1, int p_node_id_2) const
{
	std::vector<int> res;

	auto first_to_find = finite_elems.begin();
	auto last_to_find = finite_elems.end();

	while (first_to_find != last_to_find) {
		auto found_elem = std::find_if(first_to_find, last_to_find,
			[p_node_id_1, p_node_id_2](const FiniteElement& elem) {
				return std::find(elem.node_id.begin(), elem.node_id.end(), p_node_id_1) != elem.node_id.end()
					&& std::find(elem.node_id.begin(), elem.node_id.end(), p_node_id_2) != elem.node_id.end();
			});

		first_to_find = found_elem;
		if (found_elem != last_to_find) {
			res.push_back(found_elem->element_id);
			++first_to_find;
		}
	}

	return res;
}

