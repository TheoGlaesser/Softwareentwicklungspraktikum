#ifndef ELEMENT
#define ELEMENT
#include "Element.h"
#include <cmath>
#endif

Element::Element(const Backend::Point & p1, const Backend::Point & p2, const std::vector<Backend::Node> & nodes ) {
	p_A=p1;
	p_B=p2;
	double x_diff = p_B.x - p_A.x;
	double y_diff = p_B.y - p_A.y;
	L_0 = std::sqrt((x_diff)*(x_diff) + (y_diff)*(y_diff));
	l_s = x_diff/L_0;
	m_s = y_diff/L_0;
	assign_nodes(nodes);
}


double Element::get_L_0() {return L_0;}
double Element::get_l_s() {return l_s;}
double Element::get_m_s() {return m_s;}
Backend::Point Element::get_p_A() {return p_A;}
Backend::Point Element::get_p_B() {return p_B;}


//Compute local stiffness matrix
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

//assign to each element a node
void Element::assign_nodes(const std::vector<Backend::Node> & nodes) {
	for (int i = 0; i < nodes.size(); i++) {
		if (p_A.x == nodes[i].p.x && p_A.y == nodes[i].p.y) {
			first_node = &nodes[i];
		}
		else if (p_B.x == nodes[i].p.x && p_B.y == nodes[i].p.y) {
			second_node = &nodes[i];
		}
	}	


}

//get the class variables
const Backend::Node* Element::get_first_node() {return first_node;}

const Backend::Node* Element::get_second_node() {return second_node;}


/*Test
int main() {
	Backend::Node Node1(0,0,1);
	Backend::Node Node2(0,10,2);
	Backend::Node Node3(10,0,3);
	Backend::Node Node4(10,10,4);
	Backend::Node Node5(5,15,5);
	std::vector<Backend::Node> v = {Node1, Node2, Node3, Node4, Node5};
	
	Backend::Point p1(0,10);
        Backend::Point p2(5,15);
        Element first(p1,p2, v);
	Backend::Point p_check = first.get_p_A();
	std::cout << p_check.x << " " << p_check.y << std::endl;
        std::vector<std::vector<double>> A = first.compute_stiff(1,1);
        for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                        std::cout << A[i][j] << " ";
                }
                std::cout << std::endl;
        }
	
	
	
	
	Backend::Rod rod(0,0,10,0);
	Backend::Point p3(0,0);
	Backend::Point p4(10,0);
	Element second(p3,p4,v);
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
	
	std::cout << "Start node is: " << (*first.get_first_node()).id << std::endl;
	std::cout << "End node is: " << (*first.get_second_node()).id  << std::endl;	




	return 0;

}

*/




