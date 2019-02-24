#include <iostream>
#include <iomanip>

#ifndef COMPARABLE_H
#define COMPARABLE_H

/*
 * Comparable base class.
 */
template <class T>
class Comparable {
public:
    Comparable() {}
    ~Comparable() = default;

    virtual int compare(const T& t) = 0;

    bool operator<(const T& t) {
        return this->compare(t) < 0 ? true : false;
    }

    bool operator>(const T& t) {
        return this->compare(t) > 0 ? true : false;
    }

    bool operator==(const T& t) {
        return !(*this > t || *this < t);
    }

    bool operator!=(const T& t) {
        return !(*this == t);
    }

    bool operator<=(const T& t) {
        return *this < t || *this == t;
    }

    bool operator>=(const T& t) {
        return *this > t || *this == t;
    }
};

#endif /* COMPARABLE_H */
