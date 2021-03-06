#include <algorithm>
#include <fstream>
#include <queue>
#include <vector>
#include <map>
#include <cmath>
#include <iostream>
#include <string>
using namespace std;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
vector<vii> AdjList;
int V, E;
int DFS_WHITE = 0;
int DFS_BLACK = 1;
int DFS_GRAY = 2;
vi dfs_num;
vi dfs_parent;
bool hasCycle;

void graphCheck(int u) {
	dfs_num[u] = DFS_GRAY;
	for(int j = 0; j < (int)AdjList[u].size(); ++j) {
		ii v = AdjList[u][j];
		if (dfs_num[v.first] == DFS_WHITE) {
			dfs_parent[v.first] = u;
			graphCheck(v.first);
		}
		else if (dfs_num[v.first] == DFS_GRAY) {
			if(v.first != dfs_parent[u]) {
				hasCycle = true;
				return;
			}
		}
		else if (dfs_num[v.first] == DFS_BLACK) {
			//forward cross edge
		}
	}
	dfs_num[u] = DFS_BLACK;
}

bool cycleCheck() {
	dfs_num.assign(V, DFS_WHITE);
	dfs_parent.assign(V, -1);
	hasCycle = false;
	for(int i = 0; i < V; ++i) {
		if (dfs_num[i] == DFS_WHITE) {
			graphCheck(i);
		}
	}
	return hasCycle;
}

void test(string filepath) {
	ifstream file;
	file.open(filepath);
	file >> V;
	file >> E;
	AdjList.clear();
	for(int i = 0; i < V; ++i) {
		vii tmp;
		AdjList.push_back(tmp);
	}
	int from, to;
	for(int i = 0; i < E; ++i) {
		file >> from >> to;
		AdjList[from].push_back(make_pair(to, 0));
	}
	cout << cycleCheck() << "\n";
	file.close();
}

int main() {
	test("cycle1.txt");
	test("cycle2.txt");
	return 0;
}