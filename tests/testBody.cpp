#ifndef _TESTBODY_H
#define _TESTBODY_H

#include "cppunit"

class BodyTest : public CppUnit::TestFixture {
private:
  Body *mybody;
public:
	void setUp() {
		mybody = new Body(90);
	}
	
	void tearDown() {
		delete mybody;
	}
	
	void testImpulse() {
		mybody->applyForce(Force(10, 10, 10));
	}
};

#endif
