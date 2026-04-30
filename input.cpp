#include <iostream>
#include <limits>

using namespace std;

int suma(int x, int y) {
    return x + y;
}
int main() {
    int a, b;
    cout << "Enter two integers: ";
    cin >> a >> b;
    cout << "You entered: " << a << " and " << b << endl;
    cout << "Sum: " << suma(a, b) << endl;
    return 0;
}