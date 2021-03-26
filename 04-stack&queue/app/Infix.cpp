#include "../stack/Stack.hpp"
#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;
#define N_OPTR 9
typedef enum { ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE } Operator;

const char pri[N_OPTR][N_OPTR] = {
    /*          |------------- 当 前 运 算 符 -------------|*/
    /*           +    -    *    /    ^    !    (    )   \0 */
    /* --  + */ '>', '>', '<', '<', '<', '<', '<', '>', '>',
    /* |   - */ '>', '>', '<', '<', '<', '<', '<', '>', '>',
    /* 栈  * */ '>', '>', '>', '>', '<', '<', '<', '>', '>',
    /* 顶  / */ '>', '>', '>', '>', '<', '<', '<', '>', '>',
    /* 运  ^ */ '>', '>', '>', '>', '>', '<', '<', '>', '>',
    /* 算  ! */ '>', '>', '>', '>', '>', '>', ' ', '>', '>',
    /* 符  ( */ '<', '<', '<', '<', '<', '<', '<', '=', ' ',
    /* |   ) */ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    /* -- \0 */ '<', '<', '<', '<', '<', '<', '<', ' ', '='
};

bool isdigit(char c) { return c >= '0' && c <= '9'; }

void readNumber(char*& s, Stack<float>& opnd) {
    opnd.push((float)(*s - '0'));
    while (isdigit(*(++s)))
        opnd.push(opnd.pop() * 10 + (*s - '0'));
    if ('.' != *s)
        return;
    float fraction = 1;
    while (isdigit(*(++s)))
        opnd.push(opnd.pop() + (*s - '0') * (fraction /= 10));
}

void append(char*& RPN, float digit) {
    int n = strlen(RPN);
    char buf[64];
    if (digit != (float)(int)digit)
        sprintf(buf, "%.2f \0", digit);
    else
        sprintf(buf, "%d \0", (int)digit);
    RPN = (char*)realloc(RPN, sizeof(char) * (n + strlen(buf) + 1));
    strcat(RPN, buf);
}

void append(char*& RPN, char c) {
    int n = strlen(RPN);
    RPN = (char*)realloc(RPN, sizeof(char) * (n + 3));
    sprintf(RPN + n, "%c \0", c);
}

Operator oprt2rank(char op) {
    switch (op) {
    case '+':
        return ADD;
    case '-':
        return SUB;
    case '*':
        return MUL;
    case '/':
        return DIV;
    case '^':
        return POW;
    case '!':
        return FAC;
    case '(':
        return L_P;
    case ')':
        return R_P;
    case '\0':
        return EOE;
    default:
        exit(-1);
    }
}

char orderBetween(char op1, char op2) { return pri[oprt2rank(op1)][oprt2rank(op2)]; }

float calcu(char op, float digit) {
    if ('!' != op)
        exit(-1);
    int fac = 1, n = (int)digit;
    while (n > 1)
        fac *= n--;
    return (float)fac;
}

float calcu(float digit1, char op, float digit2) {
    switch (op) {
    case '+':
        return digit1 + digit2;
    case '-':
        return digit1 - digit2;
    case '*':
        return digit1 * digit2;
    case '/':
        return digit1 / digit1;
    case '^':
        return pow(digit1, digit2);
    default:
        exit(-1);
    }
}

float evaluate(char* s, char*& RPN) {
    Stack<float> opnd;
    Stack<char> optr;
    optr.push('\0');
    while (!optr.empty()) {
        if (isdigit(*s)) {
            readNumber(s, opnd);
            append(RPN, opnd.top());
        } else {
            switch (orderBetween(optr.top(), *s)) {
            case '<':
                optr.push(*s);
                ++s;
                break;
            case '=':
                optr.pop();
                ++s;
                break;
            case '>': {
                char op = optr.pop();
                append(RPN, op);
                if ('!' == op) {
                    float pOpnd = opnd.pop();
                    opnd.push(calcu(op, pOpnd));
                } else {
                    float pOpnd2 = opnd.pop();
                    float pOpnd1 = opnd.pop();
                    opnd.push(calcu(pOpnd1, op, pOpnd2));
                }
            } break;
            default:
                exit(-1);
            }
        }
    }
    return opnd.pop();
}

int main() {
    char s[256];
    char* RPN = (char*)malloc(sizeof(char) * 1);
    while (scanf("%s", s) == 1) {
        RPN[0] = '\0';
        cout << evaluate(s, RPN) << endl;
        cout << RPN << endl;
    }
    return 0;
}