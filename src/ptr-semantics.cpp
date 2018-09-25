#include <iostream>
#include <memory>

class B{
public:
	B() : v(42.0){ std::cout << "B ctor\n"; }
	// without 'virtual', derived destructors will not be called
	virtual ~B(){ std::cout << "B dtor\n"; }
	B(B& b) : v(b.v){ std::cout << "B copy\n"; }
	B& operator=(const B&) = default;
	B& operator=(B&&) = default;
	B(B&& b) : v(b.v){ std::cout << "B move\n"; }
	virtual float get() { return v; }
protected:
	float v;
};

class D : public B{
public:
	D() {
		v = 36;
		std::cout << "D ctor\n";
	}
	~D(){ std::cout << "D dtor\n"; }
	float get() { return 1.2 * v; }
};

std::unique_ptr<B> f(){
	std::unique_ptr<B> widget {new D};
	return widget;
}

void g(){
	auto widget = f();
	std::cout << widget->get() << std::endl;
}

std::unique_ptr<D> h(){
	std::unique_ptr<D> widget {new D};
	return widget;
}

void j(){
	auto widget = h();
	std::cout << widget->get() << std::endl;
}
int main(){
	std::cout << "Using unique_ptr<Base>\n";
	g();
	std::cout << "Using unique_ptr<Derived>\n";
	j();
	std::cout << "Back in main()\n";
	return 0;
}
