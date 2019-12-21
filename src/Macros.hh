
namespace psycron {

void assert_fail_key_func(const char* error_name, const char* error_string);

}

#define EASSERT(expr, error_code) \
    if (expr) \
        assert_fail_key_func(#error_code, error_code)

#define EASSERT_ABORT(expr, error_code) \
    if (expr){ \
        assert_fail_key_func(#error_code, error_code); \
        abort(); \
    }

#ifdef NDEBUG 
#define EASSERT(expr, error_code) /* nothing */
#define EASSERT_ABORT(expr, error_code) abort();
#endif