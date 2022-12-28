struct gap
{
	int val;
	pair<int, int> p;
};

inline bool operator<(const gap& lhs, const gap& rhs)
{
	return lhs.val < rhs.val;
}

/** Usage inside main:---------> **/
// multiset<gap> gaps;



struct stl {
	int l, c;
};

struct str {
	int r, c;
};

inline bool operator<(const stl& lhs, const stl& rhs)
{
	return lhs.l == rhs.l ? lhs.c < rhs.c : lhs.l < rhs.l;
}

inline bool operator<(const str& lhs, const str& rhs)
{
	return lhs.r == rhs.r ? lhs.c > rhs.c : lhs.r < rhs.r;
}