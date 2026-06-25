#pragma once
#include <unordered_set>
#include <ostream>

class Range;

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

	friend std::ostream& operator<<(std::ostream& os, const Range& range);

public:
	RangeSegment(double min, bool minIncluded, double max, bool maxIncluded);

	double getMin() const;
	double getMax() const;

	bool operator==(const RangeSegment& s) const;
	
	bool isInside(double x) const;
};


namespace std {
	template <>
	struct hash<RangeSegment> {
		std::size_t operator()(const RangeSegment& s) const noexcept {
			// Combine the hashes of individual members
			std::size_t h1 = std::hash<double>{}(s.getMin());
			std::size_t h2 = std::hash<double>{}(s.getMax());
			return h1 ^ (h2 << 1); // Simple bit-shifting combination
		}
	};
}

/// <summary>
/// Describes collection of continuous ranges
/// </summary>
class Range
{
private:
	std::unordered_set<RangeSegment> segments_;

	friend std::ostream& operator<<(std::ostream& os, const Range& range);

public:
	Range();
	Range(std::unordered_set<RangeSegment> segments);
	Range(std::initializer_list<RangeSegment> segments);

	bool isInside(double x) const;

};