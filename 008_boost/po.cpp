#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/cmdline.hpp> // parse_command_line
#include <boost/program_options/parsers.hpp> // parse_command_line
#include <iostream>
#include <cmath>

using namespace std;
namespace po = boost::program_options;

int main(int argc, char * argv[] ) {
	int loglevel;

	cout << "---------- start -----------------" << endl;
	po::options_description desc("Allowed options");
	desc.add_options()
			("help,h", "produce help message")
			("version,v", "disp version")
			("loglevel,l", po::value<int>(&loglevel)->default_value(2), "set log level")
	;

	po::variables_map vm;
	try {
		po::store(po::parse_command_line(argc, argv, desc), vm);
	}
	catch (std::exception& e) {
	   std::cerr << "Error: " << e.what() << "\n";
	   return 1;
	}

	if ( vm.count("help")) {
		cout << desc  << endl;
		return 0;
	}

	if ( vm.count("version")) {
		cout << "1.1.1.1" << endl;
		return 0;
	}

	if ( vm.count("loglevel")) {
		cout << "loglevel = " << vm["loglevel"].as<int>() << endl;
	}

	cout << "----------  end  -----------------" << endl;
}
