/**
 * Author: Siddharth
 * Date: 2024-12-22
 * Description: Make the commented changes to remove persistence.
 * O(q) should be around 2e5 for persistent, seems like 1e6 gives memory problems
 */
#pragma once

struct SegNode{
    long long freq = 0;
    int lazy = 0;
    int left = -1;
    int right = -1;
};
 
struct PersistentDynamicSegTree {
	vector<SegNode> tree;
	const int minl, maxr;
	int timer = 0;
    int lastroot = 0; // -
 
	long long comb(long long a, long long b) { return a + b; }
 
	void apply(int cur, int len, int val) {
        tree[cur].lazy = val;
        tree[cur].freq = (long long) len * val;
	}
    
    // .., int q = 0) .. if(q > 0) {tree.reserve(2 * q * __lg(r - l + 1));}..
	PersistentDynamicSegTree(int l, int r) : minl(l), maxr(r) {tree.push_back(SegNode());}

	void push_down(int cur, int l, int r) {
		if (tree[cur].left == -1) {
			tree[cur].left = ++timer;
			tree.push_back(SegNode());
		}
        else if (tree[cur].lazy != 0){              // -
            int newleft = ++timer;                  // -
            tree.push_back(tree[tree[cur].left]);   // -
            tree[cur].left = newleft;               // -
        }
		if (tree[cur].right == -1) {
			tree[cur].right = ++timer;
			tree.push_back(SegNode());
		}
        else if (tree[cur].lazy != 0){              // -
            int newright = ++timer;                 // -
            tree.push_back(tree[tree[cur].right]);  // -
            tree[cur].right = newright;             // -
        }
        if(tree[cur].lazy == 0) {return;}
		int m = l + (r - l >> 1);
		apply(tree[cur].left, m - l + 1, tree[cur].lazy);
		apply(tree[cur].right, r - m, tree[cur].lazy);
		tree[cur].lazy = 0;
	}
    
    //void modify .. , int cur = 0, ..
	int modify(int val, int index_l, int index_r, int cur = -1, int l = 1, int r = -1) {
        if(cur == -1) cur = lastroot;   // -
        if(l == 1 and r == -1) l = minl, r = maxr;
		if (index_r < l || index_l > r) { return cur; } // { return; }
 
        int newcur = cur;   // -                     
		if (index_l <= l && r <= index_r) {
            newcur = ++timer;           // -
            tree.push_back(tree[cur]);  // -
			apply(newcur, r - l + 1, val); // replace newcur with cur
		} else {
			push_down(cur, l, r);
			int m = l + (r - l >> 1);
            newcur = ++timer;           // -
            tree.push_back(tree[cur]);  // -
			tree[newcur].left = modify(val, index_l, index_r, tree[cur].left, l, m);        // remove lhs
			tree[newcur].right = modify(val, index_l, index_r, tree[cur].right, m + 1, r);  //remove lhs
			tree[newcur].freq = // replace newcur with cur
			    comb(tree[tree[newcur].left].freq, tree[tree[newcur].right].freq);  // replace newcur with cur
		}
        return lastroot = newcur;       // -
	}
    
    // .. int cur = 0, ..
	long long query(int index_l, int index_r, int cur = -1, int l = 1, int r = -1) {
        if(cur == -1) cur = lastroot; // -
        if(l == 1 and r == -1) l = minl,r = maxr;
		if (index_r < l || index_l > r) { return 0; }
		if (index_l <= l && r <= index_r) { return tree[cur].freq; }
		push_down(cur, l, r);
		int m = l + (r - l >> 1);
		return comb(query(index_l, index_r, tree[cur].left, l, m),
		            query(index_l, index_r, tree[cur].right, m + 1, r));
	}
    
    // remove function
    int load_root(int cur){
        lastroot = ++timer;
        tree.push_back(tree[cur]);
        return lastroot;
    }
};