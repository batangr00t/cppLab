/*
 * vector.cpp
 *
 *  Created on: 2016. 4. 24.
 *      Author: juik
 */
#include <vector>
#include <iostream>

using namespace std;

int main() {
	cout << "---------- start -----------------" << endl;
	cout << "1. vector string  -----------------" << endl;
	size_t len = sizeof("hello");
	const char * hellostr = "hello";
	vector<char> vec;

	for ( int i = 0; i<len ; i++ ) {
		cout << "size=" << vec.size() << ", capacity=" << vec.capacity() << endl;
		vec.push_back(hellostr[i]);
	}
	cout << "size=" << vec.size() << ", capacity=" << vec.capacity() << endl;

	for ( const char& c : vec ) {
		cout << c;
	}
	cout << endl;

	cout << "2. reserve -------------" << endl;
	size_t len2 = sizeof("hello");
	const char * hellostr2 = "hello";
	vector<char> vec2;
	vec2.reserve( len2 );

	for ( int i = 0; i<len ; i++ ) {
		cout << "size=" << vec2.size() << ", capacity=" << vec2.capacity() << endl;
		vec2.push_back(hellostr2[i]);
	}
	cout << "size=" << vec2.size() << ", capacity=" << vec2.capacity() << endl;

	for ( const char& c : vec2 ) {
		cout << c;
	}
	cout << endl;


	cout << "2. const vector-------------" << endl;
	const vector<char> cstr = {'h', 'e', 'l', 'l', 'o' } ;
	for ( const char& c : cstr ) {
		cout << c;
	}
	cout << endl;
	//cstr.pop_back();  // error
	for ( const char& c : cstr ) {
		cout << c;
	}
	cout << endl;

	cout << "3. assign vector -------------" << endl;
	vector<int> vec3( { 1, 2, 3 });
	for ( const int& i : vec3 ) {
			cout << i << ", ";
	}
	cout << endl;

	vector<int> vec_copy = vec3;
	for ( const int& i : vec_copy ) {
		cout << i << ", ";
	}
	cout << endl;
	cout << "----------  end  -----------------" << endl;
}
