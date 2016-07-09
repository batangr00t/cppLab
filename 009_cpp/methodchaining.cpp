#include <iostream>
#include <vector>
#include <string>

class Example {
public:
	Example() {
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}

	Example& setName( std::string arg ) {
		std::cout << __PRETTY_FUNCTION__ << arg << std::endl;
		_list.push_back( arg );
		return *this;
	}

	Example& operator()( std::string arg ) {
		std::cout << __PRETTY_FUNCTION__ << arg << std::endl;
		_list.push_back( arg );
		return *this;
	}

	std::string operator()( int n ) {
		return std::move(_list.at(n));
	}

	Example& add_options() {
		return *this;
	}

private:
	std::vector<std::string> _list;
};

int main() {
	Example desc;

	desc("first")("second");
	desc.setName("third").setName("forth");

	std::cout << desc(0) << std::endl;
	std::cout << desc(1) << std::endl;
	std::cout << desc(2) << std::endl;
	std::cout << desc(3) << std::endl;
}
