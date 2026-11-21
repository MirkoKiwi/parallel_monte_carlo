#ifndef PMC_PLATFORM_HPP
#define PMC_PLATFORM_HPP

#if defined(__CUDACC__)
#    define PMC_HD __host__ __device__
#    define PMC_H __host__
#    define PMC_D __device__
#else
#    define PMC_HD
#    define PMC_H
#    define PMC_D
#endif

#if defined(__CUDACC__)
#    define PMC_FORCE_INLINE __forceinline__
#elif defined(_MSC_VER)
#    define PMC_FORCE_INLINE __forceinline
#elif defined(__GNUC__) || defined(__clang__)
#    define PMC_FORCE_INLINE inline __attribute__((always_inline))
#else
#    define PMC_FORCE_INLINE inline
#endif

#endif  // PMC_PLATFORM_HPP