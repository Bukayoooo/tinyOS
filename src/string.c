typedef unsigned int size_t;

void *memcpy(void *dst, void *src, size_t len)
{
    char *tmp = dst;
    const char *s = src;

    while(len--)
    {
            *tmp++ = *s++;
    }
    return dst;
}

size_t strlen(const char *s)
{
    const char *sc = s;
    while(*sc != '\0')
    {
            sc++;
    }

    return sc - s;
}