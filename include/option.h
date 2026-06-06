#ifndef LAB2_OPTION_H
#define LAB2_OPTION_H

#include "errors.h"

namespace lab2 {

template <class T>
class Option {
public:
    Option() : has_value_(false), value_() {}
    explicit Option(const T& value) : has_value_(true), value_(value) {}

    bool HasValue() const { return has_value_; }
    const T& Value() const {
        if (!has_value_) throw NoneValueAccess();
        return value_;
    }

private:
    bool has_value_;
    T    value_;
};

}  // namespace lab2

#include "option.tpp"

#endif
