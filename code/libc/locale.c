#include <locale.h>

struct lconv __lconv = {
    "."
};

struct lconv* localeconv(void) {
    return &__lconv;
}
