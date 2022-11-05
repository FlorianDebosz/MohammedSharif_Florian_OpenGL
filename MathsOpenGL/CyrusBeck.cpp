#include "CyrusBeck.h"

vector<array<int, 2>> CyrusBeck::cyrusBeck(vector<array<int,2>> pts, vector<array<int,2>> wPts)
{
	calculNormale(wPts);

	vector<array<int, 2>> tmpPts = pts;

	for (int i = 0; i < pts.size() - 1; i++)
	{
		cyrusBeck(tmpPts[i][0], tmpPts[i][1], tmpPts[i + 1][0], tmpPts[i + 1][1],
			wPts, normale, wPts.size());
	}

	return finalPts;
}

bool CyrusBeck::cyrusBeck(int x1, int y1, int x2, int y2, vector<array<int, 2>> poly,
	vector<array<int, 2>> normale, int nbSom)
{
	float tInf = -1000, tSup = 1000;
	int dX = x2 - x1, dY = y2 - y1;
	int nbSeg = nbSom - 1;

	for (int i = 0; i < nbSeg-1; i++)
	{
		array<int, 2> c = poly[i];
		int dN = dX * normale[i][0] + dY * normale[i][1];
		int wN = (x1 - c[0]) * normale[i][0] + (y1 - c[1]) * normale[i][1];

		if (dN == 0)
			printf(" WN >= 0");
		else
		{
			float t =  -(static_cast<float>( wN) / static_cast<float>(dN));
			if (dN > 0)
			{
				if (t > tInf)
					tInf = t;
			}
			else
			{
				if (t < tSup)
					tSup = t;
			}
		}
	}

	if (tInf < tSup)
	{
		if ((tInf < 0) && (tSup > 1))
		{
			finalPts.push_back({ x1,y1 });
			finalPts.push_back({ x2,y2 });
			return true;
		}
		else
		{
			if ((tInf > 1) || (tSup < 0))
				return false;
			else
			{
				if (tInf < 0)
					tInf = 0;
				else
				{
					if (tSup > 1)
						tSup = 1;
				}
				x2 = x1 + dX * tSup;
				y2 = y1 + dY * tSup;
				x1 = x1 + dX * tInf;
				y1 = y1 + dY * tInf;
				finalPts.push_back({x1,y1});
				finalPts.push_back({x2,y2});
				return true;
			}
		}
	}
	else
		return false;
}

void CyrusBeck::calculNormale(vector<array<int, 2>> poly)
{
	if (!poly.empty())
	{
		for (int i = 0; i < poly.size() - 1; i++)
		{
			if (poly[i][0] * poly[i + 1][1] - poly[i][1] * poly[i + 1][0] == 0)
			{
				if (poly[i][0] - poly[i][1] - poly[i + 1][0] - poly[i + 1][1] > 0)
					normale.push_back({ -(poly[i + 1][1] - poly[i][1]), poly[i + 1][0] - poly[i][0] });
				else
					normale.push_back({ poly[i + 1][1] - poly[i][1], -(poly[i + 1][0] - poly[i][0]) });
			}
			else if (poly[i][0] * poly[i + 1][1] - poly[i][1] * poly[i + 1][0] > 0)
				normale.push_back({ -(poly[i + 1][1] - poly[i][1]), poly[i + 1][0] - poly[i][0] });
			else
				normale.push_back({ poly[i + 1][1] - poly[i][1], -(poly[i + 1][0] - poly[i][0]) });
		}
	}
}

void CyrusBeck::setNormale(vector<array<int, 2>> norm)
{
	normale = norm;
}

vector<array<int, 2>> CyrusBeck::getNormale()
{
	return normale;
}
