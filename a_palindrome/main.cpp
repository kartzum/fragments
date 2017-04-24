#include <iostream>
#include <string>
#include <cctype>

using namespace std;

bool a_palindrome(bool trace, string text) {
    ulong i = 0;
    ulong j = text.length() - 1;

    while (i <= j) {
        while (!((bool) isalpha(text[i])) && i <= j) {
            i++;
        }

        while (!((bool) isalpha(text[j])) && j >= i) {
            j--;
        }

        if (trace) {
            cout << i << ", " << text[i] << ", " << j << ", " << text[j] << endl;
        }

        if (text[i] != text[j]) {
            return false;
        }

        i++;
        j--;
    }

    return true;
}

void a_palindrome_test(bool trace) {
    cout << std::boolalpha << (bool) a_palindrome(trace, "@@ ^fto ^^f )");
    cout << endl;
    cout << std::boolalpha << (bool) a_palindrome(trace, "   r!!ot $or ^");
    cout << endl;
}

int main() {
    a_palindrome_test(true);
    return 0;
}