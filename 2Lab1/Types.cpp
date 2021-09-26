#include "DataType.h"
#include "Types.h"

Node::Node(int p_node_id, const std::array<double, double, double>& p_XYZ, bool p_flag)
	: node_id(p_node_id), XYZ(p_XYZ), flag(p_flag)
{}

Node::Node(const Node& p_node)
	: node_id(p_node.node_id), XYZ(p_node.XYZ), flag(p_node.flag)
{}

std::istream& operator >> (std::istream& p_in, Node& p_node)
{
	p_in >> p_node.node_id;
	p_in >> get<0>(p_node.XYZ) >> get<1>(p_node.XYZ) >> get<2>(p_node.XYZ);
	p_in >> p_node.flag;
	return p_in;
}

std::ostream& operator << (std::ostream& p_out, const Node& p_node)
{
	p_out << p_node.node_id;
	p_out << get<0>(p_node.XYZ) << get<1>(p_node.XYZ) << get<2>(p_node.XYZ);
	p_out << p_node.flag;
	return p_out;
}
