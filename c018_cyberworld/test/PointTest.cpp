#include "gtest/gtest.h"
#include "Point.h"
#include <random>

using namespace std;

namespace {

// The fixture for testing class Foo.
class PointTest: public ::testing::Test {
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	PointTest() {
		// You can do set-up work for each test here.
	}

	virtual ~PointTest() {
		// You can do clean-up work that doesn't throw exceptions here.
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:

	virtual void SetUp() {
		// Code here will be called immediately after the constructor (right
		// before each test).
	}

	virtual void TearDown() {
		// Code here will be called immediately after each test (right
		// before the destructor).
	}

	// Objects declared here can be used by all tests in the test case for Foo.
};

// Tests that the Foo::Bar() method does Abc.
TEST_F(PointTest, consdest) {
	random_device rd;
	mt19937 gen(rd());
	normal_distribution<> dis(0, 10);

	for ( int i=0; i<10; ++i ) {
		Point p( dis(gen), dis(gen) );
		cout << p << endl;
	}
}

TEST_F(PointTest, move) {

}

}  // namespace

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
