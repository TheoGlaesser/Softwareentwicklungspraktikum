#ifndef TRUSSTEST
#define TRUSSTEST
#include "../Assembler.h"
#include "../Element.h"
#include <iostream>
#include <vector>
#endif
#include <gtest/gtest.h>

class TrussTest : public testing::Test {
	protected:
		std::vector<Backend::Node> test_nodes;
		std::vector<Backend::Rod> test_rods;
		std::vector<Backend::Bearing> test_bearings;
		std::vector<Backend::Force> test_forces;
		double test_A_0;
		double test_E;
		int dim;
		Assembler test_truss;
		TrussTest() {dim = 2;}
		void SetUp(const std::vector<Backend::Node> & nodes, const std::vector<Backend::Rod> & rods, const std::vector<Backend::Bearing> & bearings, const std::vector<Backend::Force> & forces, const double & A_0, const double & E) { 
			test_nodes = nodes;
			test_rods = rods;
			test_forces = forces;
			test_bearings = bearings;
			test_A_0 = A_0;
			test_E = E;
			Assembler test_truss_copy(dim, nodes.size(), nodes, rods, forces, bearings);
			test_truss = test_truss_copy;
			test_truss.assemble(E, A_0);
		}

		std::vector<std::vector<double>> test_element(const Backend::Point & p1, const Backend::Point & p2) {
			Element test_object(p1,p2,test_nodes);
			return test_object.compute_stiff(test_A_0, test_E);
		}

		std::vector<std::vector<double>> test_global_stiff() {
			return test_truss.get_A();
		}

			
		std::vector<double> test_rhs() {
			return test_truss.get_rhs();
		}

		std::vector<double> test_displacement() {
			return test_truss.get_displacement();
		}		       
			
};





TEST_F(TrussTest, General) {
	Backend::Node Node1(0,0,0);
        Backend::Node Node2(0,2,1);
        Backend::Node Node3(2,2,2);
        Backend::Node Node4(2,0,3);
        Backend::Node Node5(1,4,4);
        std::vector<Backend::Node> nodes = {Node1, Node2, Node3, Node4, Node5};
        Backend::Rod Rod1(0,0,0,2);
        Backend::Rod Rod2(0,2,2,2);
        Backend::Rod Rod3(2,2,2,0);
        Backend::Rod Rod4(2,0,0,2);
        Backend::Rod Rod5(0,2,1,4);
        Backend::Rod Rod6(1,4,2,2);
        Backend::Rod Rod7(2,2,0,0);
        Backend::Rod Rod8(0,0,2,0);
        std::vector<Backend::Rod> rods = {Rod1, Rod2, Rod3, Rod4, Rod5, Rod6, Rod7, Rod8};
        Backend::Force Force1(2,2,-10,45);
        Backend::Force Force2(1,4,-30,90);
        std::vector<Backend::Force> forces = {Force1, Force2};
        Backend::Bearing Bearing1(0,0,0,0);
        Backend::Bearing Bearing2(2,0,0,0);
        std::vector<Backend::Bearing> bearings = {Bearing1, Bearing2};	
	SetUp(nodes, rods, bearings, forces, 1,1);

	//test of the element
	Backend::Point p1(0,0);
        Backend::Point p2(0,2);
        std::vector<std::vector<double>> test_stiff=test_element(p1,p2);
	std::vector<std::vector<double>> correct_stiff(4, std::vector<double> (4,0));
        correct_stiff[1][1] = 0.5;
        correct_stiff[1][3] = -0.5;
        correct_stiff[3][1] = -0.5;
        correct_stiff[3][3] = 0.5;
	std::cout << "Diocane" << std::endl;
        EXPECT_EQ(test_stiff, correct_stiff);
	testing::internal::CaptureStdout();
	std::cout << "Helo world" <<std::endl;
	//Test right hand side
	std::vector<double> correct_rhs = {0,0,0,0, -7.07107, -7.07107, 0, 0, 0, -30};
	std::vector<double> output_rhside = test_rhs();
	for (int i = 0; i < correct_rhs.size(); i++) {
		EXPECT_NEAR(output_rhside[i], correct_rhs[i],10e-5);
	}


	//Test displacement
	std::vector<double> correct_displacement = {0, 0, -27.79, -29.42, -12.21, -29.42, 0, 0,-20, -75.24};
	std::vector<double> output_displacement = test_displacement();
	for (int i = 0; i < correct_displacement.size(); i++) {
		EXPECT_NEAR(output_displacement[i], correct_displacement[i], 10e-3);
	}

}



int main (int argc, char **argv) {
	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}








