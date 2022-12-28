int mod = 1e9 + 7;
const int maxn = 1e5 + 10;
int fact[maxn];

int mul(int x, int y) {
	return (x * y) % mod;
}
int add(int x, int y) {
	return (x + y) % mod;
}
int sub(int x, int y) {
	return (x - y + mod) % mod;
}

int power(int x, int y) {
	int res = 1;
	while (y) {
		if (y & 1)
			res = mul(res, x);
		x = mul(x, x);
		y >>= 1;
	}
	return res;
}

int modinv(int x) {
	return power(x, mod - 2);
}

int ncr(int n, int r) {
	return mul(fact[n], modinv(mul(fact[r], fact[n - r])));
}