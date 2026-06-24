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

	float getMin() const;
	float getMax() const;

	bool operator==(const RangeSegment& s) const;
	
	bool isInside(double x);
};


namespace std {
	template <>
	struct hash<RangeSegment> {
		std::size_t operator()(const RangeSegment& s) const noexcept {
			// Combine the hashes of individual members
			std::size_t h1 = std::hash<float>{}(s.getMin());
			std::size_t h2 = std::hash<float>{}(s.getMax());
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

public:
	Range(std::unordered_set<RangeSegment> segments);
	Range(RangeSegment segments[]);

	bool isInside(double x);
};