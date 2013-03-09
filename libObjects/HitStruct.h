/*
 * HitStruct.h
 * Author: abhinavdevireddy
 */

#ifndef HITSTRUCT_H_
#define HITSTRUCT_H_

#include "Vector.h"

struct HitStruct {
	Vector normal;
	double distance;
	Vector color;
	Vector intersectPoint;
};

#endif /* HITSTRUCT_H_ */
