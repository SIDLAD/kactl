/**
 * Author: Siddharth Shah
 * Date: 2016-10-08
 * License: CC0
 * Source: me
 * Description: Segment tree with ability to add or set values of large intervals, and compute max of intervals.
 * Can be changed to other things.
 * Use with a bump allocator for better performance, and SmallPtr or implicit indices to save memory.
 * Time: O(\log N).
 * Usage: Node* tr = new Node(v, 0, sz(v));
 * Status: stress-tested a bit
 */
#pragma once
template <typename T = int, typename V = T>
struct segtree
{
	int n;
	vector<T> tree;
	// vector<V> lazy;
	T zero = 0; // Change according to QUERY operation
	// V lazy_zero = 0; // Change according to MODIFY operation
	segtree(int sz)
	{
		n = sz;
		tree.clear(), tree.resize(2 * sz - 1, zero);
		;
		// lazy.clear(), lazy.resize(2 * sz - 1, lazy_zero);
	}

	template <typename U>
	segtree(vector<U> &v) : segtree(v.size()) { build(v); }
	T combine(T a, T b) { return a + b; } // Change according to QUERY operation

	template <typename U>
	void build(vector<U> &v, int id = 0, int segl = 0, int segr = -1)
	{
		if (segr == -1)
			segr = n - 1;
		if (segl == segr)
		{
			tree[id] = v[segl]; // Change according to MODIFY operation
			return;
		}
		int mid = (segl + segr) / 2;
		build(v, id + 1, segl, mid);
		build(v, id + 2 * (mid - segl + 1), mid + 1, segr);
		tree[id] = combine(tree[id + 1], tree[id + 2 * (mid - segl + 1)]);
	}
	/* void propagate(int id, int segl, int segr){
		if(lazy[id] == lazy_zero)return;
		if(segl != segr){
			int mid = (segl + segr) / 2;
			array<int, 2> children= {id + 1, id + 2 * (mid - segl + 1)};
			for(auto child : children){
				tree[child] = lazy[id];  // Change according to MODIFY operation
				lazy[child] = lazy[id];  // Change according to MODIFY operation
			}
		}
		lazy[id] = lazy_zero;
	} */

	template <typename U>
	void modify(U val, int index_l, int index_r, int id = 0, int segl = 0, int segr = -1)
	{
		if (segr == -1)
			segr = n - 1;
		if (index_l > index_r || index_l > segr || segl > index_r)
		{
			return;
		}
		// propagate(id, segl, segr);
		if (segl >= index_l && segr <= index_r)
		{
			tree[id] = val; // Change according to MODIFY operation
			// lazy[id] = val; // Change according to MODIFY operation
			return;
		}
		int mid = (segl + segr) / 2;
		modify(val, index_l, index_r, id + 1, segl, mid);
		modify(val, index_l, index_r, id + 2 * (mid - segl + 1), mid + 1, segr);
		tree[id] = combine(tree[id + 1], tree[id + 2 * (mid - segl + 1)]);
	}

	T query(int index_l, int index_r, int id = 0, int segl = 0, int segr = -1)
	{
		if (segr == -1)
			segr = n - 1;
		if (index_l > index_r || index_l > segr || segl > index_r)
		{
			return zero;
		}
		// propagate(id, segl, segr);
		if (segl >= index_l && segr <= index_r)
		{
			return tree[id];
		}
		int mid = (segl + segr) / 2;
		T leftVal = query(index_l, index_r, id + 1, segl, mid);
		T rightVal = query(index_l, index_r, id + 2 * (mid - segl + 1), mid + 1, segr);
		return combine(leftVal, rightVal);
	}
};