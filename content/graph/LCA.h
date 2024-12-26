/**
 * Author: Siddharth
 * Date: 2024-12-22
 * Description: Lowest common ancestor in 0-rooted tree 
 */

#pragma once

#include "../data-structures/SparseTable.h"

struct LCA {
	int T = 0;
	vi time, path, ret;
	SparseTable st;

	LCA(vector<vi>& C) : time(sz(C)), st((dfs(C,0,-1), ret)) {}
	void dfs(vector<vi>& C, int v, int par) {
		time[v] = T++;
		for (int y : C[v]) if (y != par) {
			path.push_back(v), ret.push_back(time[v]);
			dfs(C, y, v);
		}
	}

	int lca(int a, int b) {
		if (a == b) return a;
		tie(a, b) = minmax(time[a], time[b]);
		return path[st.query_val(a, b - 1)];
	}
	//dist(a,b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
};