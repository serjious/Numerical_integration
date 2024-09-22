#include "Interface.h"
#include <string.h>
#include <iostream>
#include <math.h>
#include <iomanip>

struct Flags
{
    bool gui;
    bool debug;
};
void checkFlag(int argc, char **argv, Flags &flags)
{
    flags.debug = false;
    flags.gui = false;
    for(int i = 0; i<argc; i++)
    {

        if(!strcmp(*(argv+i), "-g")) flags.gui = true;
        if(!strcmp(*(argv+i), "--gui")) flags.gui = true;
        if(!strcmp(*(argv+i), "-d")) flags.debug = true;
        if(!strcmp(*(argv+i), "--debug")) flags.debug = true;
    }

}


bool prefix(const char *pre, const char *str)
{
    return strncmp(pre, str, strlen(pre)) == 0;
}
void initParam(Interface* intg, int argc, char **argv)
{
    char expression[MAX_STRING];
    char method[MAX_STRING];
    double a;
    double b;
    double e;
    for(int i = 0; i<argc; i++)
    {
        if(prefix("f=", argv[i]) || prefix("F=", argv[i]))
            strcpy(expression, &argv[i][2]);
        if(prefix("m=", argv[i]) || prefix("M=", argv[i]))
            strcpy(method, &argv[i][2]);
        if(prefix("a=", argv[i]) || prefix("A=", argv[i]))
            a = strtod(&argv[i][2], NULL);
        if(prefix("b=", argv[i]) || prefix("B=", argv[i]))
            b = strtod(&argv[i][2], NULL);
        if(prefix("e=", argv[i]) || prefix("E=", argv[i]))
            e = strtod(&argv[i][2], NULL);

    }
    intg->init(expression, a, b, e, method);
}
void printFormatted(Interface *a, bool debug)
{
    int iter;
    double precision = a->getPrecision();
    int i;
    for(i = 0; ; i++)
    {
        if(precision*pow(10,i) > 1.0) break;
    }
    std::cout<<std::setprecision(i)<<a->calcIntegral(iter)<<std::endl;
    if (debug)
        std::cout<<"For "<<iter<<" iterations"<<std::endl;
}
int main(int argc, char **argv)
{

    Flags flags;
    checkFlag(argc, argv, flags);
    Interface* intg = new Interface;
    if(flags.gui)
    {
        intg->initGUI();
    }
    else
    {
        initParam(intg, argc, argv);
        printFormatted(intg, flags.debug);
    }


	return 0;
}
