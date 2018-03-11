#include "spellsmanager.h"

using namespace Spells;

hgeVector *MakeVector(point Destiny)
{
	hgeVector *testVector;
	testVector=new hgeVector(Destiny.x, Destiny.y);
	float angle=testVector->Angle();

	hgeVector *finalVector;
	finalVector=new hgeVector(0, 200);
	finalVector->Rotate(angle);
	return finalVector;
}