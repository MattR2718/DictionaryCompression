#include <map>
#include <vector>
#include <fstream>
#include <sstream>

#include "gnuplot-iostream.h"

int main() {
	Gnuplot gp;

    std::vector<std::tuple<int, int, std::string>> compressed;
    std::vector<std::tuple<int, int, std::string>> original;
    std::ifstream file("../sizes.txt");
    std::string linetxt;
    while (std::getline(file, linetxt)){
        std::istringstream iss(linetxt);
        std::vector<std::string> results(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());

        compressed.push_back(std::make_tuple(std::stoi(results[0]), std::stoi(results[1]), results[2]));
        original.push_back(std::make_tuple(std::stoi(results[0]), 18349, results[2]));
    }

	gp << "plot" << gp.file1d(compressed) << "using 1:2:xticlabels(3) with lines title 'compressed'," << gp.file1d(original) << "using 1:2:xticlabels(3) with lines title 'original'" << std::endl;

}