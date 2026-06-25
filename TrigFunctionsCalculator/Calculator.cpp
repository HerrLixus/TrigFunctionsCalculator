#include "Calculator.h"
#include <iostream>


Result<double> Evaluator::evaluate(double x, double precision)
{
    Result<double> res;

    if (!noFallbackRange.isInside(x))
        return fallbackStrategy(x, precision);

    double initial = initialTerm(x);
    double lastTerm = initial;
    double sum = initial;
    bool precisionFlag = false;

    for (int n = 1; n < maxDepth && !precisionFlag; n++)
    {
        lastTerm *= termFactor(x, n);

        if (abs(lastTerm) < precision)
            precisionFlag = true;

        sum += lastTerm;
    }

    if (abs(sum) > maxValue)
    {
        if (sum > 0)
            res.setValue(INFINITY);
        else
            res.setValue(-INFINITY);
    }
    else
    {
        res.setValue(sum);
    }

    if (!precisionFlag)
        res.addError(Error(CantAchievePrecision));

    return res;
}

Result<double> Evaluator::validateInput(double x, double precision) const
{
    Result<double> res;

    if (!computableRange.isInside(x))
    {
        Error error(WrongArgValue);
        error.setAllowedRange(computableRange);
        res.addError(error);
    }
          
    if (precision < 1e-10 || precision > 1.0)
        res.addError(Error(WrongPrecisionValue));

    return res;
}



Cos::Cos()
{
    noFallbackRange = Range({ RangeSegment(-4.0, true, 4.0, true) });
    computableRange = Range({ RangeSegment(-32.0, true, 32.0, true) });
}

Result<double> Cos::fallbackStrategy(double x, double precision)
{
    if (x > 0)
        return Cos::evaluate(x - 2 * PI, precision);
    else
        return Cos::evaluate(x + 2 * PI, precision);
}

double Cos::initialTerm(double x)
{
    return 1;
}

double Cos::termFactor(double x, int n)
{
    return -x * x / ((2.0 * n) * (2.0 * n - 1.0));
}




Sin::Sin()
{
    noFallbackRange = Range({ RangeSegment(-PI, true, PI, true) });
    computableRange = Range({ RangeSegment(-32, true, 32, true) });
}

Result<double> Sin::fallbackStrategy(double x, double precision)
{
    if (x > 0)
        return Sin::evaluate(x - 2 * PI, precision);
    else
        return Sin::evaluate(x + 2 * PI, precision);
}

double Sin::initialTerm(double x)
{
    return x;
}

double Sin::termFactor(double x, int n)
{
    return -x * x / ((2.0 * n) * (2.0 * n + 1.0));
}




Tan::Tan()
{
    noFallbackRange = Range({ });
    computableRange = Range({ RangeSegment(-32, true, 32, true) });
}

Result<double> Tan::fallbackStrategy(double x, double precision)
{
    Result<double> fail = Result<double>();
    fail.addError(Error(CantAchievePrecision));

    Result<double> outOfRange;
    outOfRange.addError(Error(ErrorType::WrongArgValue));

    Result<double> sinus = Sin().evaluate(x, precision / 4.0);
    Result<double> cosinus = Cos().evaluate(x, precision / 4.0);
    if (!sinus.isSuccess() || !cosinus.isSuccess())
        return fail;

    if (cosinus.getValue() == 0.0)
        return outOfRange;

    Result<double> success = Result<double>();

    double value = sinus.getValue() / cosinus.getValue();

    if (abs(value) > maxValue)
    {
        if (value > 0)
            success.setValue(INFINITY);
        else
            success.setValue(-INFINITY);
    }
    else
    {
        success.setValue(value);
    }

    return success;
}

double Tan::initialTerm(double x) { return 0.0; };
double Tan::termFactor(double x, int n) { return 0.0; };




Cot::Cot()
{
    noFallbackRange = Range({ });
    computableRange = Range({ RangeSegment(-32, true, 0, false), RangeSegment(0, false, 32, true)});
}

