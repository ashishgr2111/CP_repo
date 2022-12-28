const int maxn = 4e5 + 10;
vector<int> val(maxn);	// Actual value
vector<int> par(maxn);	// Parent
vector<int> ra(maxn, 0); // Rank
vector<pair<int, int>> range(maxn) ; // Range covered by DSU
vector<int> howm(maxn, 0);		// How many of a[i] array in that DSU node
vector<int> ps(maxn, 0);		// Prefix sum of linear sorted vector

struct gap
{
	int val;
	pair<int, int> p;
};

inline bool operator<(const gap& lhs, const gap& rhs)
{
	return lhs.val < rhs.val;
}

int find(int i) {
	if (par[i] != i)
		return par[i] = find(par[i]);

	return par[i];
}

int calc(int x) {
	int parent = find(x);
	int na = howm[parent];
	int r = range[parent].second;
	int l = r - na;
	int res = ps[r];
	if (l >= 0)
		res -= ps[l];

	return res;
}

void uni(int x, int y, int &ans) {
	int px = find(x);
	int py = find(y);
	if (px == py)
		return ;

	if (ra[px] < ra[py]) {
		swap(px, py);
	}

	par[py] = px;
	range[px] = mp(min(range[px].first, range[py].first),
	               max(range[px].second, range[py].second));
	howm[px] += howm[py];
	ans += calc(px);
	if (ra[px] == ra[py]) {
		ra[px]++;
	}
}