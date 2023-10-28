#include <Vector.h>

/*
 * структура линии, а-ля самадельный pair
 */
struct line{
    bool color;
    unsigned long long size;
};

/*
 * обёртка ветора для того, чтобы сделать vector-функцию
 */
struct Array_bool {
    Vector<bool> v;
};

/*
 * обёртка ветора для того, чтобы сделать vector-функцию
 */
struct Array_line {
    Vector<line> v;
};
