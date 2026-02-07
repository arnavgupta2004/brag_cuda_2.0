
#ifndef BB_SEGSORT_EXPORT_H
#define BB_SEGSORT_EXPORT_H

#ifdef BB_SEGSORT_STATIC_DEFINE
#  define BB_SEGSORT_EXPORT
#  define BB_SEGSORT_NO_EXPORT
#else
#  ifndef BB_SEGSORT_EXPORT
#    ifdef bb_segsort_EXPORTS
        /* We are building this library */
#      define BB_SEGSORT_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define BB_SEGSORT_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef BB_SEGSORT_NO_EXPORT
#    define BB_SEGSORT_NO_EXPORT 
#  endif
#endif

#ifndef BB_SEGSORT_DEPRECATED
#  define BB_SEGSORT_DEPRECATED __declspec(deprecated)
#endif

#ifndef BB_SEGSORT_DEPRECATED_EXPORT
#  define BB_SEGSORT_DEPRECATED_EXPORT BB_SEGSORT_EXPORT BB_SEGSORT_DEPRECATED
#endif

#ifndef BB_SEGSORT_DEPRECATED_NO_EXPORT
#  define BB_SEGSORT_DEPRECATED_NO_EXPORT BB_SEGSORT_NO_EXPORT BB_SEGSORT_DEPRECATED
#endif

/* NOLINTNEXTLINE(readability-avoid-unconditional-preprocessor-if) */
#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef BB_SEGSORT_NO_DEPRECATED
#    define BB_SEGSORT_NO_DEPRECATED
#  endif
#endif

#endif /* BB_SEGSORT_EXPORT_H */
