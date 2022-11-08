#include "SutherlandHodgman.h"
#include <stdexcept>

bool SutherlandHodgman::coupe(array<int, 2> s, array<int, 2> pj, array<int, 2> fi, array<int, 2> fi1)
{
	int tmp;

	if ((((pj[0] - s[0]) * (fi[1] - fi1[1])) - ((fi[0] - fi1[1]) * (pj[1] - s[1]))) == 0)
		return false;
	else
		tmp = 1 / (((pj[0] - s[0]) * (fi[1] - fi1[1])) - ((fi[0] - fi1[1]) * (pj[1] - s[1])));
	
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
	array<int, 2> b = { (fi[0] - s[0]),(fi[1] - s[1]) };
	array<int, 2> inverseAX = { (tmp * (fi[1] - fi1[1])),(tmp * -(fi[0] - fi1[0])) };
	array<int, 2> inverseAY = { (tmp * -(pj[1] - s[1])),(tmp * (pj[0] - s[0])) };
	array<int, 2> ts = { (inverseAX[0] * b[0] + inverseAX[1] * b[0]),(inverseAY[0] * b[1] + inverseAY[1] * b[1]) };

	array<int, 2> xy = { s[0] + ((pj[0] - s[0]) * ts[0]), s[1] + ((pj[1] - s[1]) * ts[0]) };

	/*int mSPj = (pj[1] - s[1]) / (pj[0] - s[0]);
	int kSPj = s[1] - (mSPj * s[0]);

	int mfifi1 = (fi1[1] - fi[1]) / (fi1[0] - fi[0]);
	int kfifi1 = fi[1] - (mfifi1 * fi[0]);

	int y = mSPj * s[0] + kSPj;
	int x = (y - kfifi1)/mfifi1;

	array<int, 2> ts = { (x),(y) };*/

	return xy;
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
	{
		if (fi[0] * fi1[1] - fi[1] * fi1[0] == 0)
		{
			if (fi[0] - fi[1] - fi1[0] - fi1[1] > 0)
			{
				if ((fisX * fi1fiY - fisY * fi1fiX) < 0)
					return false;
				else
					return true;
			}
			else
			{
				if ((fisX * fi1fiY - fisY * fi1fiX) > 0)
					return false;
				else
					return true;
			}
		}
		else if (fi[0] * fi1[1] - fi[1] * fi1[0] > 0)
		{
			if ((fisX * fi1fiY - fisY * fi1fiX) > 0)
				return false;
			else
				return true;
		}
		else
		{
			if ((fisX * fi1fiY - fisY * fi1fiX) < 0)
				return false;
			else
				return true;
		}
	}

	
}

vector<array<int, 2>> SutherlandHodgman::sutherlandHodgman(vector<array<int, 2>> pl, vector<array<int, 2>> pw)
{
	vector<array<int, 2>> ps;
	vector<array<int, 2>> pf;
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
			s = pl[j];
			if (j == 0)
				f = pl[j];
			else
			{
				if (coupe(s, pl[j], pw[i], pw[i + 1]))
				{
					I = intersection(s, pl[j], pw[i], pw[i + 1]);
					ps.push_back(I);
					pf.push_back(I);
					n2++;
				}
			}
			if (visible(s, pw[i], pw[i + 1]))
			{
				ps.push_back(s);
				pf.push_back(s);
				n2++;
			}
		}
		if (n2 > 0)
		{
			if (coupe(s, f, pw[i], pw[i + 1]))
			{
				I = intersection(s, f, pw[i], pw[i + 1]);
				ps.push_back(I);
				pf.push_back(I);
				n2++;
			}
			pl = ps;
			n1 = n2;
		}
	}

	return pf;
}
