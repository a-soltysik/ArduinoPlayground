#include <inttypes.h>

template<typename T, uint32_t N>
struct Array
{
    T data[N];

    const T& operator[](uint32_t at) const
    {
        return data[at];
    }

    T& operator[](uint32_t at)
    {
        return data[at];
    }

    constexpr uint32_t size() const
    {
        return N;
    }
};