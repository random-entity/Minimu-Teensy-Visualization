void ShortTo2Bytes(short n, byte *arr)
{
    *arr = (n >> 8) & 0xFF;
    *(arr + 1) = n & 0xFF;
}

short TwoBytesToShort(byte *arr) {
  return (*arr << 8) | *(arr + 1);
}