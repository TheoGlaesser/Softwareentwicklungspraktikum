#pragma once
#include <iostream>
#include <vector>
#include "Simulator.h"

///Represents a finite element of a truss. It is used to compute the local stiffness matrix and to assign nodes to the finite element
class Element{
	private:
		double L_0;
		double l_s;
		double m_s;
		Backend::Point p_A;
		Backend::Point p_B;		
		const Backend::Node* first_node = nullptr;
		const Backend::Node* second_node = nullptr;
	public:
		Element(const Backend::Point &, const Backend::Point &, const std::vector<Backend::Node> &);
		double get_L_0();
		double get_l_s();
		double get_m_s();
		Backend::Point get_p_A();
		Backend::Point get_p_B();
		const Backend::Node* get_first_node();
		const Backend::Node* get_second_node();		
		std::vector<std::vector<double>> compute_stiff(const double &, const double &);
		void assign_nodes(const std::vector<Backend::Node> &);
};






