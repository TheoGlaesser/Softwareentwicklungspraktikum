#include <iostream>
#include <vector>
#include "Constants_naive.h"
#include "Simulator_naive.h"


class Assembler {
	private:
		int n;
		int dim;
		std::vector<std::vector<double>> A;
		std::vector<double> displacement;
		std::vector<double> forces;
		std::vector<Backend::Node> new_nodes;
		std::vector<Backend::Rod> new_rods;
	public:
		Assembler(const int &, const int &);
		std::vector<std::vector<double>> get_A();
		std::vector<double> get_forces();
		std::vector<double> get_displacement();
		void assemble(const std::vector<Backend::Node> &,std::vector<Backend::Rod> &, std::vector<Backend::Force> &,std::vector<Backend::Bearing> &, const double &, const double &);
		std::vector<double> compute_forces(std::vector<Backend::Force> &, const std::vector<Backend::Node> &);
		void apply_bearings(const std::vector<Backend::Node> &, std::vector<Backend::Bearing> &);
		std::vector<Backend::Node> solve(const std::vector<Backend::Node>&);
		std::vector<Backend::Rod> compute_new_rods(const std::vector<Backend::Node> &, const std::vector<Backend::Rod> &);
};




