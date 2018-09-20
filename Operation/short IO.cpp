/*steal from zerol*/
1inline char next_char() {
    static char buf[100000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}
inline bool maybe_digit(char c) {
    return c >= '0' && c <= '9';
}
template <typename T>
void rn(T& _v) {
    static char ch;
    static bool negative = false;
    _v = 0;
    while (!maybe_digit(ch)) {
        negative = ch == '-';
        ch = next_char();
    }
    do _v = (_v << 1) + (_v << 3) + ch - '0';
    while (maybe_digit(ch = next_char()));
    if (negative) _v = -_v;
}

template <typename T>
void o(T p) {
    static int stk[70], tp;
    if (p == 0) {
        putchar('0');
        return;
    }
    if (p < 0) { p = -p; putchar('-'); }
    while (p) stk[++tp] = p % 10, p /= 10;
    while (tp) putchar(stk[tp--] + '0');
}
