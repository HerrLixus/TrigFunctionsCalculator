#pragma once
#include <unordered_set>


/// <summary>
/// Describes continuous segment of real values
/// </summary>
class RangeSegment
{
private:
	double min_;          
	bool minIncluded_;    
	double max_;
	bool maxIncluded_;

public:
	RangeSegment(double min, bool minIncluded, double max, bool maxIncluded);
	
	bool isInside(double x);
};


/// <summary>
/// Describes collection of continuous ranges
/// </summary>
class Range
{
private:
	std::unordered_set<RangeSegment> segments_;

public:
	Range(std::unordered_set<RangeSegment> segments);
	Range(RangeSegment segments[]);

	bool isInside(double x);
};