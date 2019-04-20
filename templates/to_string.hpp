/*
 * Returns given unsigned integer value string representation in specified radix.
 */
char const *to_string(unsigned int value) {
    unsigned int i = 0;
    unsigned int radix = DEFAULT_RADIX;
    char *digits = new char[33];
    while (value > 0) {
        unsigned int digit = value % radix;
        digits[i] =  digit > 9 ? 'a' + digit - 10 : '0' + digit;
        value %= radix;
        i++;
    }
    digits[i--] = 0;
    int j = 0;
    while (i > j) {
        char t = digits[i];
        digits[i--] = digits[j];
        digits[j++] = t;
    }
    return digits;
}