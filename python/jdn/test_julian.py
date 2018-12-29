#!/Library/Frameworks/Python.framework/Versions/3.6/bin/python3

import unittest
import julian

class TestJulian(unittest.TestCase):
    def setUp(self):
        self.cases_JD = [
            (2018, 6, 23, 6, 6, 6, 2458292.754236, 2458293, "Sun"),
            (1985, 2, 17, 6, 0, 0, 2446113.75, 2446114, "Sun"),
            (1990, 9, 18, 12, 0, 0, 2448153.0, 2448153, "Tue"),
            (1990, 9, 19, 0, 0, 0, 2448153.5, 2448154, "Wed"),
            (1990, 9, 19, 12, 0, 0, 2448154.0, 2448154, "Wed")
        ]

    def test_ymd_gte(self):
        cases_True = [
            (-1776, 7, 7, -1777, 7, 7),
            (-1777, 7, 7, -1777, 7, 7),
            (1777, 7, 7, -1777, 7, 7),
            (1999, 9, 9, 1999, 9, 9),
            (1999, 9, 10, 1999, 9, 9),
            (1999, 10, 9, 1999, 9, 9),
            (2000, 9, 9, 1999, 9, 9),
            (1999, 10, 8, 1999, 9, 9),
            (2000, 8, 8, 1999, 9, 9)
            ]

        for y1, m1, d1, y2, m2, d2 in cases_True:
            self.assertTrue(julian.ymd_gte(y1, m1, d1, y2, m2, d2))

        cases_False = [
            (1999, 9, 8, 1999, 9, 9),
            (1999, 8, 10, 1999, 9, 9),
            (-1999, 9, 0, -1999, 9, 9),
            (-2000, 9, 5, -1999, 9, 5)
        ]

        for y1, m1, d1, y2, m2, d2 in cases_False:
            self.assertFalse(julian.ymd_gte(y1, m1, d1, y2, m2, d2))

    def test_g2jd(self):
        for yr, mo, dy, hr, mi, sc, jd_ref, jdn_ref, dow in self.cases_JD:
            result = julian.g2jd(yr, mo, dy, hr, mi, sc)
            jdn = int(result)
            frac_part = int((result - jdn) * 1000000)
            result = (frac_part / 1000000) + jdn

            self.assertEqual(result, jd_ref)

    def test_g2jdn(self):
        for yr, mo, dy, hr, mi, sc, jd_ref, jdn_ref, dow in self.cases_JD:
            result = julian.g2jdn(yr, mo, dy)

            self.assertEqual(result, jdn_ref)

    def test_g2jdn2(self):
        for yr, mo, dy, hr, mi, sc, jd_ref, jdn_ref, dow in self.cases_JD:
            result = julian.g2jdn2(yr, mo, dy)

            self.assertEqual(result, jdn_ref)

if __name__ == '__main__':
    unittest.main()
        
