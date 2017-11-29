#include <iostream>
#include <map>
#include <memory>
#include <cstring>
#include "Box.h"

using namespace std;

class Resource {
private:
	unique_ptr<char []> resource;

public:
	Resource() {
		cout << this << " : " << __PRETTY_FUNCTION__ << endl;
	}
	Resource( const char * name ) {
		char * data = new char[10];
		strncpy( data, name, 10 );

		resource = unique_ptr<char []>( data );

		cout << this << " : " << __PRETTY_FUNCTION__ << resource.get() << endl;
	}
//	Resource(const Resource &) = delete;
//	Resource &operator=(const Resource &) = delete;
//	~Resource() {
//		cout << this << ":" << __PRETTY_FUNCTION__ << *resource.get() << endl;
//	}

};

int main() {
	cout << "---- start --- " << endl;

	// no problem
	Resource res1("Sample");
	Resource res2;
	res2 = Resource("sam2");

	std::unique_ptr<int> first(new int);      // OK
	std::unique_ptr<int> second = move(first);      // Fails, copy constructor is private
//	std::unique_ptr<int> third(first);        // Fails, copy constructor is private
	std::unique_ptr<int> fourth;
	fourth = move(first);                           // Fails, assignment operator is private

	map<string, string> map1;
	auto it= map1.insert({"cho", "haha"});
	cout << it.first->first << endl;
	cout << it.second << endl;
	string name = "cho";
	it = map1.insert( make_pair( name, "haha"));
	it = map1.insert( { name, "haha" });
	cout << it.first->first << endl;
	cout << it.second << endl;

	cout << "---- end --- " << endl;
}



