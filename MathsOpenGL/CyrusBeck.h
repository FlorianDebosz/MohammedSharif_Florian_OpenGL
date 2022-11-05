#pragma once
#ifndef CYRUSBECK_H
#define CYRUSBECK_H

#include <vector>
#include <array>

using namespace std;

class CyrusBeck
{
public:
	vector<array<int,2>> cyrusBeck(vector<array<int, 2>> pts, vector<array<int,2>> wPts);
	bool cyrusBeck(int x1, int y1, int x2, int y2, vector<array<int, 2>> poly,
		vector<array<int, 2>> normale, int nbSom);
	void calculNormale(vector<array<int, 2>> poly);
	void setNormale(vector<array<int, 2>> norm);
	vector<array<int, 2>> getNormale();
private:
	vector < array<int, 2>> normale;
	vector < array<int, 2>> finalPts;
};

#endif CYRUSBECK_H
