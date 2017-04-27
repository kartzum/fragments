#include <iostream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

bool a_small_check_braces(bool trace, string text) {
    stack<char> stack;
    long i = 0;
    const long n = text.length();
    while (i < n) {
        const char c = text[i];
        if ('(' == c) {
            stack.push(c);
        } else if (')' == c) {
            if (stack.size() > 0) {
                if ('(' == stack.top()) {
                    stack.pop();
                }
            } else {
                stack.push(c);
            }
        }
        i++;
    }

    return stack.size() == 0;
}

void a_small_check_braces_test(bool trace) {
    cout << boolalpha << a_small_check_braces(trace, "( ( () ) )") << endl;
    cout << boolalpha << a_small_check_braces(trace, "(") << endl;
    cout << boolalpha << a_small_check_braces(trace, ")") << endl;
    cout << boolalpha << a_small_check_braces(trace, "(( (( ))") << endl;
    cout << boolalpha << a_small_check_braces(trace, "((  )") << endl;
}

long a_small_reverse_polish_notation_priority(char o) {
    switch (o) {
        case '*':
            return 3;
        case '+':
        case '-':
            return 2;
        case '(':
            return 1;
        default:
            return 0;
    }
}

void a_small_reverse_polish_notation_trace(string comment, string *r, vector<char> &o) {
    cout << comment << ". result: " << *r << ". stack: ";
    for (vector<char>::const_iterator i = o.begin(); i != o.end(); i++) {
        cout << *i << ", ";
    }
    cout << endl;
}

string *a_small_reverse_polish_notation(bool trace, string text) {
    string *r = new string;
    vector<char> o;
    for (long i = 0; i < text.length(); i++) {
        const char c = text[i];
        if (c >= 'a' && c <= 'z') {
            r->push_back(c);
            if (trace) {
                a_small_reverse_polish_notation_trace("variable", r, o);
            }
        } else if (c == '+' || c == '-' || c == '*') {
            if (o.empty()) {
                o.push_back(c);
                if (trace) {
                    a_small_reverse_polish_notation_trace("operator. empty", r, o);
                }
            } else if (a_small_reverse_polish_notation_priority(o.back()) <
                       a_small_reverse_polish_notation_priority(c)) {
                o.push_back(c);
                if (trace) {
                    a_small_reverse_polish_notation_trace("operator. high-priority", r, o);
                }
            } else {
                while (!o.empty() && a_small_reverse_polish_notation_priority(o.back()) >=
                                     a_small_reverse_polish_notation_priority(c)) {
                    r->push_back(o.back());
                    o.pop_back();
                }
                o.push_back(c);
                if (trace) {
                    a_small_reverse_polish_notation_trace("operator. low-priority", r, o);
                }
            }
        } else if (c == '(') {
            o.push_back(c);
            if (trace) {
                a_small_reverse_polish_notation_trace("operator. (", r, o);
            }
        } else if (c == ')') {
            if (trace) {
                a_small_reverse_polish_notation_trace("operator. ). start", r, o);
            }
            while (o.back() != '(') {
                r->push_back(o.back());
                o.pop_back();
            }
            o.pop_back();
            if (trace) {
                a_small_reverse_polish_notation_trace("operator. )", r, o);
            }
        }
    }
    while (!o.empty()) {
        r->push_back(o.back());
        o.pop_back();
    }
    return r;
}

void a_small_reverse_polish_notation_test(bool trace) {
    string *r1 = a_small_reverse_polish_notation(trace, "(a+b)*(c+d)-e");
    cout << *r1 << endl;
    delete r1;
}

int main() {
    const bool trace = true;
    a_small_check_braces_test(trace);
    a_small_reverse_polish_notation_test(trace);
    return 0;
}