Result<double> Cot::fallbackStrategy(double x, double precision)
{
    Result<double> fail = Result<double>();
    fail.addError(Error(CantAchievePrecision));

    Result<double> outofRange;
    outofRange.addError(Error(WrongArgValue));

    Result<double> sinus = Sin().evaluate(x, precision / 10.0);
    Result<double> cosinus = Cos().evaluate(x, precision / 10.0);
    if (!sinus.isSuccess() || !cosinus.isSuccess())
        return fail;

    if (sinus.getValue() == 0.0)
        return outofRange;

    Result<double> success = Result<double>();
    double value = cosinus.getValue() / sinus.getValue();

    if (abs(value) > maxValue)
    {
        if (value > 0)
            success.setValue(INFINITY);
        else
            success.setValue(-INFINITY);
    }
    else
    {
        success.setValue(value);
    }
    return success;
}

double Cot::initialTerm(double x) { return 0.0; };
double Cot::termFactor(double x, int n) { return 0.0; };




Sec::Sec()
{
    noFallbackRange = Range({ });
    computableRange = Range({ RangeSegment(-32, true, 32, true) });
}

Result<double> Sec::fallbackStrategy(double x, double precision)
{
    Result<double> fail = Result<double>();
    fail.addError(Error(CantAchievePrecision));

    Result<double> outofRange;
    outofRange.addError(Error(WrongArgValue));

    Result<double> cosinus = Cos().evaluate(x, precision / 10.0);
    if (!cosinus.isSuccess())
        return fail;

    if (cosinus.getValue() == 0.0)
        return outofRange;

    Result<double> success = Result<double>();
    double value = 1.0 / cosinus.getValue();

    if (abs(value) > maxValue)
    {
        if (value > 0)
            success.setValue(INFINITY);
        else
            success.setValue(-INFINITY);
    }
    else
    {
        success.setValue(value);
    }
    return success;
}

double Sec::initialTerm(double x) { return 0.0; };
double Sec::termFactor(double x, int n) { return 0.0; };




Csc::Csc()
{
    noFallbackRange = Range({ });
    computableRange = Range({ RangeSegment(-32, true, 0, false), RangeSegment(0, false, 32, true) });
}

Result<double> Csc::fallbackStrategy(double x, double precision)
{
    Result<double> fail = Result<double>();
    fail.addError(Error(CantAchievePrecision));

    Result<double> outofRange;
    outofRange.addError(Error(WrongArgValue));

    Result<double> sinus = Sin().evaluate(x, precision / 10.0);
    if (!sinus.isSuccess())
        return fail;
    
    if (sinus.getValue() == 0.0)
        return outofRange;

    Result<double> success = Result<double>();
    double value = 1.0 / sinus.getValue();

    if (abs(value) > maxValue)
    {
        if (value > 0)
            success.setValue(INFINITY);
        else
            success.setValue(-INFINITY);
    }
    else
    {
        success.setValue(value);
    }
    return success;
}

double Csc::initialTerm(double x) { return 0.0; };
double Csc::termFactor(double x, int n) { return 0.0; };




Arcsin::Arcsin()
{
    computableRange = Range({ RangeSegment(-1.0, true, 1.0, true) });
    noFallbackRange = Range({ RangeSegment(-0.75, true, 0.75, true) });
}

Result<double> Arcsin::fallbackStrategy(double x, double precision)
{
    Result<double> fail = Result<double>();
    fail.addError(Error(CantAchievePrecision));

    Result<double> res = Arcsin().evaluate(sqrt(1.0-x*x), precision);
    if (!res.isSuccess())
        return fail;

    Result<double> success = Result<double>();

    double val = PI / 2 - res.getValue();
    if (x < 0)
        val *= -1.0;

    success.setValue(val);
    return success;
}

double Arcsin::termFactor(double x, int n)
{
    double t = 2.0 * n;
    return x * x * (t - 1.0) * (t - 1.0) / (t * t + t);
}

double Arcsin::initialTerm(double x)
{
    return x;
}




