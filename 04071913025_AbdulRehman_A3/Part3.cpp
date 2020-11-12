#include"stack.h"
#include<string>
bool is_operator(char x)
{
    return (x == '+' || x == '-' || x == '*' || x == '/' || x == '^' || x == '%');
}
int prec_of_opr(char x)
{
    if (x == '+' || x == '-')
        return 1;
    else if (x == '*' || x == '/' || x == '%')
        return 2;
    else if (x == '^')
        return 3;
    else
        return 0;
}
string infixToPostfix(string infix)
{
    string postfix;
    stack<char> s;
    for (int i = 0;i < infix.length();i++)
    {
        if (isdigit(infix[i]) || isalpha(infix[i]))
        {
            postfix += infix[i];
        }
        else if (infix[i] == '(')
        {
            s.push(infix[i]);
        }
        else if (infix[i] == ')')
        {
            while ((s.top() != '(') && (!s.empty()))
            {
                char temp = s.top();
                postfix += temp;
                s.pop();
            }
            if (s.top() == '(')
            {
                s.pop();
            }
        }
        else if (is_operator(infix[i]))
        {
            if (s.empty())
            {
                s.push(infix[i]);
            }
            else
            {
                if (prec_of_opr(infix[i]) > prec_of_opr(s.top()))
                {
                    s.push(infix[i]);
                }
                else if ((prec_of_opr(infix[i]) == prec_of_opr(s.top())) && (infix[i] == '^'))
                {
                    s.push(infix[i]);
                }
                else
                {
                    while ((!s.empty()) && (prec_of_opr(infix[i]) <= prec_of_opr(s.top())))
                    {
                        if ((infix[i] == '^'))
                            s.push(infix[i]);
                        else {
                            postfix += s.top();
                            s.pop();
                        }
                    }
                    s.push(infix[i]);
                }
            }
        }
    }
    while (!s.empty())
    {
        postfix += s.top();
        s.pop();
    }

    return postfix;
}
int main(int argc, char* argv[])
{
    string postfixNotation;
    cout << "Infix Notation: " << argv[1] << endl;
    postfixNotation = infixToPostfix(argv[1]);
    cout << "Postfix Notation: " << postfixNotation << endl;
    return 0;
}