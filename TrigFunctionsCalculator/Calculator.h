#pragma once
#include "Ranges.h"
#include "ErrorHandling.h"
#include <unordered_map>

constexpr double PI = 3.14159265358979323846;

/// <summary>
/// Available trigonometric functions
/// </summary>
enum Functions { SIN, COS, TAN, COT, SEC, CSC, ARCSIN, ARCCOS, ARCTAN, ARCCOT, ARCSEC, ARCCSC };

/// <summary>
/// Base class containing common logic for evaluating taylor series
/// </summary>
class Evaluator
{
private:
	int maxDepth = 10000;        ///<summary>Maximum number of terms computable</summary>

	static Result<void> validateInput(double x, double precision); ///<summary>Whether function can be computed with those inputs</summary>

protected:
	double maxValue = 1000.0;    ///<summary>Maximum absolute value before considering infinite</summary>

	Range computableRange;       ///<summary>Range over which function is defined</summary>
	Range noFallbackRange;       ///<summary>Range over which function is computed directly as taylor series</summary>
	
	virtual Result<double> fallbackStrategy(double x, double precision) = 0;   ///<summary>Strategy to bring argument into directly computable range. Reducing angle etc.</summary>
	virtual double initialTerm(double x) = 0;                                  ///<summary>First term of taylor series</summary>
	virtual double termFactor(double x, int n) = 0;                            ///<summary>Ratio between two consecutive series terms</summary>

public:
	Result<double> evaluate(double x, double precision);
};


class Sin : public Evaluator
{
private:
	Result<double> fallbackStrategy(double x, double precision) override;
	double initialTerm(double x) override;
	double termFactor(double x, int n) override;

public:
	Sin();
};

class Cos : public Evaluator
{
private:
	Result<double> fallbackStrategy(double x, double precision) override;
	double initialTerm(double x) override;
	double termFactor(double x, int n) override;

public:
	Cos();
};

class Tan : public Evaluator
{
private:
	Result<double> fallbackStrategy(double x, double precision) override;
	double initialTerm(double x) override;
	double termFactor(double x, int n) override;

public:
	Tan();
};

class Cot : public Evaluator
{
private:
	Result<double> fallbackStrategy(double x, double precision) override;
	double initialTerm(double x) override;
	double termFactor(double x, int n) override;

public:
	Cot();
};

class Sec : public Evaluator
{
private:
	Result<double> fallbackStrategy(double x, double precision) override;
	double initialTerm(double x) override;
	double termFactor(double x, int n) override;

public:
	Sec();
};

class Csc : public Evaluator
{
private:
	Result<double> fallbackStrategy(double x, double precision) override;
	double initialTerm(double x) override;
	double termFactor(double x, int n) override;

public:
	Csc();
};

class Arcsin : public Evaluator
{
private:
	Result<double> fallbackStrategy(double x, double precision) override;
	double initialTerm(double x) override;
	double termFactor(double x, int n) override;

public:
	Arcsin();
};

class Arccos : public Evaluator
{
private:
	Result<double> fallbackStrategy(double x, double precision) override;
	double initialTerm(double x) override;
	double termFactor(double x, int n) override;

public:
	Arccos();
};

class Arctan : public Evaluator
{
private:
	Result<double> fallbackStrategy(double x, double precision) override;
	double initialTerm(double x) override;
	double termFactor(double x, int n) override;

public:
	Arctan();
};

class Arccot : public Evaluator
{
private:
	Result<double> fallbackStrategy(double x, double precision) override;
	double initialTerm(double x) override;
	double termFactor(double x, int n) override;

public:
	Arccot();
};

class Arcsec : public Evaluator
{
private:
	Result<double> fallbackStrategy(double x, double precision) override;
	double initialTerm(double x) override;
	double termFactor(double x, int n) override;

public:
	Arcsec();
};

class Arccsc : public Evaluator
{
private:
	Result<double> fallbackStrategy(double x, double precision) override;
	double initialTerm(double x) override;
	double termFactor(double x, int n) override;

public:
	Arccsc();
};