Arccos::Arccos()
{
    computableRange = Range({ RangeSegment(-1.0, true, 1.0, true) });
    noFallbackRange = Range({});
}

Result<double> Arccos::fallbackStrategy(double x, double precision)
{
    Result<double> fail = Result<double>();
    fail.addError(Error(CantAchievePrecision));

    Result<double> res = Arcsin().evaluate(x, precision);
    if (!res.isSuccess())
        return fail;

    Result<double> success = Result<double>();

    double val = PI / 2 - res.getValue();

    success.setValue(val);
    return success;
}

double Arccos::termFactor(double x, int n) { return 0.0; };

double Arccos::initialTerm(double x) { return 0.0; };




Arctan::Arctan()
{
    noFallbackRange = Range({ RangeSegment(-1.0, true, 1.0, true)});
    computableRange = Range({ RangeSegment(-32.0, true, 32.0, true) });
}

Result<double> Arctan::fallbackStrategy(double x, double precision)
{
    Result<double> fail = Result<double>();
    fail.addError(Error(CantAchievePrecision));


    Result<double> res = Arctan::evaluate(1.0/x, precision);
    if (!res.isSuccess())
        return fail;

    Result<double> success = Result<double>();

    double val = PI / 2;
    if (x < 0)
        val *= -1.0;
    val -= res.getValue();

    success.setValue(val);
    return success;
}

double Arctan::initialTerm(double x)
{
    return x;
}

double Arctan::termFactor(double x, int n)
{
    return -1.0 * x * x * (2.0 * n - 1.0) / (2.0 * n + 1.0);
}




Arccot::Arccot()
{
    noFallbackRange = Range({  });
    computableRange = Range({ RangeSegment(-32.0, true, 32.0, true) });
}

Result<double> Arccot::fallbackStrategy(double x, double precision)
{
    Result<double> fail = Result<double>();
    fail.addError(Error(CantAchievePrecision));


    Result<double> res = Arctan().evaluate(x, precision);
    if (!res.isSuccess())
        return fail;

    Result<double> success = Result<double>();
    double val = PI / 2 - res.getValue();

    success.setValue(val);
    return success;
}

double Arccot::initialTerm(double x) { return 0.0; };
double Arccot::termFactor(double x, int n) { return 0.0; };




Arcsec::Arcsec()
{
    noFallbackRange = Range({  });
    computableRange = Range({ RangeSegment(-32.0, true, -1.0, false), RangeSegment(1.0, false, 32.0, true)});
}

Result<double> Arcsec::fallbackStrategy(double x, double precision)
{
    Result<double> outOfRange;
    outOfRange.addError(Error(ErrorType::WrongArgValue));

    if (x == 0.0)
        return outOfRange;

    Result<double> fail = Result<double>();
    fail.addError(Error(CantAchievePrecision));

    Result<double> res = Arccos().evaluate(1.0 / x, precision);
    if (!res.isSuccess())
        return fail;

    Result<double> success = Result<double>();
    double val = res.getValue();

    success.setValue(val);
    return success;
}

double Arcsec::initialTerm(double x) { return 0.0; };
double Arcsec::termFactor(double x, int n) { return 0.0; };




Arccsc::Arccsc()
{
    noFallbackRange = Range({  });
    computableRange = Range({ RangeSegment(-32.0, true, -1.0, false), RangeSegment(1.0, false, 32.0, true) });
}

Result<double> Arccsc::fallbackStrategy(double x, double precision)
{
    Result<double> outOfRange;
    outOfRange.addError(Error(ErrorType::WrongArgValue));

    if (x == 0.0)
        return outOfRange;

    Result<double> fail = Result<double>();
    fail.addError(Error(CantAchievePrecision));

    Result<double> res = Arcsin().evaluate(1.0 / x, precision);
    if (!res.isSuccess())
        return fail;

    Result<double> success = Result<double>();
    double val = res.getValue();

    success.setValue(val);
    return success;
}

double Arccsc::initialTerm(double x) { return 0.0; };
double Arccsc::termFactor(double x, int n) { return 0.0; };
