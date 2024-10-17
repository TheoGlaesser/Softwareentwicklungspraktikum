#ifndef TRUSSTEST
#define TRUSSTEST
#include "../Assembler.h"
#include "../Element.h"
#include "../Simulator.h"
#include <iostream>
#include <vector>
#include <utility>
#endif
#include <gtest/gtest.h>

#define M_PI 3.14159265358979323846 //pi

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
			Backend::Exception error(true);
			test_truss.assemble(E, A_0,error);
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
			std::vector<double> displacementTest = test_truss.get_displacement();
			return test_truss.get_displacement();
		}		       
			
};





TEST_F(TrussTest, General) {
	Backend::Node Node1(0,0,0);
        Backend::Node Node2(0,100,1);
        Backend::Node Node3(100,100,2);
        Backend::Node Node4(100,0,3);
        Backend::Node Node5(50,200,4);
        std::vector<Backend::Node> nodes = {Node1, Node2, Node3, Node4, Node5};
        Backend::Rod Rod1(0,0,0,100);
        Backend::Rod Rod2(0,100,100,100);
        Backend::Rod Rod3(100,100,100,0);
        Backend::Rod Rod4(100,0,0,100);
        Backend::Rod Rod5(0,100,50,200);
        Backend::Rod Rod6(50,200,100,100);
        Backend::Rod Rod7(100,100,0,0);
        Backend::Rod Rod8(0,0,100,0);
        std::vector<Backend::Rod> rods = {Rod1, Rod2, Rod3, Rod4, Rod5, Rod6, Rod7, Rod8};
        double angle = 90;
        double rad = angle*M_PI/180;
        Backend::Force Force1(50,200,100000,rad);
        std::vector<Backend::Force> forces = {Force1};
	std::pair<bool, double> xInfo1(true,0);
	std::pair<bool, double> yInfo1(true,0);
	std::pair<bool, double> xInfo2(true,0);
	std::pair<bool, double> yInfo2(true,0);
        Backend::Bearing Bearing1(0,0,xInfo1,yInfo1);
        Backend::Bearing Bearing2(100,0,xInfo2,yInfo2);
        std::vector<Backend::Bearing> bearings = {Bearing1, Bearing2};
	SetUp(nodes, rods, bearings, forces, 1,100000);

	//Test right hand side
	std::vector<double> correct_rhs = {0,0,0,0, 0,0, 0, 0, 0, -100000};
	std::vector<double> output_rhside = test_rhs();
	for (int i = 0; i < correct_rhs.size(); i++) {
		EXPECT_NEAR(output_rhside[i], correct_rhs[i],10e-5) << "Error in rhs at element " << i;
	}
 

	//Test displacement
	std::vector<double> correct_displacement = {0, 0, -16.83, -41.34, 16.83, -41.34, 0, 0,0, -119.62};
	std::vector<double> output_displacement = test_displacement();
	for (int i = 0; i < correct_displacement.size(); i++) {
    EXPECT_NEAR(output_displacement[i], correct_displacement[i], 10e-3) << "Error in displacement at element " << i;
	}
	
	

}


TEST_F(TrussTest, Element) {
	Backend::Node Node1(0,0,0);
        Backend::Node Node2(0,2,1);
        Backend::Node Node3(2,2,2);
        Backend::Node Node4(2,0,3);
        Backend::Node Node5(1,4,4);
        std::vector<Backend::Node> nodes = {Node1, Node2, Node3, Node4, Node5};
        Backend::Rod Rod1(0,0,0,100);
        Backend::Rod Rod2(0,2,2,2);
        Backend::Rod Rod3(2,2,2,0);
        Backend::Rod Rod4(2,0,0,2);
        Backend::Rod Rod5(0,2,1,4);
        Backend::Rod Rod6(1,4,2,2);
        Backend::Rod Rod7(2,2,0,0);
        Backend::Rod Rod8(0,0,2,0);
        std::vector<Backend::Rod> rods = {Rod1, Rod2, Rod3, Rod4, Rod5, Rod6, Rod7, Rod8};
        double angle = 90;
        double rad = angle*M_PI/180;
        Backend::Force Force1(1,4,1,rad);
        std::vector<Backend::Force> forces = {Force1};
        std::pair<bool, double> xInfo1(true,0);
    	std::pair<bool, double> yInfo1(true,0);
 	std::pair<bool, double> xInfo2(true,0);
	std::pair<bool, double> yInfo2(true,0);
	Backend::Bearing Bearing1(0,0,xInfo1,yInfo1);
        Backend::Bearing Bearing2(2,0,xInfo2,yInfo2);
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
        EXPECT_EQ(test_stiff, correct_stiff);
}




int main (int argc, char **argv) {
	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}








