#include <iostream>
#include <vector>
#include "Simulator_naive.h"

class Element{
	private:
		double L_0;
		double l_s;
		double m_s;
		Backend::Point p_A;
		Backend::Point p_B;		
		int first_node = 0;
		int second_node = 0;
	public:
		Element(const double &, const double &, const double &, const double &);
		double get_L_0();
		double get_l_s();
		double get_m_s();
		Backend::Point get_p_A();
		Backend::Point get_p_B();
		int get_first_node();
		int get_second_node();		
		std::vector<std::vector<double>> compute_stiff(const double &, const double &);
		void assign_nodes(const std::vector<Backend::Node> &);
		
};






