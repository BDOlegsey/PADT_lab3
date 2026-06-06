#ifndef LAB2_BIT_H
#define LAB2_BIT_H
namespace lab2 {
struct Bit {
    bool value;
    Bit() : value(false) {}
    explicit Bit(bool v) : value(v) {}
    bool operator==(const Bit& o) const { return value == o.value; }
    bool operator!=(const Bit& o) const { return value != o.value; }
};
}  // namespace lab2
#endif
