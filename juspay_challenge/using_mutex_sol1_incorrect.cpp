// ----------------------------------------------------------------------

vector<bool> is_mutex_locked(N, unlocked); // This represents access to any node in the tree

bool try_mutex_locking_ancs(Tree& tree, vector<Node>& nodes, int node_id) {
	while (1) {
		int parent_id = (node_id - 1);
		bool every_anc_is_unlocked = false;
		while (parent_id >= 0) {
			parent_id /= tree.m;
			if (is_mutex_locked[parent_id]) {
				break;
			}
			parent_id--;
		}
		if (parent_id < 0) {
			every_anc_is_unlocked = true;
		}
		if (every_anc_is_unlocked == true)
			break;
	}
}