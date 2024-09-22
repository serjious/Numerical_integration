#include "NumericalIntegration.h"
#include "tinyexpr.h"
#include <string.h>
NumericalIntegration::NumericalIntegration()
{
	*integral_.expression = '\0';
	integral_.a = 0;
	integral_.b = 0;
	iterations = 0;
}
NumericalIntegration::NumericalIntegration(const char* exp,
										   double _a, double _b, int iter){
	strcpy(integral_.expression, exp);
	integral_.a = _a;
	integral_.b = _b;
	iterations = iter;
}
NumericalIntegration::~NumericalIntegration() {};

int NumericalIntegration::getIterations() const
{
    return iterations;
}
const char* NumericalIntegration::getExpression() const
{
    return integral_.expression;
}

void NumericalIntegration::setIntegral(const char* expression_, double low_, double high_)
{
    strcpy(integral_.expression, expression_);
    integral_.a = low_;
	integral_.b = high_;
}
void NumericalIntegration::setExpression(const char* expression_)
{
    strcpy(integral_.expression, expression_);
}
void NumericalIntegration::setInterval(double low_, double high_)
{
    if (low_>high_)
    {
        double tmp = low_;
        low_ = high_;
        high_ = tmp;
    }
    integral_.a = low_;
	integral_.b = high_;
}

void NumericalIntegration::setIterations(int iterations_)
{
    iterations = iterations_;
}
double NumericalIntegration::leftRiemann() const
{
    int err;
    double x;
    double result = 0.0;
    double h = (integral_.b - integral_.a) / iterations;
    te_variable var = { "x", &x };
    te_expr* value = te_compile(integral_.expression, &var, 1, &err);

    if (!err) {
        for (int i = 0; i < iterations; i++) {
            x = integral_.a + i * h;
            result += te_eval(value);
        }
        result *= h;
    }
    else {
        throw "Incorrect math expression";
    }

    te_free(value);
    return result;
}
double NumericalIntegration::rightRiemann() const
{
    int err;
    double x;
    double result = 0.0;
    double h = (integral_.b - integral_.a) / iterations;
    te_variable var = { "x", &x };
    te_expr* value = te_compile(integral_.expression, &var, 1, &err);

    if (!err) {
        for (int i = 1; i < iterations + 1; i++) {
            x = integral_.a + i * h;
            result += te_eval(value);
        }
        result *= h;
    }
    else {
        throw "incorrect math expression";
    }

    te_free(value);
    return result;
}


double NumericalIntegration::middleRiemann() const
{
    int err;
    double x;
    double result = 0.0;
    double h = (integral_.b - integral_.a) / iterations;
    te_variable var = { "x", &x };
    te_expr* value = te_compile(integral_.expression, &var, 1, &err);

    if (!err)
    {
        for (int i = 0; i < iterations; i++)
        {
            x = integral_.a + h / 2 + i * h;
            result += te_eval(value);
        }
        result *= h;
    }
    else
    {
        throw "incorrect math expression";
    }

    te_free(value);
    return result;
}

double NumericalIntegration::trapezoidal() const
{
    int err;
    double x;
    double result = 0.0;
    double h = (integral_.b - integral_.a) / iterations;
    te_variable var = { "x", &x };
    te_expr* value = te_compile(integral_.expression, &var, 1, &err);

    if (!err)
    {
		x = integral_.a;
        double f0 = te_eval(value);
		x = integral_.b;
		double fn = te_eval(value);
        for (int i = 1; i < iterations + 1; i++)
        {
			x = integral_.a + i*h;
			result += te_eval(value);
        }
		result += (f0+fn)/2;
        result *= h;
    }
    else
    {
        throw "incorrect math expression";
    }

    te_free(value);
    return result;
}

double NumericalIntegration::simpson() const
{
    int err;
    double x;
    double result = 0.0;
    double h = (integral_.b - integral_.a) / iterations;
    te_variable var = { "x", &x };
    te_expr* value = te_compile(integral_.expression, &var, 1, &err);

    if (!err)
    {
        x = integral_.a;
        double f0 = te_eval(value);
        x = integral_.b;
        double fn = te_eval(value);
        for (int i = 1; i < iterations / 2 + 1; i++) {
            x = integral_.a + h * (i * 2 - 1);
            result += 4 * te_eval(value);
        }
        for (int i = 1; i < iterations / 2; i++) {
            x = integral_.a + h * i * 2;
            result += 2 * (te_eval(value));
        }
        result += f0 + fn;
        result *= h / 3;
    }
    else
    {
        throw "incorrect math expression";
    }
    te_free(value);
    return result;
}
