#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <queue>
#include <map>
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
vector<vii> AdjList;
int V, E;
const int DFS_WHITE = -1;
const int DFS_BLACK = 1;
vi dfs_low, dfs_num, dfs_parent;
vector<bool> articulation_vertex;
int dfsNumberCounter;
int rootChildren, dfsRoot;
vii rlt;

void articulationPointAndBridge(int u) {
	dfs_low[u] = dfs_num[u] = dfsNumberCounter++;
	for(int j = 0; j < (int)AdjList[u].size(); ++j) {
		ii v = AdjList[u][j];
		if (dfs_num[v.first] == DFS_WHITE) {
			dfs_parent[v.first] = u;
			if (u == dfsRoot) rootChildren++;
			articulationPointAndBridge(v.first);
			if (dfs_low[v.first] >= dfs_num[u])
				articulation_vertex[u] = true;
			if (dfs_low[v.first] > dfs_num[u]) {
				// this is a bridge (u, v.first)
				rlt.push_back(make_pair(u, v.first));
			}
			dfs_low[u] = min(dfs_low[u], dfs_low[v.first]);
		}
		else if (v.first != dfs_parent[u]) {
			dfs_low[u] = min(dfs_low[u], dfs_num[v.first]);
		}
	}
}

void graphPointEdge() {
	dfsNumberCounter = 0;
	articulation_vertex.assign(V, false);
	dfs_parent.assign(V, 0);
	dfs_num.assign(V, DFS_WHITE);
	dfs_low.assign(V, 0);
	for(int i = 0; i < V; ++i) {
		if (dfs_num[i] == DFS_WHITE) {
			dfsRoot = i;
			rootChildren = 0;
			articulationPointAndBridge(i);
			articulation_vertex[dfsRoot] = (rootChildren > 1);
		}
	}
}

struct less_than_key
{
    inline bool operator() (const ii first, const ii second)
    {
        return (first.first < second.first);
    }
};

void test() {
	ifstream fi;
	fi.open("input.txt");
	fi >> V;
	for(int i = 0; i < V; ++i) { vii tmp; AdjList.push_back(tmp); }
	while(!fi.eof()) {
		int from, to;
		fi >> from;
		int E;
		fi >> E;
		for(int i = 0; i < E; ++i) {
			fi >> to;
			AdjList[from].push_back(make_pair(to, 0));
		}
	}
	graphPointEdge();
	sort(rlt.begin(), rlt.end(), less_than_key());
	cout << (int) rlt.size() << " criticial links\n";
	for(int i = 0; i < (int) rlt.size(); ++i) {
		ii tmp = rlt[i];
		cout << tmp.first << " - " << tmp.second << "\n";
	}
}

int main() {
	test();
	return 0;
}