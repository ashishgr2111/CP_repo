#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

#define pb push_back

struct Node
{
    int locked_ancs, locked_decs;
    string name;
    bool isLocked;
    int user_id;
};

struct Tree
{
    int n, m;
    vector<vector<int>> children;
};

struct Query
{
    int operation;
    string node_name;
    int user_id;
};

bool is_any_anc_locked(Tree &tree, vector<Node> &nodes, int node_id)
{
    int parent_id = (node_id - 1);
    bool any_anc_locked = false;

    while (parent_id >= 0)
    {
        parent_id /= tree.m;
        any_anc_locked |= (nodes[parent_id].isLocked == true);
        parent_id--;
    }
    return any_anc_locked;
}

void update_ancs(Tree &tree, vector<Node> &nodes, int node_id, int change)
{
    int parent_id = (node_id - 1);
    while (parent_id >= 0)
    {
        parent_id /= tree.m;
        nodes[parent_id].locked_decs += change;
        parent_id--;
    }
}

void update_decs(Tree &tree, vector<Node> &nodes, int node_id, int change)
{
    for (auto it : tree.children[node_id])
    {
        nodes[it].locked_ancs += change;
        update_decs(tree, nodes, it, change);
    }
}

string lock(Tree &tree, vector<Node> &nodes, int node_id, int user_id)
{
    if (nodes[node_id].isLocked == true)
    {
        return "false";
    }
    nodes[node_id].isLocked = true;
    nodes[node_id].user_id = user_id;
    update_ancs(tree, nodes, node_id, 1);

    if (is_any_anc_locked(tree, nodes, node_id) || nodes[node_id].locked_decs)
    {
        // Revert any changes now
        nodes[node_id].isLocked = false;
        nodes[node_id].user_id = -1;
        update_ancs(tree, nodes, node_id, -1);
        return "false";
    }
    else if (nodes[node_id].user_id != user_id)
    {
        update_ancs(tree, nodes, node_id, -1);
        return "false";
    }
    return "true";
}

string unlock(Tree &tree, vector<Node> &nodes, int node_id, int user_id)
{
    if (nodes[node_id].isLocked == false || nodes[node_id].user_id != user_id)
    {
        return "false";
    }
    nodes[node_id].isLocked = false;
    nodes[node_id].user_id = -1;
    update_ancs(tree, nodes, node_id, -1);
    update_decs(tree, nodes, node_id, -1);
    return "true";
}

bool decs_have_same_uid(Tree &tree, vector<Node> &nodes, int node_id, int user_id)
{
    bool same_uid = (nodes[node_id].isLocked == false || nodes[node_id].user_id == user_id);
    for (auto it : tree.children[node_id])
    {
        same_uid &= decs_have_same_uid(tree, nodes, it, user_id);
    }
    return same_uid;
}

void unlock_decs(Tree &tree, vector<Node> &nodes, int node_id, int user_id)
{
    for (auto it : tree.children[node_id])
    {
        if (nodes[it].isLocked)
        {
            unlock(tree, nodes, it, user_id);
        }
        unlock_decs(tree, nodes, it, user_id);
    }
}

string upgradeLock(Tree &tree, vector<Node> &nodes, int node_id, int user_id)
{
    if (nodes[node_id].isLocked ||
        nodes[node_id].locked_ancs ||
        nodes[node_id].locked_decs == 0 ||
        decs_have_same_uid(tree, nodes, node_id, user_id) == false)
    {
        return "false";
    }
    unlock_decs(tree, nodes, node_id, user_id);
    return lock(tree, nodes, node_id, user_id);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    // IO speedup
    cin.tie(0); // Flush the output for interactive scenarios or problems..
    // int tt;
    // cin >> tt;
    // while (tt--)
    // {
    // }

    Tree tree;
    int q;
    cin >> tree.n >> tree.m >> q;
    tree.children.resize(tree.n);

    vector<Node> nodes(tree.n);
    map<string, int> name_to_id;

    for (int i = 0; i < tree.n; i++)
    {
        nodes[i].locked_ancs = nodes[i].locked_decs = 0;
        nodes[i].isLocked = false;
        nodes[i].user_id = -1;

        cin >> nodes[i].name;
        name_to_id[nodes[i].name] = i;

        if (i)
        {
            tree.children[(i - 1) / tree.m].pb(i);
        }
    }

    vector<Query> query(q);
    for (int i = 0; i < q; i++)
    {
        cin >> query[i].operation >> query[i].node_name >> query[i].user_id;

        switch (query[i].operation)
        {
        case 1:
            cout << lock(tree, nodes, name_to_id[query[i].node_name], query[i].user_id) << "\n";
            break;
        case 2:
            cout << unlock(tree, nodes, name_to_id[query[i].node_name], query[i].user_id) << "\n";
            break;
        case 3:
            cout << upgradeLock(tree, nodes, name_to_id[query[i].node_name], query[i].user_id) << "\n";
            break;
        }
    }
}