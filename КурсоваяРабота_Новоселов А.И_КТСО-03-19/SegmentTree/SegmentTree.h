#pragma once
#include <iostream>

class SegmentTree
{
public:
	SegmentTree();
	~SegmentTree();
	void SetParam(int, int, int, int, int[]);
	void BuildTree(int[], int, int, int);
	int GetSum(int, int, int, int, int);
	void Build(int, int);
	void Push(int, int);
	void IntervalModify(int, int, int);
	void PrintTree();
private:
	void Calc(int, int);
	void Apply(int, int, int);
	int SignificantBit(int);
	int ln, v, tl, tr, a[1000] = { 0 }, tree[4000] = { 0 }, h, d[1000] = { 0 };
};