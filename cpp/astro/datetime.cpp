#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cassert>

#include "datetime.h"

using namespace std;

/*
 * Conversions
 */
struct HMS {
    int hr;
    int min;
    int sec;
};

inline double hms2days(int h, int m, double s) {
    return (double) h / 24 + (double) m / (24 * 60) + s / (24 * 3600);
}

inline double hms2days(int h, int m, int s) {
    return hms2days(h, m, (double) s);
}

inline int hms2secs(int h, int m, int s) {
    return h * 3600 + m * 60 + s;
}

HMS day2hms(double day) {
    HMS hms{0};

    hms.sec = int(day * 24 * 3600);
    hms.hr = hms.sec / 3600;
    hms.sec %= 3600;
    hms.min = hms.sec / 60;
    hms.sec %= 60;
    
    return hms;
};

ostream& operator<<(ostream& out, const DateTime& dt) {
    out << setw(4) << dt.yr << "-" << setw(2) << dt.mon << "-" << setw(2) << dt.day;
    out << " ";
    out << setw(2) << dt.hr << ":" << setw(2) << dt.min << ":" << setw(2) << dt.sec;
    return out;
}

DateTime::DateTime(int yr, int mon, double day) {
    this->yr = yr;
    this->mon = mon;
    this->day = int(day);
    day -= double(this->day);
    HMS hms = day2hms(day);
    this->hr = hms.hr;
    this->min = hms.min;
    this->sec = hms.sec;
}

/*
 * Implement the compare function for DateTime to support comparable.
 */
int DateTime::compare(const DateTime& dt) {
    int result = 
        (this->yr << 16 | this->mon << 8 | this->day)
        -
        (dt.yr << 16 | dt.mon << 8 | dt.day);

    if (result == 0)
        result =
            hms2secs(this->hr, this->min, this->sec)
            -
            hms2secs(dt.hr, dt.min, dt.sec);

    return result < 0 ? -1 : result > 0 ? 1 : 0;
}

/*
 * Convert a Gregorian date/time to a Julian Day.
 *
 * source: Duffett-Smith
 *
 * Returns: A Julian Day value including the decimal day-time.
 *       To get the Julian Day Number (JDN) take the integer part of the result.
 */
double DateTime::julian_day() {
    double df = hms2days(this->hr, this->min, this->sec);
    df += (double) this->day;
    int y = this->yr;
    int m = this->mon;

    if (m == 1 || m == 2) {
        y -= 1;
        m += 12;
    }

    int B = 0;
    if (*this >= DateTime(1582, 10, 15)) {
        int A = y/100;
        B = 2 - A + (A/4);
    }

    double Cf = 365.25 * (double)y;
    if (y < 0) {
        Cf -= 0.75;
    }

    int C = (int)Cf;

    int D = (int)(30.6001 * (double)(m + 1));

    return (double)(B + C + D) + df + 1720994.5;
}


/*
 * Juliand Day to Calendar Date
 * source: Duffet-Smith
 */
DateTime::DateTime(double jd) {
    jd += 0.5;
    int i = (int) jd;
    double F = jd - (double) i;
    int b = i;

    if (i > 2299160) {
        int a = (int) ( ((double) i - 1867216.25) / 36524.25 );
        b = i + 1 + a - (int) (a/4.0);
    }

    int c = b + 1524;
    int d = (int) ((c - 122.1) / 365.25);
    int e = (int) (365.25 * d);
    int g = (int) ((c-e) / 30.6001);

    // Fractional day of the month.
    double Day = c - e + F - (int) (30.6001 * g);
    day = (int) Day;
    Day -= day;

    mon = g < 14 ? g - 1 : g - 13;
    yr = mon > 2 ? d - 4716 : d - 4715;
        
    HMS hms = day2hms(Day);
    hr = hms.hr;
    min = hms.min;
    sec = hms.sec;
}

Weekday DateTime::weekday() {
    double jd = this->julian_day();
    double a = (jd + 1.5) / 7;
    int a_i = (int) a;
    double a_frac = a - a_i;
    return (Weekday) (int) (a_frac * 7 + 0.5);
}

