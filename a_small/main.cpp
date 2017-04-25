#include <iostream>
#include <string>
#include <stack>

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

int main() {
    const bool trace = true;
    a_small_check_braces_test(trace);
    return 0;
}