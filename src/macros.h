#ifndef MACROS_H
#define MACROS_H

/*
 * Some useful macros...
 */
#ifdef BUFSIZ
#  define PROT_STDIO(x) PROT(x)
#else				/* BUFSIZ */
#  define PROT_STDIO(x) ()
#endif				/* BUFSIZ */

/* ANSI/K&R compatibility stuff;
 *
 * The correct way to prototype a function now is:
 *
 * foobar PROT((int, char *));
 *
 * foobar P2(int, x, char *, y) { ... }
 */
/* xlc can't handle an ANSI protoype followed by a K&R def, and varargs
 * functions must be done K&R (b/c va_dcl is K&R style) so don't prototype
 * vararg function arguments under AIX
 */
#ifdef __STDC__
#  define PROT(x) x
#  define P1(t1, v1) (t1 v1)
#  define P2(t1, v1, t2, v2) (t1 v1, t2 v2)
#  define P3(t1, v1, t2, v2, t3, v3) (t1 v1, t2 v2, t3 v3)
#  define P4(t1, v1, t2, v2, t3, v3, t4, v4) (t1 v1, t2 v2, t3 v3, t4 v4)
#  define P5(t1, v1, t2, v2, t3, v3, t4, v4, t5, v5) (t1 v1, t2 v2, t3 v3, t4 v4, t5 v5)
#  define P6(t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6) (t1 v1, t2 v2, t3 v3, t4 v4, t5 v5, t6 v6)
#  define P7(t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7) (t1 v1, t2 v2, t3 v3, t4 v4, t5 v5, t6 v6, t7 v7)
#  define VOLATILE volatile
#  define SIGNED signed
#else				/* __STDC__ */
#  define PROT(x) ()
#  define P1(t1, v1) (v1) t1 v1;
#  define P2(t1, v1, t2, v2) (v1, v2) t1 v1; t2 v2;
#  define P3(t1, v1, t2, v2, t3, v3) (v1, v2, v3) t1 v1; t2 v2; t3 v3;
#  define P4(t1, v1, t2, v2, t3, v3, t4, v4) (v1, v2, v3, v4) t1 v1; t2 v2; t3 v3; t4 v4;
#  define P5(t1, v1, t2, v2, t3, v3, t4, v4, t5, v5) (v1, v2, v3, v4, v5) t1 v1; t2 v2; t3 v3; t4 v4; t5 v5;
#  define P6(t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6) (v1, v2, v3, v4, v5, v6) t1 v1; t2 v2; t3 v3; t4 v4; t5 v5; t6 v6;
#  define P7(t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7) (v1, v2, v3, v4, v5, v6, v7) t1 v1; t2 v2; t3 v3; t4 v4; t5 v5; t6 v6; t7 v7;
#  define VOLATILE
#  define SIGNED
#endif				/* __STDC__ */

/*
 * varargs can't be prototyped portably ... *sigh*
 */
#if defined(LATTICE)
#  define PROTVARGS(x) (char *, ...)
#  define PVARGS(v) (char *v, ...)
#else
#  define PROTVARGS(x) ()
#  define PVARGS(v) (v) va_dcl
#endif

#ifndef INLINE
#  if defined(__GNUC__) && !defined(__STRICT_ANSI__) && !defined(lint)
#    define INLINE inline
#  else
#    ifdef LATTICE
#      define INLINE __inline
#    else
#      define INLINE
#    endif
#  endif
#endif

/*
   Define for MALLOC, FREE, REALLOC, and CALLOC depend upon what malloc
   package and optional wrapper is used.  This technique is used because
   overlaying system malloc with another function also named malloc doesn't
   work on most mahines that have shared libraries.  It will also let
   us keep malloc stats even when system malloc is used.

   Please refer to options.h for selecting malloc package and wrapper.
*/
#if defined (WRAPPEDMALLOC) && !defined(IN_MALLOC_WRAPPER)

#  define MALLOC(x)               wrappedmalloc(x)
#  define FREE(x)                 wrappedfree(x)
#  define REALLOC(x, y)           wrappedrealloc(x, y)
#  define CALLOC(x, y)            wrappedcalloc(x, y)
#  define XALLOC(x)               xalloc(x)
#  define DXALLOC(x, t, d)        xalloc(x)
#  define DMALLOC(x, t, d)        MALLOC(x)
#  define DREALLOC(x, y, t, d)    REALLOC(x,y)
#  define DCALLOC(x, y, t, d)     CALLOC(x,y)

#else

#  if defined(DEBUGMALLOC) && !defined(IN_MALLOC_WRAPPER)

#    define MALLOC(x)               debugmalloc(x, 0, (char *)0)
#    define DMALLOC(x, t, d)        debugmalloc(x, t, d)
#    define XALLOC(x)               debugmalloc(x, 0, (char *)0)
#    define DXALLOC(x, t, d)        debugmalloc(x, t, d)
#    define FREE(x)                 debugfree(x)
#    define REALLOC(x,y)            debugrealloc(x,y,0,(char *)0)
#    define DREALLOC(x,y,tag,desc)  debugrealloc(x,y,tag,desc)
#    define CALLOC(x,y)             debugcalloc(x,y,0,(char *)0)
#    define DCALLOC(x,y,tag,desc)   debugcalloc(x,y,tag,desc)

