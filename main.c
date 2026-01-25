#include "csafe/csafe.h"

int main() {
    dbuf buf = dbuf_new(2);
    dbuf_add(&buf, 16);
    dbuf_add(&buf, 24);
    dbuf_extend(&buf, -1);
    dbuf_debug(&buf);

    return 0;
}
