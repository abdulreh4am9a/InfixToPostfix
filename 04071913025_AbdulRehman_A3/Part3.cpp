#include<iostream>
#include<string>
using namespace std;
template<typename T>
struct node {
    T data;
    node<T>* next;
};
template<typename T>
class stack {
    node<T>* top_ptr;
public:
    stack() {
        top_ptr = NULL;
    }
    ~stack() {
        make_empty();
    }
    void push(const T& val) {
        if (full())
            throw("Stack Overflow!");
        node<T>* temp;
        temp = new node<T>;
        temp->data = val;
        temp->next = top_ptr;
        top_ptr = temp;
    }
    void pop() {
        if (empty())
            throw("Stack Underflow!");
        node<T>* temp;
        temp = top_ptr;
        top_ptr = top_ptr->next;
        delete temp;
    }
    T top() const {
        if (empty())
            throw("Stack is empty!");
        return top_ptr->data;
    }
    bool empty() const {
        return top_ptr == NULL;
    }
    bool full() const {
        node<T>* temp;
        temp = new node<T>;
        if (temp == NULL)
            return true;
        else {
            delete temp;
            return false;
        }
    }
    void make_empty() {
        while (!empty()) {
            pop();
        }
    }
};
bool is_operator(char x)
{
    return (x == '+' || x == '-' || x == '*' || x == '/' || x == '^' || x == '%');
}
int prec_of_opr(char x)
{
    if (x == '^')
        return 3;
    else if (x == '*' || x == '/' || x == '%')
        return 2;
    else if (x == '+' || x == '-')
        return 1;
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