#  else

#    include "malloc.h"

#  endif
#endif

#ifndef MALLOC
#  define MALLOC(x)  puts("You need to specify a malloc package in options.h")
#  define FREE(x)    puts("You need to specify a malloc package in options.h")
#  define REALLOC(x) puts("You need to specify a malloc package in options.h")
#  define CALLOC(x)  puts("You need to specify a malloc package in options.h")
#endif

#ifdef DEBUG
#  define IF_DEBUG(x) x
#  define DEBUG_CHECK(x, y) if (x) fatal(y)
#  define DEBUG_CHECK1(x, y, a) if (x) fatal(y, a)
#  define DEBUG_CHECK2(x, y, a, b) if (x) fatal(y, a, b)
#else
#  define IF_DEBUG(x) 
#  define DEBUG_CHECK(x, y)
#  define DEBUG_CHECK1(x, y, a)
#  define DEBUG_CHECK2(x, y, a, b)
#endif

#define COPY2(x, y)      ((char *)(x))[0] = ((char *)y)[0]; \
                         ((char *)(x))[1] = ((char *)y)[1]
#define LOAD2(x, y)      ((char *)&(x))[0] = *y++; \
                         ((char *)&(x))[1] = *y++
#define STORE2(x, y)     *x++ = ((char *)(&y))[0]; \
                         *x++ = ((char *)(&y))[1]

#define COPY4(x, y)      ((char *)(x))[0] = ((char *)y)[0]; \
                         ((char *)(x))[1] = ((char *)y)[1]; \
                         ((char *)(x))[2] = ((char *)y)[2]; \
                         ((char *)(x))[3] = ((char *)y)[3]
#define LOAD4(x, y)      ((char *)&(x))[0] = *y++; \
                         ((char *)&(x))[1] = *y++; \
                         ((char *)&(x))[2] = *y++; \
                         ((char *)&(x))[3] = *y++
#define STORE4(x, y)     *x++ = ((char *)(&y))[0]; \
                         *x++ = ((char *)(&y))[1]; \
                         *x++ = ((char *)(&y))[2]; \
                         *x++ = ((char *)(&y))[3]

#define COPY8(x, y)      ((char *)(x))[0] = ((char *)y)[0]; \
                         ((char *)(x))[1] = ((char *)y)[1]; \
                         ((char *)(x))[2] = ((char *)y)[2]; \
                         ((char *)(x))[3] = ((char *)y)[3]; \
                         ((char *)(x))[4] = ((char *)y)[4]; \
                         ((char *)(x))[5] = ((char *)y)[5]; \
                         ((char *)(x))[6] = ((char *)y)[6]; \
                         ((char *)(x))[7] = ((char *)y)[7]
#define LOAD8(x, y)      ((char *)&(x))[0] = *y++; \
                         ((char *)&(x))[1] = *y++; \
                         ((char *)&(x))[2] = *y++; \
                         ((char *)&(x))[3] = *y++; \
                         ((char *)&(x))[4] = *y++; \
                         ((char *)&(x))[5] = *y++; \
                         ((char *)&(x))[6] = *y++; \
                         ((char *)&(x))[7] = *y++;
#define STORE8(x, y)     *x++ = ((char *)(&y))[0]; \
                         *x++ = ((char *)(&y))[1]; \
                         *x++ = ((char *)(&y))[2]; \
                         *x++ = ((char *)(&y))[3]; \
                         *x++ = ((char *)(&y))[4]; \
                         *x++ = ((char *)(&y))[5]; \
                         *x++ = ((char *)(&y))[6]; \
                         *x++ = ((char *)(&y))[7]

#if SIZEOF_SHORT == 2
#define COPY_SHORT(x, y) COPY2(x,y)
#define LOAD_SHORT(x, y) LOAD2(x,y)
#define STORE_SHORT(x, y) STORE2(x,y)
#else
shorts of size other than 2 not implemented
#endif

#if SIZEOF_INT == 4
#define COPY_INT(x, y) COPY4(x,y)
#define LOAD_INT(x, y) LOAD4(x,y)
#define STORE_INT(x, y) STORE4(x,y)
#else
ints of size other than 4 not implemented
#endif

#if SIZEOF_FLOAT == 4
#define COPY_FLOAT(x, y) COPY4(x,y)
#define LOAD_FLOAT(x, y) LOAD4(x,y)
#define STORE_FLOAT(x, y) STORE4(x,y)
#else
floats of size other than 4 not implemented
#endif

#if SIZEOF_PTR == 4
#define COPY_PTR(x, y) COPY4(x,y)
#define LOAD_PTR(x, y) LOAD4(x,y)
#define STORE_PTR(x, y) STORE4(x,y)
#elif SIZEOF_PTR == 8
#define COPY_PTR(x, y) COPY8(x,y)
#define LOAD_PTR(x, y) LOAD8(x,y)
#define STORE_PTR(x, y) STORE8(x,y)
#else
pointers of size other than 4 or 8 not implemented
#endif

#ifndef _FUNC_SPEC_
char *string_copy PROT((char *));
char *xalloc PROT((int));
#endif

#endif
