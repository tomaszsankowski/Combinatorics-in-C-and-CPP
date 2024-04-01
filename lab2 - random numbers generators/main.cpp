#include <iostream>
#include <list>
#include <cmath>
#include <climits>
#include <iterator>

using namespace std;

struct Pair {
	double x, y;
};

class RandomGen
{
public:
	int a, c, m;
	int seed;

	RandomGen(const int a, const int c, const int m)
	{
		this->a = a;
		this->c = c;
		this->m = m;

		this->seed = (17 * a + 3) % m;
	}

	double generateNext()
	{
		const int tmp = (a * seed + c) % m;
		this->seed = tmp;
		auto out = double(double(seed) / double(m));
		return fabs(out);
	}

	Pair generatePair()
	{
		Pair out{};
		out.x = generateNext();
		out.y = generateNext();
		return out;
	}
};

class RegisterGen
{
public:
	list<bool> bits;

	int p, q;

	RegisterGen(const int p, const int q)
	{
		this->p = p;
		this->q = q;
		RandomGen gen(16807, 17, INT_MAX);
		for (int i = 0; i < 128; i++)
		{
			if (gen.generateNext() > 0.5)
				bits.push_front(1);
			else
				bits.push_front(0);
		}
	}

	bool generateNextBit()
	{
		auto it = bits.begin();
		advance(it, p);
		bool bit_p = *it;
		it = bits.begin();
		advance(it, q);
		bool bit_q = *it;
		bool newBit = bit_p ^ bit_q;
		bits.pop_front();
		bits.push_back(newBit);
		return newBit;
	}
};

int main()
{
	RandomGen generator1(16807, 17, INT_MAX);

	const double R = 5.0;
	int pointsCounter = 0, circleCounter = 0;
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			double f = generator1.generateNext();
			cout << f << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < 100000; i++)
	{
		Pair p = generator1.generatePair();
		p.x *= 2;
		p.x -= 1;
		p.y *= 2;
		p.y -= 1;
		double odl = sqrt((p.x - 0.0) * (p.x - 0.0) + (p.y - 0.0) * (p.y - 0.0));
		double odl2 = sqrt((p.x - 1.0) * (p.x - 1.0) + (p.y - 1.0) * (p.y - 1.0));
		if (odl < 1.0)
			circleCounter++;
		if (odl < 1.0 && odl2 < R)
			pointsCounter++;
	}
	int counterF = 0;
	for (int i = 0; i < 100000; i++)
	{
		double f = generator1.generateNext();
		if (f >= 0.1 && f <= 0.25)
			counterF++;
	}
	cout << double(double(counterF) / 100000) << endl;
	cout << double(double(pointsCounter) / 25000) << endl;
	cout << double(double(circleCounter) / 25000) << endl;

	RegisterGen gen(29, 2);
	int oneCounter = 0;
	for (int i = 0; i < 100000; i++)
	{
		bool nr = gen.generateNextBit();
		if (nr)
			oneCounter++;
	}

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			bool b = gen.generateNextBit();
			cout << b;
		}
		cout << endl;
	}

	const int N = 20, k = 5;
	int mainCounter = 0;
	for (int i = 0; i < 100000; i++)
	{
		int ctr = 0;
		for (int j = 0; j < N; j++)
		{
			bool tmp = gen.generateNextBit();
			if (tmp)
				ctr++;
			else
				ctr = 0;
			if (ctr >= k)
			{
				mainCounter++;
				break;
			}
		}
	}
	cout << double(double(mainCounter) / 100000) << endl;
	cout << double(double(oneCounter) / 100000) << endl;
}