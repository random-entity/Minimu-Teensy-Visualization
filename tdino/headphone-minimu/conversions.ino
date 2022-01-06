void IntTo4Bytes(int n, byte *arr)
{
    *arr = (n >> 24) & 0xFF;
    *(arr + 1) = (n >> 16) & 0xFF;
    *(arr + 2) = (n >> 8) & 0xFF;
    *(arr + 3) = n & 0xFF;
}

void ShortTo2Bytes(short n, byte *arr)
{
    *arr = (n >> 8) & 0xFF;
    *(arr + 1) = n & 0xFF;
}