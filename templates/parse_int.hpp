/*
 * Parses given string as an unsigned integer in specified radix.
 * If input string is invalid, returns -1
 */
int parse_int(char const *token) {
    unsigned int value = 0;
    unsigned int radix = DEFAULT_RADIX;
    for (char const *c = token; *c != '\0'; c++) {
        int digit = *c > '9' ? *c - 'a' : *c - '0';
        if (digit >= 0 && digit < radix) {
            (value *= radix) += digit;
        } else {
            return -1;
        }
    }
    return value;
}