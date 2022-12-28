class dsu
{
private:
	int *pa, *ra, n;
public:
	dsu(int n) {
		this->n = n;
		pa = new int[n];
		ra = new int[n];

		for (int i = 0; i < n; i++) {
			pa[i] = i;
			ra[i] = 0;
		}
	}
	~dsu() {
		delete[] pa;
		delete[] ra;
	}

	int find(int i) {
		if (pa[i] != i)
			return pa[i] = find(pa[i]);

		return pa[i];
	}

	void uni(int x, int y) {
		int px = find(x);
		int py = find(y);
		if (px == py)
			return ;

		if (ra[px] < ra[py]) {
			swap(px, py);
		}
		pa[py] = px;
		if (ra[px] == ra[py]) {
			ra[px]++;
		}
	}
};

