#include <iostream>

#include "datetime.h"

using namespace std;

int main() {
    double jd = 2446113.75;
    DateTime ref {1985, 2, 17.25};
    DateTime dt {jd};
    cout << "ref: " << ref << endl;
    cout << " dt: " << dt << endl;
    dt = DateTime(2019,2, 24);
    cout << "weekday: " << (int) dt.weekday() << endl;
}
