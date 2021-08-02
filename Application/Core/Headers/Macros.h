// Reference: https://github.com/pfultz2/Cloak/wiki/C-Preprocessor-tricks,-tips,-and-idioms#deferred-expression
// Core Elements
#define VA_NUM_ARGS_HELPER(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...)    N
#define VA_NUM_ARGS(...) VA_NUM_ARGS_HELPER(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

// allow for obfuscation of ## operator
#define CAT(a, ...) PRIMITIVE_CAT(a, __VA_ARGS__)
#define PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__

#define IIF(c) PRIMITIVE_CAT(IIF_, c)
#define IIF_0(t, ...) __VA_ARGS__
#define IIF_1(t, ...) t

#define COMPL(b) PRIMITIVE_CAT(COMPL_, b)
#define COMPL_0 1
#define COMPL_1 0

#define BITAND(x) PRIMITIVE_CAT(BITAND_, x)
#define BITAND_0(y) 0
#define BITAND_1(y) y

#define INC(x) PRIMITIVE_CAT(INC_, x)
#define INC_0 1
#define INC_1 2
#define INC_2 3
#define INC_3 4
#define INC_4 5
#define INC_5 6
#define INC_6 7
#define INC_7 8
#define INC_8 9
#define INC_9 9

#define DEC(x) PRIMITIVE_CAT(DEC_, x)
#define DEC_0 0
#define DEC_1 0
#define DEC_2 1
#define DEC_3 2
#define DEC_4 3
#define DEC_5 4
#define DEC_6 5
#define DEC_7 6
#define DEC_8 7
#define DEC_9 8

#define CHECK_N(x, n, ...) n
#define CHECK(...) CHECK_N(__VA_ARGS__, 0,)
#define PROBE(x) x, 1,

#define IS_PAREN(x) CHECK(IS_PAREN_PROBE x)
#define IS_PAREN_PROBE(...) PROBE(~)

#define NOT(x) CHECK(PRIMITIVE_CAT(NOT_, x))
#define NOT_0 PROBE(~)
// since there is no NOT_x, CHECK will get given a blank value (no params) and will return 0

#define BOOL(x) COMPL(NOT(x))
#define IF(c) IIF(BOOL(c))

#define EAT(...)
#define EXPAND(...) __VA_ARGS__
#define WHEN(c) IF(c)(EXPAND, EAT)

#define EMPTY()
#define DEFER(id) id EMPTY()
#define OBSTRUCT(...) __VA_ARGS__ DEFER(EMPTY)()

#define EVAL(...)  EVAL1(EVAL1(EVAL1(__VA_ARGS__)))
#define EVAL1(...) EVAL2(EVAL2(EVAL2(__VA_ARGS__)))
#define EVAL2(...) EVAL3(EVAL3(EVAL3(__VA_ARGS__)))
#define EVAL3(...) EVAL4(EVAL4(EVAL4(__VA_ARGS__)))
#define EVAL4(...) EVAL5(EVAL5(EVAL5(__VA_ARGS__)))
#define EVAL5(...) EVAL6(EVAL6(EVAL6(__VA_ARGS__)))
#define EVAL6(...) EVAL7(EVAL7(EVAL7(__VA_ARGS__)))
#define EVAL7(...) __VA_ARGS__

#define PRIMITIVE_COMPARE(x, y) IS_PAREN \
( \
    COMPARE_ ## x ( COMPARE_ ## y) (())  \
)
#define IS_COMPARABLE(x) IS_PAREN( CAT(COMPARE_, x) (()) )
#define NOT_EQUAL(x, y) \
IIF(BITAND(IS_COMPARABLE(x))(IS_COMPARABLE(y)) ) \
( \
   PRIMITIVE_COMPARE, \
   1 EAT \
)(x, y)
#define EQUAL(x, y) COMPL(NOT_EQUAL(x, y))
// Comparison of tokens requires macros for both tokens of the form
// COMPARE_<token>(x) x

#define REPEAT(count, macro, ...) \
    WHEN(count) \
    ( \
        OBSTRUCT(REPEAT_INDIRECT) () \
        ( \
            DEC(count), macro, __VA_ARGS__ \
        ) \
        OBSTRUCT(macro) \
        ( \
            DEC(count), __VA_ARGS__ \
        ) \
    )
#define REPEAT_INDIRECT() REPEAT

#define WHILE(pred, op, ...) \
    IF(pred(__VA_ARGS__)) \
    ( \
        OBSTRUCT(WHILE_INDIRECT) () \
        ( \
            pred, op, op(__VA_ARGS__) \
        ), \
        __VA_ARGS__ \
    )
#define WHILE_INDIRECT() WHILE
// \Core Elements

#define STRIP(X) EAT X // turns 'STRIP((int) x)' into 'EAT(int) x' into 'x'
#define PAIR(X) EXPAND X // turns 'PAIR((int) x)' into 'EXPAND(int) x' into 'int x'

#define TYPEOF(X) DETAIL_TYPEOF(DETAIL_TYPEOF_PROBE X,) // turns 'TYPEOF((int) x)' into 'DETAIL_TYPEOF(DETAIL_TYPEOF_PROBE(int) x,)'
#define DETAIL_TYPEOF(...) DETAIL_TYPEOF_HEAD(__VA_ARGS__) // turns 'DETAIL_TYPEOF((int) x)' into 'DETAIL_TYPEOF_HEAD((int) x)'
#define DETAIL_TYPEOF_HEAD(X, ...) EXPAND X // turns 'DETAIL_TYPEOF_HEAD((int), x)' into 'int'
#define DETAIL_TYPEOF_PROBE(...) (__VA_ARGS__), // turns 'DETAIL_TYPEOF_PROBE(X)' into '(X),'
// sample:
// TYPEOF((int) x)
// DETAIL_TYPEOF(DETAIL_TYPEOF_PROBE (int) x,)
// DETAIL_TYPEOF((int), x)
// DETAIL_TYPEOF_HEAD((int), x)
// EXPAND (int)
// int

#define FOR_EACH(macro, ...) EVAL(REPEAT(VA_NUM_ARGS(__VA_ARGS__), macro, __VA_ARGS__))

#define ARG_I(i, ...) PRIMITIVE_CAT(ARG_, i)(__VA_ARGS__)
#define ARG_0(X, ...) X
#define ARG_1(X, ...) ARG_0(__VA_ARGS__)
#define ARG_2(X, ...) ARG_1(__VA_ARGS__)
#define ARG_3(X, ...) ARG_2(__VA_ARGS__)
#define ARG_4(X, ...) ARG_3(__VA_ARGS__)
#define ARG_5(X, ...) ARG_4(__VA_ARGS__)
#define ARG_6(X, ...) ARG_5(__VA_ARGS__)
#define ARG_7(X, ...) ARG_6(__VA_ARGS__)
#define ARG_8(X, ...) ARG_7(__VA_ARGS__)
#define ARG_9(X, ...) ARG_8(__VA_ARGS__)

#define STRINGIFY(x) #x
#define TO_STRING(x) STRINGIFY(x)