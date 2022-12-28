int n;
const int maxn = 2e5 + 10;
int seg[4 * maxn];
int a[maxn];

void build(int a[], int pos, int l, int r) {
	if (l == r) {
		seg[pos] = a[l];
		return ;
	}
	int mid = l + ((r - l) >> 1);
	build(a, 2 * pos + 1, l, mid);
	build(a, 2 * pos + 2, mid + 1, r);
	seg[pos] = __gcd(seg[2 * pos + 1], seg[2 * pos + 2]);
}

int query(int l, int r, int cl, int cr, int pos) {
	if (cl > r || l > cr)
		return -1;
	else if (cl >= l && cr <= r)
		return seg[pos];
	else {
		int mid = cl + ((cr - cl) >> 1);
		int al = query(l, r, cl, mid, 2 * pos + 1);
		int ar = query(l, r, mid + 1, cr, 2 * pos + 2);
		if (al == -1)
			return ar;
		else if (ar == -1)
			return al;
		else
			return __gcd(al, ar);
	}
}