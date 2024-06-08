#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <time.h>

void* malloc(size_t size) {
    static void* (*original_malloc)(size_t) = NULL;
    static int call_count = 0;

    if (!original_malloc) {
        original_malloc = dlsym(RTLD_NEXT, "malloc");        
    }

    // Simulate a failure condition every 10 calls
    call_count++;
    if (call_count % 10 == 0) {
        // Set errno to ENOMEM and return NULL to simulate failure
        errno = ENOMEM;
        return NULL;
    }

    void* ptr = original_malloc(size);

    // Use snprintf to format the message
    char buffer[256];
    int len = snprintf(buffer, sizeof(buffer), "malloc called with size: %zu, returned: %p\n", size, ptr);
    if (len > 0) {
        write(2, buffer, len);
    }

    return ptr;
}
