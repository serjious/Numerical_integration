#include "Interface.h"
#include "Info.h"
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

#define STEP_ITERATION 10

enum {ENTER = 10, BACKSPACE = 127, SPACE = 32};


Interface::Interface(){}
Interface::Interface(const char* expression_, double a_, double b_, double precision_, const char* meth_)
{
    init(expression_, a_, b_, precision_, meth_);
}

void Interface::init(const char* expression_, double a_, double b_, double precision_, const char* meth_)
{
    integral.setIntegral(expression_, a_, b_);
    setPrecision(precision_);
    setMethod(meth_);
}

void Interface::GUI()
{

    int iter_;
    setExpression_GUI();
    setInterval_GUI();
    setMethod_GUI();
    setPrecision_GUI();
    printw("\n%.15f\n", calcIntegral(iter_));
    printw("for %d iterations\n", iter_);
}
void Interface::initGUI()
{
    initscr();
    noecho();
    printInformation();
    clear();
    while(true)
    {
       int y,x;
       char reply[MAX_STRING];
       GUI();
       addstr(CONTINUE);
       getyx(stdscr, y, x);
       scanString(y,x, reply);
       if(*reply != 'y') break;
       clear();
    }
    endwin();
}

double Interface::getPrecision()
{
    return precision;
}
double Interface::calcIntegral(int& interations)
{
    char intg1_method[MAX_STRING];
    switch(method){
    case L_RIENMANN:
        strcpy(intg1_method, "LR");
        break;
    case R_RIENMANN:
        strcpy(intg1_method, "RR");
        break;
    case M_RIENMANN:
        strcpy(intg1_method, "MR");
        break;
    case TRAPEZ:
        strcpy(intg1_method, "TR");
        break;
    case SIMPSON:
        strcpy(intg1_method, "SI");
        break;
    }
    int i = 0;
    double intg1;
    double intg2;
    double diff;
    do
    {
        i++;
        integral.setIterations(STEP_ITERATION*i);
        setMethod(intg1_method);
        intg1 = calcSelectMethod();

        integral.setIterations(STEP_ITERATION*(i+1));
        setMethod("SI");
        intg2 = calcSelectMethod();
        //printf("%f %f %f\n", intg1, intg2, diff);
        diff = fabs(intg1-intg2);

    } while(diff > precision);
    interations = STEP_ITERATION*i;
    return intg1;
}
double Interface::calcIntegral()
{
    int n;
    return calcIntegral(n);
}

double Interface::calcSelectMethod()
{
    try{
    switch(method){
    case L_RIENMANN:
        return integral.leftRiemann();
    case R_RIENMANN:
        return integral.rightRiemann();
    case M_RIENMANN:
        return integral.middleRiemann();
    case TRAPEZ:
        return integral.trapezoidal();
    case SIMPSON:
        return integral.simpson();
        }
    }
    catch(const char* ex)
    {
        printw("\n%s%s", "ERROR: ", ex);
        getch();
        clear();
        GUI();
    }
    return integral.simpson();
}
void Interface::setMethod(const char *meth_){
    if (!strcmp(meth_, "LR") || !strcmp(meth_, "lr")) method = L_RIENMANN;
    else if (!strcmp(meth_, "RR") || !strcmp(meth_, "rr")) method = R_RIENMANN;
    else if (!strcmp(meth_, "MR") || !strcmp(meth_, "mr")) method = M_RIENMANN;
    else if (!strcmp(meth_, "TR") || !strcmp(meth_, "tr")) method = TRAPEZ;
    else method = SIMPSON;
}
void Interface::setMethod_GUI()
{
    char meth_[MAX_STRING];
    addstr(SELECT_METHOD);
    int y, x;
    getyx(stdscr,y,x);
    addstr(METHOD_LR);
    addstr(METHOD_RR);
    addstr(METHOD_MR);
    addstr(METHOD_TR);
    addstr(METHOD_SI);
    int y_l, x_l;
    getyx(stdscr, y_l, x_l);
    move(y,x);
    scanString(y,x, meth_);
    setMethod(meth_);
    move(y_l, x_l);

}
void Interface::setInterval_GUI()
{
    char a_bord[MAX_STRING];
    char b_bord[MAX_STRING];
    addstr(INTERVAL);
    addch('[');
    int y, x;
    getyx(stdscr, y, x);
    scanDoubleString(y, x, a_bord);
    addstr(" : ");
    getyx(stdscr, y, x);
    scanDoubleString(y, x, b_bord);
    addstr("]\n\n");
    double a_ = strtod(a_bord, NULL);
    double b_ = strtod(b_bord, NULL);
    integral.setInterval(a_, b_);

}

