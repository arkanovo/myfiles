#include <iostream>
#include "SegmentTree.h"
#include <chrono>
using namespace std;


class Timer
{
private:
	// Псевдонимы типов используются для удобного доступа к вложенным типам
	using clock_t = chrono::high_resolution_clock;
	using second_t = chrono::duration<double, ratio<1> >;

	chrono::time_point<clock_t> m_beg;

public:
	Timer() : m_beg(clock_t::now())
	{
	}

	void reset()
	{
		m_beg = clock_t::now();
	}

	double elapsed() const
	{
		return chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};

SegmentTree::SegmentTree()
{
}

SegmentTree::~SegmentTree()
{
}

void SegmentTree::SetParam(int length, int current, int left, int right, int a[])
{
	ln = length;
	v = current;
	tl = left;
	tr = right;
	h = SignificantBit(ln);
	for (int i = 0; i < ln; i++)
		cin >> a[i];
}

void SegmentTree::BuildTree(int a[], int v, int tl, int tr) 
{
	if (tl == tr)
	{
		tree[v] = a[tl];
	}
	else
	{
		int tm = (tl + tr) / 2;
		BuildTree(a, v * 2, tl, tm);
		BuildTree(a, v * 2 + 1, tm + 1, tr);
		tree[v] = tree[v * 2] + tree[v * 2 + 1];
	}
}

int SegmentTree::GetSum(int l, int r, int v, int tl, int tr)
{
	if (l <= tl && tr <= r)
	{
		return tree[v];
	}

	if (tr < l || r < tl)
	{
		return 0;
	}

	int tm = (tl + tr) / 2;
	return GetSum(l, r, v * 2, tl, tm) + GetSum(l, r, v * 2 + 1, tm + 1, tr);
}

void SegmentTree::Build(int tl, int tr)
{
	int k = 2;
	for (tl += ln, tr += ln - 1; tl > 1; k <<= 1)
	{
		tl >>= 1, tr >>= 1;
		for (int i = tr; i >= tl; --i) Calc(i, k);
	}
}

void SegmentTree::Push(int tl, int tr)
{
	int s = h, k = 1 << (h - 1);
	for (tl += ln, tr += ln - 1; s > 0; --s, k >>= 1)
		for (int i = tl >> s; i <= tr >> s; ++i)
			if (d[i] != 0)
			{
				Apply(i << 1, d[i], k);
				Apply(i << 1 | 1, d[i], k);
				d[i] = 0;
			}
}

int SegmentTree::SignificantBit(int value)
{
	int max_int = 1 << 30;
	int power = 30;
	while (value < max_int)
	{
		max_int >>= 1;
		--power;
	}
	return power;
}

void SegmentTree::Apply(int v, int value, int levlen)
{
	a[v] = value * levlen;
	if (v < ln)
	{
		d[v] = value;
		cout << "Applying changing value at position " << v << "\n";
	}
}

void SegmentTree::Calc(int v, int levlen)
{
	if (d[v] == 0)
	{
		tree[v] = tree[v << 1] + tree[v << 1 | 1];
		cout << "No delay at position " << v << "\n";
	}
	else
	{
		tree[v] = d[v] * levlen;
		cout << "Delay detected at position " << v << "\n";
	}
}

void SegmentTree::IntervalModify(int tl, int tr, int value)
{
	Push(tl, tl + 1);
	Push(tr - 1, tr);
	bool cl = false, cr = false;
	int k = 1;
	for (tl += ln, tr += ln; tl < tr; tl >>= 1, tr >>= 1, k <<= 1)
	{
		if (cl)
			Calc(tl - 1, k);
		if (cr)
			Calc(tr, k);
		if (tl & 1)
			Apply(tl++, value, k), cl = true;
		if (tr & 1)
			Apply(--tr, value, k), cr = true;
	}
	for (--tl; tr > 0; tl >>= 1, tr >>= 1, k <<= 1)
	{
		if (cl)
			Calc(tl, k);
		if (cr && (!cl || tl != tr))
			Calc(tr, k);
	}
}

void  SegmentTree::PrintTree()
{
	cout << "\n";
	for (int i = 1; i < 4 * ln; i++)
	{
		cout << tree[i] << " ";
	}
	cout << "\n\n";
}

int main()
{
	Timer t;
    int length, current = 1, left = 0, a[1000], lborder, rborder, value;
    cin >> length >> lborder >> rborder >> value;
    SegmentTree tree;

    tree.SetParam(length, current, left, length - 1, a);
    tree.BuildTree(a, current, left, length - 1);
    tree.PrintTree();

    cout << "Sum:" << tree.GetSum(lborder, rborder - 1, current, left, length - 1) <<  "\n\n";
		
	if (value != 0)
	{
		tree.Push(lborder, rborder);
		tree.IntervalModify(lborder, rborder, value);
		tree.Build(lborder, rborder);
	}

	cout << t.elapsed();

    return 0;
}