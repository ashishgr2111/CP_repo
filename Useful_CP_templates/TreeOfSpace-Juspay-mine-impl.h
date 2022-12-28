struct Node {
	int index;
	string name;

	bool isLocked;
	int locked_ancs, locked_decs;

	int user_id;
};

struct Query {
	int operation;
	string node_name;
	int user_id;
};

struct Tree {
	int n, m;
	vector<vector<int>> children;
};

void change_decs_status(Tree& tree, vector<Node>& nodes, int node_id, int change) {
	for (auto it : tree.children[node_id]) {
		nodes[it].locked_ancs += change;
		change_decs_status(tree, nodes, nodes[it].index, change);
	}
}

void change_ancs_status(Tree& tree, vector<Node>& nodes, int node_id, int change) {
	int parent_id = node_id - 1;
	while (parent_id >= 0) {
		parent_id /= tree.m;
		nodes[parent_id].locked_decs += change;
		parent_id--;
	}
}

bool is_decs_user_same(Tree& tree, vector<Node>& nodes, int node_id, int user_id) {
	bool user_is_same = (nodes[node_id].isLocked == false || nodes[node_id].user_id == user_id);
	for (auto it : tree.children[node_id]) {
		user_is_same &= is_decs_user_same(tree, nodes, nodes[it].index, user_id);
	}
	return user_is_same;
}

string lock(Tree& tree, vector<Node>& nodes, int node_id, int user_id) {
	if (nodes[node_id].isLocked || nodes[node_id].locked_ancs || nodes[node_id].locked_decs)
		return "false";

	nodes[node_id].isLocked = true;
	nodes[node_id].user_id = user_id;
	change_ancs_status(tree, nodes, node_id, 1);
	change_decs_status(tree, nodes, node_id, 1);
	return "true";
}

string unlock(Tree& tree, vector<Node>& nodes, int node_id, int user_id) {
	if (nodes[node_id].isLocked == false || nodes[node_id].user_id != user_id)
		return "false";

	nodes[node_id].isLocked = false;
	nodes[node_id].user_id = -1;
	change_ancs_status(tree, nodes, node_id, -1);
	change_decs_status(tree, nodes, node_id, -1);
	return "true";
}

void unlock_decs(Tree& tree, vector<Node>& nodes, int node_id, int user_id) {
	for (auto it : tree.children[node_id]) {
		if (nodes[it].isLocked) {
			unlock(tree, nodes, nodes[it].index, user_id);
		}
		unlock_decs(tree, nodes, nodes[it].index, user_id);
	}
}

string upgrade(Tree& tree, vector<Node>& nodes, int node_id, int user_id) {
	if (nodes[node_id].isLocked || nodes[node_id].locked_decs == 0 || nodes[node_id].locked_ancs
	        || is_decs_user_same(tree, nodes, node_id, user_id) == false)
		return "false";
	unlock_decs(tree, nodes, node_id, user_id);
	return lock(tree, nodes, node_id, user_id);
}

void code_for_main() {
	Tree tree;
	int q;
	cin >> tree.n >> tree.m >> q;
	tree.children.resize(tree.n);
	vector<Node> nodes(tree.n);
	map<string, int> name_to_id;

	for (int i = 0; i < tree.n; i++) {
		nodes[i].index = i;
		cin >> nodes[i].name;
		name_to_id[nodes[i].name] = i;
		nodes[i].isLocked = false; // Tree's nodes init
		nodes[i].locked_ancs = nodes[i].locked_decs = 0;
		nodes[i].user_id = -1;

		if (i)
			tree.children[(i - 1) / tree.m].pb(i); // create the links of the tree
	}

	for (int i = 0; i < q; i++) {
		Query query;
		cin >> query.operation >> query.node_name >> query.user_id;

		switch (query.operation) {
		case 1:
			cout << lock(tree, nodes, name_to_id[query.node_name], query.user_id) << "\n";
			break;
		case 2:
			cout << unlock(tree, nodes, name_to_id[query.node_name], query.user_id) << "\n";
			break;
		case 3:
			cout << upgrade(tree, nodes, name_to_id[query.node_name], query.user_id) << "\n";
			break;
		}
	}
}