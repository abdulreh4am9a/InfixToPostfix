#include"stack.h"
#include<string>
bool is_operator(char x) //simple function to check whether the character is operator or not
{
    return (x == '+' || x == '-' || x == '*' || x == '/' || x == '^' || x == '%');
}
int prec_of_opr(char x) //simple function to return the precedence of the operator
{
    if (x == '+' || x == '-') //+ - has least precedence
        return 1;
    else if (x == '*' || x == '/' || x == '%') //* / and % have more precedence then + and -
        return 2;
    else if (x == '^') //power operator has more precendence then all of these
        return 3;
    else
        return 0;
}
string infixToPostfix(string infix) //function to convert infix notation to postfix notation
{
    string postfix;
    stack<char> s;
    int i = 0;
    while (infix[i] != '\0') { //while the end character does not appear check each index of infix notation
        if (isdigit(infix[i]) || isalpha(infix[i])) //if the value at ith index is a digit or an alphabet then concatenate it in postfix notation
        //to check the character built in functions of isdigit and isalpha are used
        {
            postfix += infix[i];
        }
        else if (infix[i] == '(') //if the opening bracket appears we simply have to push it because it has the highest precendence so there is no need to check anything
        {
            s.push(infix[i]);
        }
        else if (infix[i] == ')') //if the opening bracket appears we have to simply pop all the operators one by one and concatenating them to postfix until the opening bracket arrives
        {
            while ((s.top() != '(') && (!s.empty()))
            {
                postfix += s.top();
                s.pop();
            }
            if (s.top() == '(') //in the end we  also have to pop the opening bracket and discarding it
            {
                s.pop();
            }
        }
        else if (is_operator(infix[i])) //if the ith element is an operator
        {
            if (s.empty()) //and the stack is empty we have to push it immediately without checking anything
            {
                s.push(infix[i]);
            }
            else //if not empty check the precedence and associativity
            {
                if (prec_of_opr(infix[i]) > prec_of_opr(s.top())) //if the arrived operator has higher precedence then the top operator at stack simply push it
                {
                    s.push(infix[i]);
                }
                else if ((prec_of_opr(infix[i]) == prec_of_opr(s.top())) && (infix[i] == '^')) //if the precedence is equal the associativity should be checked and only power operator has right to left associativity so dealing it seperately
                {
                    s.push(infix[i]);
                }
                else
                { //if both the conditions are false then whether the precedence of present operater is low or if same then the present operator is not power operator
                    while ((!s.empty()) && (prec_of_opr(infix[i]) <= prec_of_opr(s.top())))
                    {
                        if ((infix[i] == '^')) //if power operator appears simply push it because it has associativity right to left
                            s.push(infix[i]);
                        else { //if any other operator appears then pop and concatenate it to postfix notation
                            postfix += s.top();
                            s.pop();
                        }
                    }
                    s.push(infix[i]); //in the end pushing the ith element to stack
                }
            }
        }
        i++;
    } //when the infix notation is completely analysed the remaining operators on stack should be poped and concatenated to postfix
    while (!s.empty())
    {
        postfix += s.top();
        s.pop();
    }

    return postfix; //returning postfix notation
}
int main(int argc, char* argv[])
{
    string postfixNotation;
    cout << "Infix Notation: " << argv[1] << endl;
    postfixNotation = infixToPostfix(argv[1]);
    cout << "Postfix Notation: " << postfixNotation << endl;
    return 0;
}