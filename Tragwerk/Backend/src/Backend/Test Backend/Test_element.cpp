#include <cassert>
#include "../Element.h"
#include <cmath>
#include <gtest/gtest.h>

/*
void test_element() {
	Backend::Node Node1(0,0,0);
	Backend::Node Node2(0,10,1);
	Backend::Node Node3(10,0,2);
	Backend::Node Node4(10,10,3);
	Backend::Node Node5(5,15,4);
	std::vector<Backend::Node> v = {Node1, Node2, Node3, Node4, Node5};

	Backend::Point p1(0,0);
        Backend::Point p2(0,10);
        Element first(p1,p2,v);
	double length = 10;
	double diff = std::abs(first.get_L_0() - length); 
	std::cout << "Difference in output (length): "  << diff << std::endl;
}

*/




TEST(Element, variables) {
	Backend::Node Node1(0,0,0);
        Backend::Node Node2(0,2,1);
        Backend::Node Node3(2,2,2);
        Backend::Node Node4(2,0,3);
        Backend::Node Node5(1,4,4);
        std::vector<Backend::Node> v = {Node1, Node2, Node3, Node4, Node5};

        Backend::Point p1(0,0);
        Backend::Point p2(0,2);
        Element first(p1,p2,v);
	std::vector<std::vector<double>> element_stiff=first.compute_stiff(1,1);
	std::vector<std::vector<double>> correct_stiff(4, std::vector<double> (4,0));
       	correct_stiff[1][1] = 0.5;
	correct_stiff[1][3] = -0.5;
	correct_stiff[3][1] = -0.5;
	correct_stiff[3][3] = 0.5;
	EXPECT_EQ(element_stiff, correct_stiff);

}

/*
int main() {
	test_element();
	
	return 0;
}

*/



