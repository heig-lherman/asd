#ifndef SOME_BITS
#define SOME_BITS

template<typename T>
class SomeBits {
    size_t shift;
    T mask;
public:
    SomeBits(size_t nombreDeBits, size_t part)
            : shift(part * nombreDeBits),
              mask((T(1u) << nombreDeBits) - T(1u)) {

    }
    T operator()(T const& t) {
        return T(mask & (t >> shift));
    }
};

#endif