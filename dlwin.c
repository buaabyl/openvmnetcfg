#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "dlwin.h"

//not thread safe!!!
static char libname[8196];
static char message[8196 + 32];

void* dlopen(const char* filename, int flags)
{
    HANDLE h;

    strncpy(libname, filename, 8195);

    h = LoadLibrary(filename);
    if (h == INVALID_HANDLE_VALUE) {
        return NULL;
    }

    return (void*)h;
}

int dlclose(void* handle)
{
    HANDLE h = (HANDLE)handle;

    if ((handle == NULL) || (h == INVALID_HANDLE_VALUE)) {
        return -1;
    }

    FreeLibrary(h);

    return 0;
}

void* dlsym(void* handle, const char* name)
{
    HANDLE h = (HANDLE)handle;

    if ((handle == NULL) || (h == INVALID_HANDLE_VALUE)) {
        return NULL;
    }

    return GetProcAddress(h, name); 
}

char* dlerror(void)
{
    int n;
    char* msg;

    if (GetLastError() == ERROR_SUCCESS) {
        return NULL;
    }

    n = sprintf(message, "%s: ", libname);
    FormatMessage(
            FORMAT_MESSAGE_FROM_SYSTEM,
            NULL, 
            GetLastError(),
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            &message[n],
            sizeof(message) - n,
            NULL);

    return message;
}


