// Problem link - https://codeforces.com/contest/1731/problem/D
// Problem name - D. Valiant's New Map

#include "bits/stdc++.h"
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
#define PI 3.1415926535898
#define mp make_pair
#define pb push_back
#define pii pair<int, int>
#define ll long long
// #define int long long

using namespace std;
// using namespace __gnu_pbds;
// typedef tree<int, null_type, less<int>, rb_tree_tag,
//         tree_order_statistics_Node_update> ordered_set;

// If code without memory alloc still passes, let me try storing big arrays
// Maybe that will fail ?? -> Yes, it does fail if your stack has limited size.
// But if you store dynamically, then it won't fail.
// That is because, the dynamic memory pool (a.k.a. the heap) is typically
// much larger than the stack.

#define deb(...) logger(#__VA_ARGS__, __VA_ARGS__)
template <typename... Args>
void logger(string vars, Args &&...values)
{
	cout << vars << " = ";
	string delim = "";
	(..., (cout << delim << values, delim = ", "));
}

class Solution {
protected:
	int n, m;
	vector<vector<int>> a;
public:
	Solution() {
		cin >> n >> m;
		a.resize(n, vector<int> (m));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cin >> a[i][j];
			}
		}
	}
};

class SparseTable: protected Solution {
	struct newv {
		vector<short> sv;
	};
	vector<vector<newv>> spv; // our sparse table
	int lgn;
public:
	static const int N;
	static vector<int> lg2;
	SparseTable () {
		lgn = 0;
		for (int i = 1, pow = 0; i <= n; i <<= 1, lgn++);
		spv.resize(n, vector<newv> (m));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				spv[i][j].sv.resize(lgn);
			}
		}
	}

	int yo(int x1, int y1, int x2, int y2) {
		x2++;
		y2++;
		int a = lg2[x2 - x1], b = lg2[y2 - y1];

		return min(
		           min(spv[x1][y1].sv[a], spv[x2 - (1 << a)][y1].sv[a]),
		           min(spv[x1][y2 - (1 << b)].sv[a], spv[x2 - (1 << a)][y2 - (1 << b)].sv[a])
		       );
	}

	void build() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				int val = a[i][j];
				if (a[i][j] > INT16_MAX)
					val = INT16_MAX;
				spv[i][j].sv[0] = val;
			}
		}
		for (int a = 1; a < lgn; a++) {
			for (int i = 0; i + (1 << a) <= n; i++) {
				for (int j = 0; j + (1 << a) <= m; j++) {
					spv[i][j].sv[a] = min(min(spv[i][j].sv[a - 1], spv[i + (1 << (a - 1))][j].sv[a - 1]),
					                      min(spv[i][j + (1 << (a - 1))].sv[a - 1], spv[i + (1 << (a - 1))][j + (1 << (a - 1))].sv[a - 1]));
				}
			}
		}
	}

	void solve() {
		int l = 1, r = min(n, m);
		int ans = 1;
		while (l <= r) {
			int mid = l + ((r - l) >> 1);
			int f = 0;
			for (int i = 0; i + mid - 1 < n; i++) {
				for (int j = 0; j + mid - 1 < m; j++) {
					if (yo(i, j, i + mid - 1, j + mid - 1) >= mid) {
						f = 1;
						break;
					}
				}
				if (f)
					break;
			}
			if (f) {
				ans = max(ans, mid);
				l = mid + 1;
			}
			else {
				r = mid - 1;
			}
		}
		cout << ans << "\n";
	}
};

class PrefSumDP: protected Solution {
	vector<vector<int>> b; // our threshold prefix sum table
public:
	PrefSumDP() {
		b.resize(n + 1, vector<int>(m + 1));
	}
	int yo(int x1, int y1, int x2, int y2) {
		int ans = b[x2][y2];
		ans -= b[x1][y2];
		ans -= b[x2][y1];
		ans += b[x1][y1];
		return ans;
	}

	void solve() {
		int l = 1, r = min(n, m);
		int ans = 1;
		while (l <= r) {
			int mid = l + ((r - l) >> 1);

			for (int i = 0; i <= n; i++) {
				for (int j = 0; j <= m; j++) {
					b[i][j] = 0;
					if (i && j) {
						if (a[i - 1][j - 1] >= mid) {
							b[i][j] = 1;
						}
						b[i][j] += (b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1]);
					}
				}
			}

			int f = 0;
			for (int i = mid; i <= n; i++) {
				for (int j = mid; j <= m; j++) {
					if (yo(i - mid, j - mid, i, j) >= mid * mid) {
						f = 1;
						break;
					}
				}
				if (f)
					break;
			}
			if (f) {
				ans = max(ans, mid);
				l = mid + 1;
			}
			else {
				r = mid - 1;
			}
		}
		cout << ans << "\n";
	}
};

const int SparseTable::N = 1e6 + 10;
vector<int> SparseTable::lg2(SparseTable::N);

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	// IO speedup
	cin.tie(0); // Flush the output for interactive scenarios or problems..

	int tt;
	cin >> tt;

	for (int i = 2; i < SparseTable::N; i++) SparseTable::lg2[i] = SparseTable::lg2[i >> 1] + 1;

	while (tt--)
	{
		// SparseTable *st = new SparseTable();
		// st->build();
		// st->solve();

		PrefSumDP *psdp = new PrefSumDP();
		psdp->solve();
	}

	return 0;
}