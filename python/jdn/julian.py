#!/Library/Frameworks/Python.framework/Versions/3.6/bin/python3
#
# JD (Julian Day) - decimal day (including fractional time of day) since the epoch
#       12:00 on 1 January, 4713BC (-4712).
# JDN (Julian Day Number) - integer part of the Julian Day (JD) (i.e. 12:00 on
#       the given day).
#

def cdiv(a,b):
    is_neg = (a*b) < 0
    result = abs(a)//abs(b)
    if is_neg:
        result *= -1
    
    return result

# returns true if y1,m1,d1 >= y2,m2,d2
def ymd_gte(y1, m1, d1, y2, m2, d2):
    if y1 > y2:
        return True
    elif y1 < y2:
        return False

    if m1 > m2:
        return True
    elif m1 < m2:
        return False

    return d1 >= d2

#
# Convert a Gregorian date/time to a Julian Day.
# 
# source: Duffett-Smith
#
# Returns: A Julian Day value including the decimal day-time.
#       To get the Julian Day Number (JDN) take the integer part of the result.
#
def g2jd(year, month, day, hour = 0, minute = 0, second = 0):
    day = day + (hour/24) + (minute/(24*60)) + (second/(24*60*60))
    y, m, d = year, month, day

    if m == 1 or m == 2:
        y -= 1
        m += 12

    B = 0
    if ymd_gte(y, m, d, 1582, 10, 15):
        A = cdiv(y,100) 
        B = 2 - A + cdiv(A,4)

    C = 365.25 * y
    if y < 0:
        C -= 0.75

    C = int(C)

    D = int(30.6001 * (m + 1))

    return B + C + D + d + 1720994.5

#
# Convert a Gregorian calendar date to a Julian Day Number.
#
# The Julian Day Number is the Julian Date at 12:00 (noon) for the given
# gregorian calendar date.
#
def g2jdn(year, month, day):
    return jd2jdn(g2jd(year, month, int(day)))

def jd2jdn(jd):
    return int(jd + 0.5)


#
# Convert a Gregorian date to a Julian Day Number.
#
# Source: wikipedia
#
def g2jdn2(Y, M, D):
    jdn = cdiv(1461 * (Y + 4800 + cdiv(M - 14,12)), 4)
    jdn += cdiv(367 * (M -2 - (12 * cdiv(M - 14,12) )) , 12)
    jdn -= cdiv(3 * cdiv(Y + 4900 + cdiv(M - 14,12),100), 4)
    jdn += D - 32075

    return jdn

def jdn2gregorian(jdn):
    """
    y=4716    v=3
    j=1401    u=5
    m=2       s=153
    n=12      w=2
    r=4       B=274277
    p=1461    C=−38
    """

    # 1. f = J + j + (((4 × J + B) div 146097) × 3) div 4 + C
    f = jdn + 1401 + (((4 * jdn + 274277) // 146097) * 3) // 4 - 38
    # 2. e = r × f + v
    e = 4 * f + 3
    # 3. g = mod(e, p) div r
    g = (e%1461) // 4
    # 4. h = u × g + w
    h = 5 * g + 2
    # 5. D = (mod(h, s)) div u + 1
    D = ((h%153) // 5) + 1
    # 6. M = mod(h div s + m, n) + 1
    M = ((h // 153 + 2) % 12) + 1
    # 7. Y = (e div p) - y + (n + m - M) div n
    Y = (e // 1461) - 4716 + (14 - M) // 12

    return (Y,M,D)

def jd2gregorian(jd):
    jdn = int(jd + 0.5)
    day_frac = jd - jdn
    Y, M, D = jdn2gregorian(jdn)
    return (Y, M, D, day_frac)


def test1():
    cases_JD = [
            (2018, 6, 23, 6, 6, 6, 2458292.754236, 2458293, "Sun"),
            (1985, 2, 17, 6, 0, 0, 2446113.75, 2446114, "Sun"),
            (1990, 9, 18, 12, 0, 0, 2448153.0, 2448153, "Tue"),
            (1990, 9, 19, 0, 0, 0, 2448153.5, 2448154, "Wed"),
            (1990, 9, 19, 12, 0, 0, 2448154.0, 2448154, "Wed"),
            (1582, 1, 1, 12, 0, 0, 2298884.0, 2298884, "Mon"),
            (1, 1, 1, 12, 0, 0, 1721424.0, 1721424, "Sat"),
            (0, 1, 1, 12, 0, 0, 1721058.0, 1721058, "Thu")
        ]

    for y, m, d, _, _, _, _, j, _ in cases_JD:
        jdn = g2jdn(y, m, d)
        jdn2 = g2jdn2(y, m, d)

        print("{}-{}-{}: {} ({}) {}".format(y,m,d,jdn,j,jdn2))


def test2():
    low = -4712
    high = 2018

    for year in range(2018, 0, -1):
        jdn = g2jdn(year, 1, 1)
        jdn2 = g2jdn2(year, 1, 1)

        if jdn2 != jdn:
            print("{}-{}-{}: {} != {}".format(year, 1, 1, jdn2, jdn))
            break

if __name__ == "__main__":
    test1()

