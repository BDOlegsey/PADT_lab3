#ifndef LAB2_BIT_SEQUENCE_H
#define LAB2_BIT_SEQUENCE_H
#include "bit.h"
#include "array_sequence.h"
namespace lab2 {
class BitSequence : public MutableArraySequence<Bit> {
public:
    BitSequence() = default;
    ~BitSequence() override = default;
};
}  // namespace lab2
#endif
