#include <stdlib.h>

int main() {
    void* ptr = malloc(10);
    free(ptr);
    return 0;
}