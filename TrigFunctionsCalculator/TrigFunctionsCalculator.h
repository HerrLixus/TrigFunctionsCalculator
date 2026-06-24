#pragma once
#include "Ranges.h"
#include "ErrorHandling.h"

/// <summary>
/// Base class containing common logic for evaluating taylor series
/// </summary>
class Evaluator
{
private:
	int maxDepth = 10000;        ///<summary>Maximum number of terms computable</summary>
	double maxValue = 1000.0;    ///<summary>Maximum absolute value before considering infinite</summary>

	static Result<void> validateInput(double x, double precision); ///<summary>Whether function can be computed with those inputs</summary>

protected:
	Range computableRange;       ///<summary>Range over which function is defined</summary>
	Range noFallbackRange;       ///<summary>Range over which function is computed directly as taylor series</summary>
	
	virtual double fallbackStrategy(double x, double precision);   ///<summary>Strategy to bring argument into directly computable range. Reducing angle etc.</summary>
	virtual double initialTerm(double x);                          ///<summary>First term of taylor series</summary>
	virtual double termFactor(double x, int n);                    ///<summary>Ratio between two consecutive series terms</summary>

public:
	static Result<double> evaluate(double x, double precision);
};


class Sin : Evaluator
{
private:
	double fallbackStrategy(double x, double precision) override;
	double initialTerm(double x) override;
	double termFactor(double x, int n) override;
};

class Cos : Evaluator
{
private:
	double fallbackStrategy(double x, double precision) override;
	double initialTerm(double x) override;
	double termFactor(double x, int n) override;
};

class Tan : Evaluator
{
private:
	double fallbackStrategy(double x, double precision) override;
	double initialTerm(double x) override;
	double termFactor(double x, int n) override;
};

class Cot : Evaluator
{
private:
	double fallbackStrategy(double x, double precision) override;
	double initialTerm(double x) override;
	double termFactor(double x, int n) override;
};

class Sec : Evaluator
{
private:
	double fallbackStrategy(double x, double precision) override;
	double initialTerm(double x) override;
	double termFactor(double x, int n) override;
};

class Csc : Evaluator
{
private:
	double fallbackStrategy(double x, double precision) override;
	double initialTerm(double x) override;
	double termFactor(double x, int n) override;
};

class Arcsin : Evaluator
{
private:
	double fallbackStrategy(double x, double precision) override;
	double initialTerm(double x) override;
	double termFactor(double x, int n) override;
};

class Arccos : Evaluator
{
private:
	double fallbackStrategy(double x, double precision) override;
	double initialTerm(double x) override;
	double termFactor(double x, int n) override;
};

class Arctan : Evaluator
{
private:
	double fallbackStrategy(double x, double precision) override;
	double initialTerm(double x) override;
	double termFactor(double x, int n) override;
};

class Arccot : Evaluator
{
private:
	double fallbackStrategy(double x, double precision) override;
	double initialTerm(double x) override;
	double termFactor(double x, int n) override;
};

class Arcsec : Evaluator
{
private:
	double fallbackStrategy(double x, double precision) override;
	double initialTerm(double x) override;
	double termFactor(double x, int n) override;
};

class Arccsc : Evaluator
{
private:
	double fallbackStrategy(double x, double precision) override;
	double initialTerm(double x) override;
	double termFactor(double x, int n) override;
};