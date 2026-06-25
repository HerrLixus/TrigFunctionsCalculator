#include "Ranges.h"

RangeSegment::RangeSegment(double min, bool minIncluded, double max, bool maxIncluded)
{
	min_ = min;
	minIncluded_ = minIncluded;
	max_ = max;
	maxIncluded_ = maxIncluded;
}

double RangeSegment::getMin() const
{
	return min_;
}

double RangeSegment::getMax() const
{
	return max_;
}

bool RangeSegment::operator==(const RangeSegment& s) const
{
	return min_ == s.min_ && minIncluded_ == s.minIncluded_ && max_ == s.max_ && maxIncluded_ == s.maxIncluded_;
}

bool RangeSegment::isInside(double x) const
{
	return ((x > min_ && !minIncluded_) || (x >= min_ && minIncluded_)) && ((x < max_ && !maxIncluded_) || (x <= max_ && maxIncluded_));
}

Range::Range()
{
	segments_ = std::unordered_set<RangeSegment>();
}

Range::Range(std::unordered_set<RangeSegment> segments)
{
	segments_ = segments;
}

Range::Range(std::initializer_list<RangeSegment> segments)
{
	segments_ = segments;
}

bool Range::isInside(double x) const
{
	bool flag = false;
	for (auto iter = segments_.cbegin(); iter != segments_.cend() && !flag; iter++)
		if (iter->isInside(x))
			flag = true;

	return flag;
}