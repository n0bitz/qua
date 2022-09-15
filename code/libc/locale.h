#ifndef __LOCALE_H
#define __LOCALE_H

struct lconv {
    char *decimal_point;
};

struct lconv* localeconv(void);

#endif
