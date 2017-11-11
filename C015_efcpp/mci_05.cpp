/*
 * mci_05.cpp
 *
 *  Created on: 2017. 11. 11.
 *      Author: cho
 */
#include <iostream>
#include <ostream>
#include <unordered_map>
#include <map>

using namespace std;

class Name {
public:
	Name( const string& param ) : name( param ) {
		cout << __PRETTY_FUNCTION__ << endl;
	};
	virtual ~Name() {
		cout << __PRETTY_FUNCTION__ << endl;
	};

	bool operator==( const Name& other ) const {
		return this->name == other.name;
	}

	string name;
};

ostream& operator<<( ostream& os, const Name& n ) {
	os << n.name;
	return os;
}

namespace std {
	template<>
	struct hash<Name> {
		size_t operator()(const Name& k) const {
			auto h = hash<string>();
			return h(k.name);
		};
	};
}

int main() {
	cout << "---- start ----" << endl;

	std::unordered_map<Name, int> m{
		{Name("first"),1},
		{Name("second"),2},
		{Name("third"),3}
	};

	cout << "=========== bad " << endl;
	for ( const pair<Name, int>& p : m ) {
		cout << p.first << " => " << p.second << endl;
	}

	cout << "=========== good " << endl;
	for ( const pair<const Name, int>& p : m ) {
		cout << p.first << " => " << p.second << endl;
	}

	cout << "=========== better " << endl;
	for ( const auto& p : m ) {
		cout << p.first << " => " << p.second << endl;
	}

	cout << "----  end  ----" << endl;
}


