#ifndef DEBUG
#   define ASSERT(cond, message) \
        __assert_with_message(#cond, cond, __FILE__, __LINE__, message)
#else
#   define ASSERT(cond, message) (void)0
#endif

void __assert_with_message(const char* expr_str, bool expr, const char* file,
                           int line, const char* msg);