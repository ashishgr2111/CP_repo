// ----------------------------------------------------------------------


vector<bool> is_mutex_locked(N, false); // This represents access to any node in the tree

// Atomic
bool try_mutex_locking_subtree(Tree& tree, vector<Node>& nodes, int node_id, int user_id) {
	bool is_subtree_locked = (is_mutex_locked[node_id] == true);
	for (auto it : tree.children[node_id]) {
		is_subtree_locked |= try_mutex_locking_subtree(tree, nodes, it, user_id);
	}

	if (is_subtree_locked)
		return false;
	else
		return true;
}

// Atomic
void mutex_lock_subtree() {
	// implemnetation is same as above
}

// Atomic
void mutex_unlock_subtree() {
	// implemnetation is same as above
}

string lock(Tree& tree, vector<Node>& nodes, int node_id, int user_id) {
	// This checks if the current subtree was locked by any other ancestor's locking operation
	while (try_mutex_locking_subtree(tree, nodes, it, user_id) == false); // This has to be atomic
	mutex_lock_subtree(); // This has to be atomic

	if (nodes[node_id].isLocked || is_any_anc_locked(tree, nodes, node_id) || nodes[node_id].locked_decs) {
		mutex_unlock_subtree(); // This has to be atomic
		return "false";
	}
	nodes[node_id].isLocked = true;
	nodes[node_id].user_id = user_id;
	// NOW WE DON'T NEED TO USE UPDATE_DECS FUNCTION
	update_ancs(tree, nodes, node_id, 1);
	mutex_unlock_subtree(); // This has to be atomic
	return "true";
}
