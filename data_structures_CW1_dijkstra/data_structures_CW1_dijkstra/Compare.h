#pragma once
#include "Path.h"

//Comparator to sort paths by distance in priority queue.
class Compare
{
public:
	bool operator() (Path a, Path b) const
	{
		return a.distance > b.distance;
	}
};