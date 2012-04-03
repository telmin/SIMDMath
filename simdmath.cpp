#include <vector>
#include "simdmath.hpp"
#include <x86intrin.h>

SIMDMath::SIMDMath(void)
    : digit(6)
{
    Init();
}

SIMDMath::~SIMDMath()
{}

void SIMDMath::Init()
{
    const size_t num = digit * 2;

    for(size_t i = 0;i < num;++i) {
	float val = 1.0f;
	for(size_t j = 2;j <= (i+1);++j) {
	    val *= static_cast<float>(j);
	}
	denoms[i] = _mm256_set1_ps(1/val);
    }
}

__m256 SIMDMath::sin(const std::vector<float>& pi)
{
    __m256 v_pi = _mm256_loadu_ps(&pi[0]);

    return sin(v_pi);
}

__m256 SIMDMath::sin(const __m256& pi)
{
    __m256 v1  = pi;
    __m256 v2  = _mm256_mul_ps(v1,v1);
    __m256 v3  = _mm256_mul_ps(v2,v1);
    __m256 v5  = _mm256_mul_ps(v3,v2);
    __m256 v7  = _mm256_mul_ps(v5,v2);
    __m256 v9  = _mm256_mul_ps(v7,v2);
    __m256 v11 = _mm256_mul_ps(v9,v2);

    __m256 v13  = _mm256_sub_ps(v1,_mm256_mul_ps(denoms[2],v3));
    __m256 v57  = _mm256_sub_ps(_mm256_mul_ps(v5,denoms[4]),_mm256_mul_ps(v7,denoms[6]));
    __m256 v911 = _mm256_sub_ps(_mm256_mul_ps(v9,denoms[8]),_mm256_mul_ps(v11,denoms[10]));

    return _mm256_add_ps(_mm256_add_ps(v13,v57),v911);
}

__m256 SIMDMath::cos(const std::vector<float>& pi)
{
    __m256 v_pi = _mm256_loadu_ps(&pi[0]);

    return cos(v_pi);
}

__m256 SIMDMath::cos(const __m256& pi)
{
    __m256 v1  = _mm256_set1_ps(1.0f);
    __m256 v2  = _mm256_mul_ps(pi,pi);
    __m256 v4  = _mm256_mul_ps( v2,v2);
    __m256 v6  = _mm256_mul_ps( v4,v2);
    __m256 v8  = _mm256_mul_ps( v6,v2);
    __m256 v10 = _mm256_mul_ps( v8,v2);

    __m256 v12  = _mm256_sub_ps(v1,_mm256_mul_ps(v2,denoms[1]));
    __m256 v46  = _mm256_sub_ps(_mm256_mul_ps(v4,denoms[3]),_mm256_mul_ps( v6,denoms[5]));
    __m256 v810 = _mm256_sub_ps(_mm256_mul_ps(v8,denoms[7]),_mm256_mul_ps(v10,denoms[9]));

    return _mm256_add_ps(_mm256_add_ps(v12,v46),v810);
}