void Interface::setPrecision(double prec_)
{
    if(prec_ > 1.0 || prec_< 0.0)
        prec_ = 0.001;
    else
        precision = prec_;
}
void Interface::setPrecision_GUI()
{
    char prec_[MAX_STRING];
    addstr(PRESICION);
    int y,x;
    getyx(stdscr, y, x);
    scanDoubleString(y, x, prec_);
    double precd = strtod(prec_, NULL);
    setPrecision(precd);
}
void Interface::setExpression_GUI()
{
    char exp[MAX_STRING];
    int curr_char;
    int y, x;
    printIntegral(0,0);
    getyx(stdscr, y, x);
    int bordX = x;
    int index = 0;
    while ((curr_char = getch()) != EOF && curr_char != ENTER)
    {
        if(curr_char != BACKSPACE && curr_char != SPACE){
            if(index == MAX_STRING - 1) break;
            mvaddch(y,x, curr_char);
            exp[index] = curr_char;
            index++;
            x++;
        }
        else if(curr_char == BACKSPACE){
            if (x == bordX) continue;
            mvdelch(y,x-1);
            exp[index-1] = '\0';
            index--;
            x--;
        }
        mvaddstr(y, x, "  dx");
        move(y, x);
        refresh();
    }
    exp[index+1] = '\0';
    integral.setExpression(exp);
    move(HI+1, 0);
}

void Interface::printBanner() const
{
    int y;
    for(y = 0; y < HB; y++){
        mvaddstr(y,0, BANNER[y]);
    }
    move(++y, 0);
}
void Interface::printInformation() const
{
    int y{0}, x{0};
    printBanner();
    addstr(HELLO);
    addstr(HOW_TO_USE);
    addstr(AUTHORS);
    addstr(BOLOGOV);
    addstr(PERINNIKOV);
    addstr(KOLYADIN);
    addstr(KUSKOV);
    addstr(SINEV);
    addstr(NEXT_STEP);
    getch();
}
void Interface::printIntegral(int y, int x) const
{
    for(int i = y; i<HI+y; i++){
        mvaddstr(i,x, INTEGRAL[i-y]);
    }
    move(HI/2, x+WI/2-1);
}
void Interface::scanString(int y, int x, char* str)
{
    getyx(stdscr, y,x);
    int bordX = x;
    int index = 0;
    int curr_char;
    while ((curr_char = getch()) != EOF && curr_char != SPACE && curr_char != ENTER)
    {
        if(curr_char != BACKSPACE){
            if(index == MAX_STRING - 1) break;
            mvaddch(y,x, curr_char);
            str[index] = curr_char;
            str[index+1] = '\0';
            index++;
            x++;
        }
        else if(curr_char == BACKSPACE){
            if (x == bordX) continue;
            mvdelch(y,x-1);
            str[index-1] = '\0';
            index--;
            x--;
        }
        move(y, x);
        refresh();
    }
}

void Interface::scanDoubleString(int y, int x, char* str)
{
    getyx(stdscr, y,x);
    int bordX = x;
    int index = 0;
    int curr_char;
    while ((curr_char = getch()) != EOF && curr_char != SPACE && curr_char != ENTER)
    {
        if(curr_char != BACKSPACE){
            if (!((curr_char>='0') && (curr_char<='9') || curr_char =='.')) continue;
            if(index == MAX_STRING - 1) break;
            mvaddch(y,x, curr_char);
            str[index] = curr_char;
            str[index+1] = '\0';
            index++;
            x++;
        }
        else if(curr_char == BACKSPACE){
            if (x == bordX) continue;
            mvdelch(y,x-1);
            str[index-1] = '\0';
            index--;
            x--;
        }
        move(y, x);
        refresh();
    }
}

