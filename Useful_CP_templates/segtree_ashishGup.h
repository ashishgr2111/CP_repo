struct nodeVal
{
	//Use required attributes
	int ans, pref, suf, leftmost, rightmost;
	bool isSorted;

	//Default Values
	nodeVal() : ans(0), pref(0), suf(0), isSorted(0), leftmost(0), rightmost(0) {};
};

struct SegTree
{
	int N;
	vector<nodeVal> st;
	vector<bool> cLazy;
	vector<int> lazy;

	void init(int n)
	{
		N = n;
		st.resize(4 * N + 5);
		cLazy.assign(4 * N + 5, false);
		lazy.assign(4 * N + 5, 0);
	}

	//Write reqd merge functions
	void merge(nodeVal &cur, nodeVal &l, nodeVal &r)
	{
		if (l.rightmost <= r.leftmost)
		{
			cur.isSorted = l.isSorted & r.isSorted;
			cur.ans = l.ans + r.ans + l.suf * r.pref;
			cur.pref = l.pref;
			if (l.isSorted)
				cur.pref += r.pref;
			cur.suf = r.suf;
			if (r.isSorted)
				cur.suf += l.suf;
		}
		else
		{
			cur.isSorted = 0;
			cur.pref = l.pref;
			cur.suf = r.suf;
			cur.ans = l.ans + r.ans;
		}
		cur.leftmost = l.leftmost;
		cur.rightmost = r.rightmost;
	}

	//Handle lazy propagation appriopriately
	void propagate(int node, int L, int R)
	{
		//No propagation, because point updates.
	}

	void build(int node, int L, int R)
	{
		if (L == R)
		{
			st[node].ans = 1;
			st[node].pref = 1;
			st[node].suf = 1;
			st[node].isSorted = 1;
			st[node].leftmost = a[L];
			st[node].rightmost = a[L];
			return;
		}
		int M = (L + R) / 2;
		build(node * 2, L, M);
		build(node * 2 + 1, M + 1, R);
		merge(st[node], st[node * 2], st[node * 2 + 1]);
	}

	nodeVal Query(int node, int L, int R, int i, int j)
	{
		if (cLazy[node])
			propagate(node, L, R);
		if (j < L || i > R)
			return nodeVal();
		if (i <= L && R <= j)
			return st[node];
		int M = (L + R) / 2;
		nodeVal left = Query(node * 2, L, M, i, j);
		nodeVal right = Query(node * 2 + 1, M + 1, R, i, j);
		nodeVal cur;
		merge(cur, left, right);
		return cur;
	}

	nodeVal pQuery(int node, int L, int R, int pos)
	{
		if (cLazy[node])
			propagate(node, L, R);
		if (L == R)
			return st[node];
		int M = (L + R) / 2;
		if (pos <= M)
			return pQuery(node * 2, L, M, pos);
		else
			return pQuery(node * 2 + 1, M + 1, R, pos);
	}

	void Update(int node, int L, int R, int i, int j, int val)
	{
		if (cLazy[node])
			propagate(node, L, R);
		if (j < L || i > R)
			return;
		if (i <= L && R <= j)
		{
			cLazy[node] = 1;
			lazy[node] = val;
			propagate(node, L, R);
			return;
		}
		int M = (L + R) / 2;
		Update(node * 2, L, M, i, j, val);
		Update(node * 2 + 1, M + 1, R, i, j, val);
		merge(st[node], st[node * 2], st[node * 2 + 1]);
	}

	void pUpdate(int node, int L, int R, int pos, int val)
	{
		if (L == R)
		{
			st[node].ans = 1;
			st[node].pref = 1;
			st[node].suf = 1;
			st[node].isSorted = 1;
			st[node].leftmost = a[L];
			st[node].rightmost = a[L];
			return;
		}
		int M = (L + R) / 2;
		if (pos <= M)
			pUpdate(node * 2, L, M, pos, val);
		else
			pUpdate(node * 2 + 1, M + 1, R, pos, val);
		merge(st[node], st[node * 2], st[node * 2 + 1]);
	}

	nodeVal query(int pos)
	{
		return pQuery(1, 1, N, pos);
	}

	nodeVal query(int l, int r)
	{
		return Query(1, 1, N, l, r);
	}

	void update(int pos, int val)
	{
		pUpdate(1, 1, N, pos, val);
	}

	void update(int l, int r, int val)
	{
		Update(1, 1, N, l, r, val);
	}
};