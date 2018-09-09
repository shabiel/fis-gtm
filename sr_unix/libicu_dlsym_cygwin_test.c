#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <unicode/umachine.h>
#include <unicode/uvernum.h>
#include <unicode/uversion.h>


int main (int arg, char **argv)
{
    void *ptr = dlopen("cygicuio.dll", RTLD_LAZY);
    if (ptr != NULL)
    {
        printf("%p\n",ptr);
    }
    else
    {
        printf("%s",dlerror());
        exit(1);
    }

    UVersionInfo v;

    void (*ptr2)(UVersionInfo) = dlsym(NULL,"u_getVersion");
    ptr2(v);
    printf("%i",v[0]);
    printf("%i",v[1]);
    printf("%i",v[2]);
    printf("%i",v[3]);
    printf("\n");


    if (ptr2 != NULL)
    {
        printf("%p\n",ptr2);
    }
    else
    {
        printf("%s",dlerror());
        exit(1);
    }

    return 0;
}
