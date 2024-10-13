#include <iostream>
#include <vector>
#include "Simulator.h"

//It assembles and solves the linear system of equation, eventually returning the new nodes and new rods
class Assembler {
	private:
		int n;
		int dim;
		std::vector<std::vector<double>> A;
		std::vector<double> displacement;
		std::vector<double> rhs;
		std::vector<Backend::Node> nodes;
		std::vector<Backend::Rod> rods;
		std::vector<Backend::Bearing> bearings;
		std::vector<Backend::Force> forces;
		std::vector<Backend::Node> new_nodes;
		std::vector<Backend::Rod> new_rods;
		std::vector<Backend::Force> new_forces;
	public:
		Assembler();
		Assembler(const int &, const int &, const std::vector<Backend::Node> &,const std::vector<Backend::Rod> &,const std::vector<Backend::Force> &,const std::vector<Backend::Bearing> &);
		std::vector<std::vector<double>> get_A();
		std::vector<double> get_rhs();
		std::vector<double> get_displacement();
		std::vector<Backend::Node> get_new_nodes();
		std::vector<Backend::Rod> get_new_rods();
		std::vector<Backend::Force> get_new_forces();
		void assemble(const double &, const double &);
		std::vector<double> compute_forces();
		void apply_bearings();
		std::vector<Backend::Node> solve();
		std::vector<Backend::Rod> compute_new_rods();
		std::vector<Backend::Force> compute_new_forces();
};




