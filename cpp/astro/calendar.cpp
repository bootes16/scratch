#include <iostream>
#include <ctime>

#include "datetime.h"

using namespace std;

void print_cal(int ndays) {
    time_t now_time = time(nullptr);
    tm *now_t = localtime(&now_time);
    DateTime now {
        now_t->tm_year + 1900, now_t->tm_mon + 1, now_t->tm_mday,
        now_t->tm_hour, now_t->tm_min, now_t->tm_sec};
    double now_jd = now.julian_day();

    for (int d = 0; d < ndays; d++) {
        double jd = now_jd + d;
        DateTime dt {jd};
        cout << dt << " " << dt.weekday() << endl;
    }
}

int main() {
    print_cal(10);
}
