#pragma once
#ifndef SUTHERLANDHODGMAN_H
#define SUTHERLANDHODGMAN_H

#include <array>
#include <vector>

using namespace std;

class SutherlandHodgman
{
public:
	bool coupe(array<int, 2> s, array<int, 2> pj, array<int, 2> fi, array<int, 2> fi1);
	array<int, 2> intersection(array<int, 2> s, array<int, 2> pj, array<int, 2> fi, array<int, 2> fi1);
	bool visible(array<int, 2> s, array<int, 2> fi, array<int, 2> fi1);
	vector<array<int, 2>> sutherlandHodgman(vector<array<int,2>> pl, vector<array<int,2>> pw);
};

#endif // !SUTHERLANDHODGMAN_H
