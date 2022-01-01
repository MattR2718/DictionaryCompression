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
    int x = 0;
    while (std::getline(file, linetxt)){
        std::istringstream iss(linetxt);
        std::vector<std::string> results(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());

        compressed.push_back(std::make_tuple(x, std::stoi(results[1]), results[2]));
        original.push_back(std::make_tuple(x, std::stoi(results[0]), results[2]));
        x++;
    }

    //Plot compressed and original using the first and second components as x and y and the thirs as a label for the x axis
	gp << "plot" << gp.file1d(compressed) << "using 1:2:xticlabels(3) with lines title 'compressed'," << gp.file1d(original) << "using 1:2:xticlabels(3) with lines title 'original'" << std::endl;

    std::cout<<"PRESS ENTER TO CLOSE";
    std::cin.get();
}