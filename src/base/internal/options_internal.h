#ifndef _BASE_INTERNAL_OPTIONS_INTERNAL_H
#define _BASE_INTERNAL_OPTIONS_INTERNAL_H

/* DO NOT MODIFY:  Everything in here is either very internal to the driver or
 * planned to be removed. You should not depends on any of the values here.
 */

/* You may optionally choose one (or none) of these malloc wrappers.  These
 * can be used in conjunction with any of the above malloc packages.
 *
 * DEBUGMALLOC:
 *   * Statistics on precisely how much memory has been malloc'd.
 *   * Incurs a fair amount of overhead (both memory and CPU)
 */
#undef DEBUGMALLOC

/* The following add certain bells and whistles to malloc: */

/* DEBUGMALLOC_EXTENSIONS: defining this (in addition to DEBUGMALLOC) enables
 * the set_malloc_mask(int) and debugmalloc(string,int) efuns.  These two
 * efuns basically allow you to cause certain malloc's and free's (with tags
 * selected by a specified mask) to print debug information (addr, tag,
 * description, size) to stdio (in the shell that invoked the driver) or to a
 * file.  Not defining this does reduce the overhead of DEBUGMALLOC from 16
 * bytes per malloc down to 8.  This macro has no effect if DEBUGMALLOC isn't
 * defined.
 */
#undef DEBUGMALLOC_EXTENSIONS

/* CHECK_MEMORY: defining this (in addition to DEBUGMALLOC and
 * DEBUGMALLOC_EXTENSIONS) causes the driver to check for memory
 * corruption due to writing before the start or end of a block.  This
 * also adds the check_memory() efun.  Takes a considerable ammount
 * more memory.  Mainly for debugging.
 */
#undef CHECK_MEMORY

/* APPLY_CACHE_BITS: defines the number of bits to use in the func lookup cache
 *   (in interpret.c).
 *
 *   22 bites : (1  << 22) * (3 * 8 + 2 * 2) ~= 112MB.
 */
#define APPLY_CACHE_BITS 22

/* NO_BUFFER_TYPE: if this is #define'd then LPC code using the 'buffer'
 *   type won't be allowed to compile (since the 'buffer' type won't be
 *   recognized by the lexer).
 */
#undef NO_BUFFER_TYPE

/* ARRAY_RESERVED_WORD: If this is defined then the word 'array' can
 *   be used to define arrays, as in:
 *
 * int array x = ({ .... });
 *
 * A side effect is that 'array' cannot be a variable or function name.
 */
#undef ARRAY_RESERVED_WORD

/* REF_RESERVED_WORD: If this is defined then the word 'ref' can be
 *   used to pass arguments to functions by value.  Example:
 *
 * void inc(int ref x) {
 *     x++;
 * }
 *
 * ... y = 1; inc(ref y); ...
 *
 * A side effect is that 'ref' cannot be a variable or function name.
 *
 * Note: ref must be used in *both* places; this is intentional.  It protects
 * against passing references to routines which don't intend to return values
 * through their arguments, and against forgetting to pass a reference
 * to a function which wants one (or accidentally having a variable modified!)
 */
#define REF_RESERVED_WORD

/* use class keyword for lpc structs */
#define STRUCT_CLASS
/* use struct keyword for lpc structs */
#define STRUCT_STRUCT

/* supress warnings about unused arguments; only warn about unused local
 * variables.  Makes older code (where argument names were required) compile
 * more quietly.
 */
#define SUPPRESS_ARGUMENT_WARNINGS

/* Some maximum string sizes
 */
#define SMALL_STRING_SIZE 100
#define LARGE_STRING_SIZE 1000
#define COMMAND_BUF_SIZE 2000

/* Number of levels of nested datastructures allowed -- this limit prevents
 * crashes from occuring when saving objects containing variables containing
 * recursive datastructures (with circular references).
 */
#define MAX_SAVE_SVALUE_DEPTH 100

/* Miscellaneous config options that should probably be in the runtime
 * config file.
 */
/* MAX_LOCAL: maximum number of local variables allowed per LPC function */
#define CFG_MAX_LOCAL_VARIABLES 50

/* CFG_MAX_GLOBAL_VARIABLES: This value determines the maximum number of
 *   global variables per object.  The maximum value is 65536.  There is
 *   a marginal memory increase for a value over 256.
 */
#define CFG_MAX_GLOBAL_VARIABLES 65536

#define CFG_EVALUATOR_STACK_SIZE 6000
#define CFG_COMPILER_STACK_SIZE 600
#define CFG_MAX_CALL_DEPTH 150
/* This must be one of 4, 16, 64, 256, 1024, 4096 */
#define CFG_LIVING_HASH_SIZE 256


/* USE_32BIT_ADDRESSES: Use 32 bits for addresses of function, instead of
 * the usual 16 bits.  This increases the maximum program size from 64k
 * of LPC bytecode (NOT source) to 4 GB.  Branches are still 16 bits,
 * imposing a 64k limit on catch(), if(), switch(), loops, and most other
 * control structures.  It would take an extremely large function to hit
 * those limits, though.
 *
 * Overhead: 2 bytes/function with LPC->C off.  Having LPC->C on forces
 * this option, since it needs 4 bytes to store the function pointers
 * anyway, and this setting is ignored.
 */
#undef USE_32BIT_ADDRESSES

/* LARGEST_PRINTABLE_STRING: defines the size of the vsprintf() buffer in
 *   comm.c's add_message(). Instead of blindly making this value larger,
 *   your mudlib should be coded to not send huge strings to users.
 */
#define LARGEST_PRINTABLE_STRING 8192

#endif /* _BASE_INTERNAL_OPTIONS_INTERNAL_H */
