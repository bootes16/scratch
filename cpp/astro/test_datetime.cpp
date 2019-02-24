#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <gtest/gtest.h>
#include <ctime>
#include <random>

#include "datetime.h"

using namespace std;

static tm tm_init(int y, int m, int d) {
    tm t {0};
    t.tm_year = y-1900;
    t.tm_mon  = m-1;
    t.tm_mday = d;
    return t;
}

DateTime tm2dt(tm *t) {
    DateTime d { t->tm_year + 1900, t->tm_mon + 1, t->tm_mday };
    return d;
}

struct TestVal {
    DateTime dt;
    double jd;
};

TestVal dates[] {
    { DateTime(2018,6,23,6,6,6), 2458292.754236 },
    { DateTime(1985,2,17,6,0,0), 2446113.75},
    { DateTime(1582,10,15),      2299160.5 },
    { DateTime(1582,10,4),       2299159.5 }
};

class DateTimeTestFixture: public ::testing::Test {
public:
    DateTimeTestFixture() {}

};

TEST_F (DateTimeTestFixture, Compare) {
    DateTime l { 1999, 9, 9 };
    DateTime m { 2000, 1, 1 };
    DateTime h { 2001, 10, 10 };

    EXPECT_TRUE(l < m);
    EXPECT_TRUE(h > l);
    EXPECT_TRUE(h <= h);
}

TEST_F (DateTimeTestFixture, Check) {
    auto f = [](auto& arg){
        //cout << arg.dt << " " << fixed << arg.dt.julian_day() << " " << arg.jd << endl;
        EXPECT_NEAR(arg.dt.julian_day(), arg.jd, 0.000005);
    };

    for_each(begin(dates), end(dates), f);
}

TEST_F (DateTimeTestFixture, Epoch) {
    DateTime c_epoch {1970,1,1};
    double c_jd {2440587.5};
    int c_jdn {2440588};

    tm c_tm = tm_init(1970,1,1);
    time_t c_time = timegm(&c_tm);
    ASSERT_EQ(c_time, 0);

    double jd = c_epoch.julian_day();
    int jdn = jd2jdn(jd);

    ASSERT_EQ(c_jdn, jdn);
    ASSERT_EQ(c_jd, jd);

    DateTime dt {1971,1,1};
    jd = dt.julian_day();
    jdn = jd2jdn(jd);
    
    ASSERT_EQ(jdn, c_jdn + 365);

    time_t time = c_time + (365 * 24 * 3600);
    tm *tt = gmtime(&time);
    DateTime dt2 = tm2dt(tt);
    jd = dt2.julian_day();
    jdn = jd2jdn(jdn);

    ASSERT_EQ(jdn, c_jdn + 365);
    ASSERT_NEAR(jd, c_jd + 365.0, 0.00001);
}

TEST_F (DateTimeTestFixture, Loop) {
    random_device rd;
    uniform_int_distribution<> dis(0,9999);
    const double precision {0.00001};
    DateTime dt_start {1970,1,1};
    double jd_start = dt_start.julian_day();
    tm c_tm = tm_init(1970,1,1);
    time_t c_time = timegm(&c_tm);

    ASSERT_NEAR(jd_start, 2440587.5, 0.00001);

    for (int i = 0; i < 1000; i++) {
        int ndays = dis(rd);
        time_t time = c_time + ndays * 24 * 3600;
        tm *time_tm = gmtime(&time);
        DateTime dt = tm2dt(time_tm);
        double jd = dt.julian_day();
        ASSERT_NEAR(jd - jd_start, (double) ndays, precision);
        ASSERT_EQ(jd - jd_start, (double) ndays);
    }
}

TEST_F (DateTimeTestFixture, Julian2Calendar) {
    double jd = 2446113.75;
    DateTime ref {1985, 2, 17.25};
    DateTime dt {jd};
    ASSERT_TRUE(ref == dt);
}

TEST_F (DateTimeTestFixture, JD) {
    random_device rd;
    uniform_int_distribution<> dis(0,9999);
    DateTime dt_start {1970,1,1};
    double jd_start = dt_start.julian_day();
    const double precision {0.00001};
    

    for (int i = 0; i < 1000; i++) {
        int ndays = dis(rd);
        double jd = jd_start + ndays;
        DateTime dt {jd};
        jd = dt.julian_day();
        jd -= ndays;
        dt = DateTime(jd);
        ASSERT_TRUE(dt == dt_start);
        ASSERT_NEAR(jd - jd_start, 0, precision);
    }
}

TEST_F (DateTimeTestFixture, Weekday) {
    DateTime dt {2019,2,22}; // Friday == 5
    ASSERT_EQ((int) dt.weekday(), 5);
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

