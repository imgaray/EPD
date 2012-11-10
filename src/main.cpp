#include "Polygon.h"
#include "Circle.h"
#include <iostream>
using namespace std;

int main() {
	Vec v1, v2(0,1), v3(1,0), v4(2,0);
	Polygon p1(v1);
	Circle c1(v4, 1);

	p1.addVertex(v2);
	p1.addVertex(v3);

	if (p1.touches(c1))
		cout << "se tocan" <<endl;
	else cout << "no se tocan" <<endl;

	return 0;
}
