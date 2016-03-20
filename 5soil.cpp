#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <algorithm>
#include "tokenizer.h"
using namespace std;

class MassSolver
{
public:
    void addElement(const string& name, double mass)
    {
        _elementMass[name] = mass;
    }
    
    double parse(const char* str)
    {
        _expr = str;
        _curIndex = 0;
        _massStack = stack<double>();
        _levelStack = stack<int>();
        int level = 0;
        string elementName;
        int num;
        while (char c = _expr[_curIndex])
        {
            switch (c)
            {
                case ' ': case '\t': 
                    _curIndex++;
                    break;
                case '(':case '[':case '{':
                    _curIndex++;
                    level++;
                    break;
                case ')':case ']':case '}':
                {
                    _curIndex++;
                    if (level <= 0)
                    {
                        cout << "Bad expression: brace not match" << endl;
                        return -1;
                    }
                    double mass = popStack(level);
                    level--;
                    _massStack.push(mass);
                    _levelStack.push(level);
                    break;
                }
                default:
                {
                    if (tryGetElementName(elementName))
                    {
                        auto itr = _elementMass.find(elementName);
                        if (itr == _elementMass.end())
                        {
                            cout << "Unknown element: " << elementName << endl;
                            return -1;        
                        }
                        _massStack.push(itr->second);
                        _levelStack.push(level);
                    }
                    else if (tryGetNumber(num))
                    {
                        if (_massStack.empty())
                        {
                            cout << "Bad expression at number: " << num << endl;
                            return -1;        
                        }
                        double mass = _massStack.top();
                        _massStack.pop();
                        _massStack.push(mass * num);
                    }
                    else 
                    {
                        cout << "Unknown character: " << c << endl;
                        return -1;        
                    }
                }
            }
        }
        
        if (level != 0)
        {
            cout << "Bad expression: brace not match" << endl;
            return -1;
        }
        
        return popStack(0);
    }    
private:
    bool tryGetElementName(string& elementName)
    {
        char c = _expr[_curIndex];
        if (c >= 'A' && c <= 'Z')
        {
            _curIndex++;
            elementName = c;
            c = _expr[_curIndex];
            if (c >= 'a' && c <= 'z')
            {
                _curIndex++;
                elementName += c;
            }
            return true;
        }
        return false;
    }
    
    bool tryGetNumber(int& num)
    {
        char c = _expr[_curIndex];
        num = 0;
        if (c >= '0' && c <= '9')
        {
            while (c >= '0' && c <= '9')
            {
                num = num * 10 + c - '0'; 
                _curIndex++;
                c = _expr[_curIndex];
            }
            return true;
        }
        return false;
    }
    
    double popStack(int level)
    {
        double mass = 0;
        while (!_levelStack.empty() && _levelStack.top() == level)
        {
            mass += _massStack.top();
            _massStack.pop();
            _levelStack.pop();
        }
        return mass;
    }
    
    const char* _expr;
    int _curIndex;
    map<string, double> _elementMass;
    stack<double> _massStack;
    stack<int> _levelStack;
};

bool parseElement(const string& line, string& elementName, double& mass)
{
    Tokenizer tokenizer(line, "=, \t\n\r\b");
    string token = tokenizer.nextToken();
    if (token.length() == 0)
        return false;
    elementName = token;
    token = tokenizer.nextToken();
    if (token.length() == 0)
        return false;
    mass = atof(token.c_str());
    return true;
}

int main()
{
    MassSolver solver;
    do 
    {
        string line;
        getline(cin, line);
        if (line.empty())
            break;
        if (line.find('=') != string::npos)
        {
            double mass;
            string name;
            if (parseElement(line, name, mass))
            {
                solver.addElement(name, mass);    
            }
        }
        else
        {
            double mass = solver.parse(line.c_str());
            if (mass > 0)
                cout << line << " = " << mass << endl;
        }
    } while (true);

    return 0;
}