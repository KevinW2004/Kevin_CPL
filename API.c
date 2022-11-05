int Choose(int a, int b) {
    if (b == 0 || b == a)
        return 1;
    return Choose(a - 1, b - 1) + Choose(a - 1, b);
}