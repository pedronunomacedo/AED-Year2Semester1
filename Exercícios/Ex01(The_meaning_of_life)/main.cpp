
#include <iostream>

using namespace std;

int main() {
    int n, s;

    cin >> n;
    int count = 0;
    for (int i = 0; i < n; i++) {
        cin >> s;
        if (s == 42) count++;
    }

    cout << count << endl;

    return 0;
}