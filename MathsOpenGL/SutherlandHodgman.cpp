#include "SutherlandHodgman.h"

bool SutherlandHodgman::coupe(array<int, 2> s, array<int, 2> pj, array<int, 2> fi, array<int, 2> fi1)
{
	int tmp = 1 / (((pj[0]-s[0]) * (fi[1]-fi1[1])) - ((fi[0]-fi1[1]) * (pj[1]-s[1])));
	array<int, 2> b = {(fi[0]-s[0]),(fi[1]-s[0])};
	array<int, 2> inverseAX = {(tmp * (fi[1] - fi1[1])),(tmp * -(fi[0] - fi1[0]))};
	array<int, 2> inverseAY = {(tmp * -(pj[1] - s[1])),(tmp * (pj[0] - s[0]))};
	array<int, 2> ts = {(inverseAX[0]*b[0]+inverseAX[1]*b[0]),(inverseAY[0] * b[1] + inverseAY[1] * b[1])};

	if (ts[0] >= 0 && ts[0] <= 1 && ts[1] >= 0 && ts[1] <= 1)
		return true;
	else
		return false;
}

array<int, 2> SutherlandHodgman::intersection(array<int, 2> s, array<int, 2> pj, array<int, 2> fi, array<int, 2> fi1)
{
	int tmp = 1 / (((pj[0] - s[0]) * (fi[1] - fi1[1])) - ((fi[0] - fi1[1]) * (pj[1] - s[1])));
	array<int, 2> b = { (fi[0] - s[0]),(fi[1] - s[0]) };
	array<int, 2> inverseAX = { (tmp * (fi[1] - fi1[1])),(tmp * -(fi[0] - fi1[0])) };
	array<int, 2> inverseAY = { (tmp * -(pj[1] - s[1])),(tmp * (pj[0] - s[0])) };
	array<int, 2> ts = { (inverseAX[0] * b[0] + inverseAX[1] * b[0]),(inverseAY[0] * b[1] + inverseAY[1] * b[1]) };

	return ts;
}

bool SutherlandHodgman::visible(array<int, 2> s, array<int, 2> fi, array<int, 2> fi1)
{
	int fisX = s[0] - fi[0];
	int fisY = s[1] - fi[1];
	int fi1fiX = fi1[0] - fi[0];
	int fi1fiY = fi1[1] - fi[1];

	if ((fisX * fi1fiY - fisY * fi1fiX) == 0)
		return true;
	else
		return false;
}

vector<array<int, 2>> SutherlandHodgman::sutherlandHodgman(vector<array<int, 2>> pl, vector<array<int, 2>> pw)
{
	vector<array<int, 2>> ps;
	array<int, 2> f;
	array<int, 2> s;
	array<int, 2> I;
	int n1 = pl.size();
	int n2;

	for (int i = 0; i < pw.size() - 1; i++)
	{
		n2 = 0;
		ps.clear();

		for (int j = 0; j < n1-1; j++)
		{
			if (j == 0)
				copy(pl[j].begin(), pl[j].end(), f.begin());
			else
			{
				if (coupe(s, pl[j], pw[i], pw[i + 1]))
				{
					I = intersection(s, pl[j], pw[i], pw[i + 1]);
					ps.push_back(I);
					n2++;
				}
			}
			copy(pl[j].begin(), pl[j].end(), s.begin());
			if (visible(s, pw[i], pw[i + 1]))
			{
				ps.push_back(s);
				n2++;
			}
		}
		if (n2 > 0)
		{
			if (coupe(s, f, pw[i], pw[i + 1]))
			{
				I = intersection(s, f, pw[i], pw[i + 1]);
				ps.push_back(I);
				n2++;
			}
			pl = ps;
			n1 = n2;
		}
	}

	return ps;
}
