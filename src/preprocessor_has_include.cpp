#if defined __has_include
#  if __has_include (<stdatomic.h>)
#    include <stdatomic.h>
#  endif
#endif

// check if optional is available
#if __has_include(<optional>)
#  include <optional>
#  define have_optional 1
// otherwise use fallback
#elif __has_include(<experimental/optional>)
#  include <experimental/optional>
#  define have_optional 1
#  define experimental_optional 1
// better: use feature test macro!
#else
#  define have_optional 0
#endif

#if have_optional == 1
#ifndef experimental_optional 
std::optional<int> oint;
#else
std::experimental::optional<int> oint;
#endif
// other implementation or error message
#endif

int main()
{
    /// ...

    return 0;
}