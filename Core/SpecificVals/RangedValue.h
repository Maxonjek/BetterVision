#ifndef RANGEDVALUE_H
#define RANGEDVALUE_H

#include <algorithm>
#include <iostream>
#include <limits>
#include <type_traits>

namespace RV {
    template<typename T>
    class RangedValue {
        static_assert(std::is_arithmetic_v<T>, "RangedValue requires arithmetic type");

    public:
        explicit RangedValue(T minVal = std::numeric_limits<T>::lowest(),
                    T maxVal = std::numeric_limits<T>::infinity(),
                    T value = T())
            : minVal_(minVal), maxVal_(maxVal), val_(Range(value))
        {}

        RangedValue& operator=(T val) {
            val_ = Range(val);
            return *this;
        }

        RangedValue& operator=(const RangedValue& other) {
            val_ = Range(other.val_);
            return *this;
        }

        explicit operator T() const {
            return val_;
        }

        RangedValue operator+(T rhs) const {
            return RangedValue(minVal_, maxVal_, Range(val_ + rhs));
        }

        RangedValue operator-(T rhs) const {
            return RangedValue(minVal_, maxVal_, Range(val_ - rhs));
        }

        RangedValue operator*(T rhs) const {
            return RangedValue(minVal_, maxVal_, Range(val_ * rhs));
        }

        RangedValue operator/(T rhs) const {
            return RangedValue(minVal_, maxVal_, Range(val_ / rhs));
        }

        RangedValue& operator+=(T rhs) {
            val_ = Range(val_ + rhs);
            return *this;
        }

        RangedValue& operator-=(T rhs) {
            val_ = Range(val_ - rhs);
            return *this;
        }

        RangedValue& operator*=(T rhs) {
            val_ = Range(val_ * rhs);
            return *this;
        }

        RangedValue& operator/=(T rhs) {
            val_ = Range(val_ / rhs);
            return *this;
        }

        T Get() const {
            return val_;
        }

        T GetMin() const {
            return minVal_;
        }

        T GetMax() const {
            return maxVal_;
        }

    protected:
        T Range(T val) const {
            return std::clamp(val, minVal_, maxVal_);
        }

        //template <typename U>
        //friend std::istream& operator>>(std::istream&, RangedValue<U>&);
//
        //template <typename U>
        //friend std::ostream& operator<<(std::ostream&, const RangedValue<U>&);

    private:
        T minVal_;
        T maxVal_;
        T val_;
    };
} // namespace RV

// Оператор ввода
template<typename T>
std::istream& operator>>(std::istream& is, RV::RangedValue<T>& val) {
    T temp;
    is >> temp;
    if (is) {
        val.Get() = val.Range(temp);
    }
    return is;
}

// Оператор вывода
template<typename T>
std::ostream& operator<<(std::ostream& os, const RV::RangedValue<T>& val) {
    os << val.Get();
    return os;
}

#endif // RANGEDVALUE_H
