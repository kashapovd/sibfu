#include <linux/vmalloc.h>

int main() {

    char *buf;
    buf = vmalloc(1000 * PAGE_SIZE);
    vfree(buf);
    return 0;
}
