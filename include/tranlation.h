#include <iostream>
#include <string>
#include <map>
#include "stack.h"

class ArithmeticExpression {

    std::map<char, int> priority { {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2} };
    enum lType { number, variable, operation, begin, end, null };
    std::string text;
    std::vector<std::pair<lType, std::string>> infix;
    std::vector<std::pair<lType, std::string>> postfix;
    std::map<std::string, double> operands;

    static bool isDigit(char c) {
        return '0' <= c && c <= '9';
    };
    static bool isOperation(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/';
    };
    static bool isMinus(char c) {
        return c == '-';
    };
    static bool isPoint(char c) {
        return c == '.';
    };
    static bool isBegin(char c) {
        return c == '(';
    };
    static bool isEnd(char c) {
        return c == ')';
    };

    static void deleteAll(std::string& str, char toDelete) {
        int spaces = 0;
        for (int i = 0; i < str.size(); i++) {
            str[i - spaces] = str[i];
            if (str[i] == toDelete) {
                spaces++;
            }
        }
        str.erase(str.size() - spaces, spaces);
    }

    void parse() {
        lType t = null;
        int b = 0;
        int allBracketsAreClosed = 0;
        for (int i = 0; i < text.size(); i++) {
            char c = text[i];
            if (c == ' ') {
                continue;
            }
            switch (t) {
            case (number):
                if (isPoint(c) || isDigit(c)) {
                    continue;
                }
                infix.emplace_back(number, text.substr(b, i - b));
                if (isEnd(c)) {
                    b = i;
                    t = end;
                }
                else if (isOperation(c)) {
                    b = i;
                    t = operation;
                }
                break;
            case (variable):
                if (isDigit(c)) {
                    continue;
                }
                infix.emplace_back(variable, text.substr(b, i - b));
                operands.insert({ text.substr(b,i - b), 0.0 });
                if (isEnd(c)) {
                    b = i;
                    t = end;
                }
                else if (isOperation(c)) {
                    b = i;
                    t = operation;
                }
                break;
            case (operation):
                infix.emplace_back(operation, text.substr(b, i - b));
                if (isBegin(c)) {
                    b = i;
                    t = begin;
                }
                else if (isDigit(c) || isPoint(c) || isMinus(c)) {
                    b = i;
                    t = number;
                }
                break;
            case (begin):
                allBracketsAreClosed++;
                infix.emplace_back(begin, text.substr(b, i - b));
                if (isBegin(c)) {
                    b = i;
                    t = begin;
                }
                else if (isDigit(c) || isPoint(c) || isMinus(c)) {
                    b = i;
                    t = number;
                }
                break;
            case (end):
                allBracketsAreClosed--;
                infix.emplace_back(end, text.substr(b, i - b));
                if (isEnd(c)) {
                    b = i;
                    t = end;
                }
                else if (isOperation(c)) {
                    b = i;
                    t = operation;
                }
                break;
            case (null):
                if (isBegin(c)) {
                    b = i;
                    t = begin;
                }
                else if (isDigit(c) || isPoint(c) || isMinus(c)) {
                    b = i;
                    t = number;
                }
                break;
            }
        }
        infix.emplace_back(t, text.substr(b, text.size() - b));
        if (t == variable) {
            operands.insert({ text.substr(b,text.size() - b), 0.0 });
        }
        if (t == end) {
            allBracketsAreClosed--;
        }
        if (t == begin) {
            allBracketsAreClosed++;
        }
    };

    void toPostfix() {
        Stack<std::pair<lType, std::string>> st;
        std::pair<lType, std::string> stackItem;
        for (auto& lexem : infix) {
            switch (lexem.first) {
            case begin:
                st.push(lexem);
                break;
            case end:
                stackItem = st.top();
                st.pop();
                while (stackItem.first != begin) {
                    postfix.emplace_back(stackItem);
                    stackItem = st.top();
                    st.pop();
                }
                break;
            case operation:
                while (!st.empty()) {
                    stackItem = st.top();
                    st.pop();
                    if (priority[lexem.second[0]] <= priority[stackItem.second[0]]) {
                        postfix.emplace_back(stackItem);
                    }
                    else {
                        st.push(stackItem);
                        break;
                    }
                }
                st.push(lexem);
                break;
            default:
                postfix.emplace_back(lexem);
            }
        }
        while (!st.empty()) {
            stackItem = st.top();
            st.pop();
            postfix.emplace_back(stackItem);
        }
    };

    void readOperands(std::istream& input, std::ostream& output) {
        output << "Enter values:" << std::endl;
        for (auto& o : operands) {
            output << o.first << " = ";
            input >> o.second;
        }
    };

public:

    ArithmeticExpression(const std::string& text) {
        this->text = text;
        deleteAll(this->text, ' ');
        parse();
        toPostfix();
    }

    std::string getInfix() { 
        return text; 
    }

    std::string getPostfix() {
        std::string postfixStr;
        for (auto& p : postfix) {
            postfixStr += p.second;
        }
        return postfixStr;
    }

    double Calculate(std::istream& input = std::cin, std::ostream& output = std::cout) {
        readOperands(input, output);
        double left, right;
        Stack<double> st;
        for (auto& lexem : postfix) {
            if (lexem.second[1] != '\0') {
                st.push(stod(lexem.second));
            }
            else {
                switch (lexem.second[0]) {
                case '+':
                    right = st.top();
                    st.pop();
                    left = st.top();
                    st.pop();
                    st.push(left + right);
                    break;
                case '-':
                    right = st.top();
                    st.pop();
                    left = st.top();
                    st.pop();
                    st.push(left - right);
                    break;
                case '*':
                    right = st.top();
                    st.pop();
                    left = st.top();
                    st.pop();
                    st.push(left * right);
                    break;
                case '/':
                    right = st.top();
                    st.pop();
                    left = st.top();
                    st.pop();
                    st.push(left / right);
                    break;
                default:
                    if (lexem.first == variable)
                        st.push(operands[lexem.second]);
                    else
                        st.push(stod(lexem.second));
                }
            }
        }
        return st.top();
    };
};