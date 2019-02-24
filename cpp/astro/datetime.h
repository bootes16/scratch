#include <iostream>
#include <iomanip>

#include "comparable.h"

using JulianDay = double;

inline int jd2jdn(double jd) {
    return int(jd + 0.5);
}

enum class Weekday { Sun, Mon, Tue, Wed, Thu, Fri, Sat };

inline std::ostream& operator<<(std::ostream& out, const Weekday w) {
    std::string name_str[] = {
    "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    out << name_str[(int)w];
    return out;
}

/*
 * DateTime class
 * Arithmetic and conversion of dates and times.
 */
class DateTime : public Comparable<DateTime> {
public:
    DateTime(int yr, int mon, int day, int hr=0, int min=0, int sec=0) : 
        yr{yr}, mon{mon}, day{day}, hr{hr}, min{min}, sec{sec} {}
    DateTime(int yr, int mon, double day);
    DateTime(const DateTime& dt) = default;
    DateTime(DateTime&& dt) = default;
    DateTime(double jd);

    DateTime operator=(const DateTime& dt) {
        yr = dt.yr; mon = dt.mon; day = dt.day;
        hr = dt.hr; min = dt.min; sec = dt.sec;
    }

    friend std::ostream& operator<<(std::ostream& out, const DateTime& dt);

    int compare(const DateTime& dt) override;

    double julian_day();
    Weekday weekday();

private:
    int yr, mon, day, hr, min, sec;
};


