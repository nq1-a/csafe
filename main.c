#include "csafe/csafe.h"

int main() {
    // Create dynamic buffer with 2 items
    dbuf buf = dbuf_new(2);
    dbuf_add(&buf, 16);
    dbuf_add(&buf, 24);
    
    // Get item & unwrap
    option i2 = dbuf_get(&buf, 1);
    printf("%hhd", *(u8*)opt_unwrap(&i2));

    return 0;
}
