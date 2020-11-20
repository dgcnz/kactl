#include <algorithm>

using namespace std;

const int NMAX = 10e4 + 11;

int n, t[4 * NMAX];

void build(int a[], int v, int tl, int tr)
{
    if (tl == tr)
        t[v] = a[tl];
    else
    {
        int tm = (tl + tr) / 2;
        build(a, v * 2, tl, tm);
        build(a, v * 2 + 1, tm + 1, tr);
        t[v] = t[v * 2] + t[v * 2 + 1];
    }
}

int sum(int v, int tl, int tr, int l, int r)
{
    if (l > r)
        return 0;
    if (l == tl and r == tr)
        return t[v];
    int tm = (tl + tr) / 2;

    // min(r, tm), when we split we only care about the left part, but if the
    // range exceeds the queried range, then the remaining is unnecessary, so
    // pick r.
    return sum(v * 2, tl, tm, l, min(r, tm)) +
           sum(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
}

void update(int v, int tl, int tr, int pos, int new_val)
{
    if (tl == tr)
        t[v] = new_val;
    else
    {
        int tm = (tl + tr) / 2;

        if (pos <= tm)
            update(v * 2, tl, tm, pos, new_val);
        else
            update(v * 2 + 1, tm + 1, tr, pos, new_val);
        t[v] = t[v * 2] + t[v * 2 + 1];
    }
}
