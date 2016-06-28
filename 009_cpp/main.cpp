#include <iostream>

namespace A {
	int a;
}

namespace B {
	int a;
}

using namespace A;
using namespace B;

int a;

int main(int argc, char * argv[] ) {

	std::cout << "---------- start -----------------" << std::endl;
	std::cout << A::a << std::endl;
	std::cout << B::a << std::endl;

	//전역네임스페이스
	std::cout << ::a << std::endl;
	std::cout << "----------  end  -----------------" << std::endl;
}
