#include <iostream>
#include <string>
#include <vector>

unsigned int gbl_obj_counter = 0;

class V{
public:
	explicit V(const char* msg);
	V(V&& v);
	V& operator=(V& v); //not implemented
	V& operator=(V&& v); //not implemented
	~V();
	friend std::ostream& operator<<(std::ostream& os, const V& v);
private:
	int id;
	const char* data;
};

V::V(const char* msg)
	: data (msg) {
	id = ++gbl_obj_counter;
	std::cout << "ctor (" << id << ") " << std::endl;
}

V::V(V&& v){
	id = ++gbl_obj_counter;
	data = v.data;
	v.data = nullptr;
	std::cout << "move (" << id << ") " << std::endl;
}

V::~V(){
	std::cout << "dtor (" << id << ") " << std::endl;
}

std::ostream& operator<<(std::ostream& os, const V& v){
	os << v.data;
	return os;
}

V defaultV(){
	V tempV("Default msg");
	std::cout << "end of defaultV()" << std::endl;
	return tempV;
}

int main(){
	const char* msg = "Message that can only exist in one place";
	V v1(msg);
	V v2("Hello v2");
	std::cout << v1 << std::endl;
	std::cout << v2 << std::endl;
	V movedV = std::move(v1);           //v1 can no longer be accessed
	std::cout << movedV << std::endl;
    /* to see move constructors, compile with -fno-elide-constructors */
	V v3 = defaultV();
	/* move constructors and vector<>*/
	using std::vector;
	vector<V> vs;
	vs.reserve(2);
	std::cout << "start of vector test:" << std::endl;
	vs.push_back(std::move(movedV));
	vs.push_back(std::move(v2));
	// size of vs is 2 initially, so before the 3rd V can be inserted,
	// all elements have to be moved. In total 5 objects are created (2 deleted)
	// to ensure only 3 objects are created, reserve 3 elements in vs.
	vs.push_back(std::move(v3));
	std::cout << "end of main()" << std::endl;
	return 0;
}
