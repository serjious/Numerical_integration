#pragma once
#define MAX_STRING 128

class NumericalIntegration
{
	struct Integral
	{
		char expression[MAX_STRING];
		double a;
		double b;
	} integral_;
    int iterations;
public:
	NumericalIntegration();
    NumericalIntegration(const char* expression_, double low_, double high_, int iterations_);
	~NumericalIntegration();

	int getIterations() const;
	const char* getExpression() const;
	void setIntegral(const char* expression_, double low_, double high_);
	void setExpression(const char* expression_);
	void setInterval(double low_, double high_);
    void setIterations(int iterations_);

    double leftRiemann() const;
    double rightRiemann() const;
    double middleRiemann() const;
    double trapezoidal() const;
    double simpson() const;
};
