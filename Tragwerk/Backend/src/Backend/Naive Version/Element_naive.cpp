#include "Element_naive.h"
#include <cmath>

Element::Element(const double & x_A, const double & y_A, const double & x_B, const double & y_B): p_A(x_A, y_A), p_B(x_B, y_B) {
	double x_diff = x_B - x_A;
	double y_diff = y_B - y_A;
	L_0 = std::sqrt((x_diff)*(x_diff) + (y_diff)*(y_diff));
	l_s = x_diff/L_0;
	m_s = y_diff/L_0;
}


double Element::get_L_0() {return L_0;}
double Element::get_l_s() {return l_s;}
double Element::get_m_s() {return m_s;}
Backend::Point Element::get_p_A() {return p_A;}
Backend::Point Element::get_p_B() {return p_B;}



std::vector<std::vector<double>> Element::compute_stiff(const double & E, const double & A_0) {
	double pre_factor = E*A_0/L_0;
	double l_s_squared = l_s * l_s;
	double m_s_squared = m_s * m_s;
	double l_s_m_s = m_s * l_s;
	std::vector<std::vector<double>> stiff(4,std::vector<double> (4));
	//Maybe a faster way to initialise the matrix?
	stiff[0][0] = pre_factor*(l_s_squared);
	stiff[0][1] = pre_factor*(l_s_m_s); 
	stiff[0][2] = pre_factor*(- l_s_squared);
	stiff[0][3] = pre_factor*(- l_s_m_s);
	stiff[1][0] = pre_factor*(l_s_m_s);	
	stiff[1][1] = pre_factor*(m_s_squared);
	stiff[1][2] = pre_factor*(- l_s_m_s);
	stiff[1][3] = pre_factor*(- m_s_squared);
	stiff[2][0] = pre_factor*(- l_s_squared);
	stiff[2][1] = pre_factor*(- l_s_m_s);
	stiff[2][2] = pre_factor*(l_s_squared);
	stiff[2][3] = pre_factor*(l_s_m_s);
	stiff[3][0] = pre_factor*(- l_s_m_s);
	stiff[3][1] = pre_factor*(- m_s_squared);
	stiff[3][2] = pre_factor*(l_s_m_s);
	stiff[3][3] = pre_factor*(m_s_squared);

	return stiff;
}

void Element::assign_nodes(const std::vector<Backend::Node> & nodes) {
	for (int i = 0; i < nodes.size(); i++) {
		if (p_A.x == nodes[i].p.x && p_A.y == nodes[i].p.y) {
			first_node = nodes[i].id;
		}
		else if (p_B.x == nodes[i].p.x && p_B.y == nodes[i].p.y) {
			second_node = nodes[i].id;
		}
	}	


}

int Element::get_first_node() {return first_node;}

int Element::get_second_node() {return second_node;}


/*
int main() {
        Element first(0,2,1,4);
	std::cout << first.get_L_0() << std::endl;
	std::vector<std::vector<double>> A = first.compute_stiff(1,1);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << A[i][j] << " ";
		}
		std::cout << std::endl;
	}

	Backend::Node Node1(0,0,1);
	Backend::Node Node2(0,10,2);
	Backend::Node Node3(10,0,3);
	Backend::Node Node4(10,10,4);
	Backend::Node Node5(5,15,5);
	std::vector<Backend::Node> v = {Node1, Node2, Node3, Node4, Node5};
	Backend::Rod rod(0,0,10,0);
	
	Element second(0,0,10,0);
	std::cout << second.get_L_0() << std::endl;
	Backend::Point p_A = second.get_p_A();
	Backend::Point p_B = second.get_p_B();
	std::cout << "(x_A, y_A) = (" << p_A.x << "," << p_A.y << ")" << std::endl;
	std::cout << "(x_B, y_B) = (" << p_B.x << "," << p_B.y << ")" << std::endl;
	std::vector<std::vector<double>> B = second.compute_stiff(0.52,1);
        for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                        std::cout << B[i][j] << " ";
                }
                std::cout << std::endl;
        }
	
	second.assign_nodes(v);
	std::cout << "Start node is: " << second.get_first_node() << std::endl;
	std::cout << "End node is: " << second.get_second_node()  << std::endl;	




	return 0;

}

*/





