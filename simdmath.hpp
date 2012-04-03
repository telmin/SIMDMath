#ifndef SIMDMATH_HPP
#define SIMDMATH_HPP

#include <x86intrin.h>
#include <vector>

class SIMDMath
{
public:
    typedef struct float8__ {
	__m256 vec;
	float sc[8] __attribute__((aligned(32)));
    } float8_t;

    typedef float8_t float8;

public:
    explicit SIMDMath(void);

    ~SIMDMath();

    __m256 sin(const __m256& pi);
    __m256 sin(const std::vector<float>& pi);

    __m256 cos(const __m256& pi);
    __m256 cos(const std::vector<float>& pi);

    // tangen will given as sin / cos
    __m256 tan(const __m256& pi);
    __m256 tan(const std::vector<float>& pi);

private:
    void Init();

    size_t digit;
    __m256 denoms[12];
};

#endif
