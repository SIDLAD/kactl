/**
 * Description: tree.construct(arr) to build a segment tree on arr.
 * tree.update(l, r, value, version) to update the segment tree.
 * tree.query(0, n-1, l, r, version_ptr) to query the segment tree.
 * 
 */
#pragma once

class DynamicPersistentSegTree{
    class Node{
    public:
        Node *left = nullptr;
        Node *right = nullptr;
        int val = 0, prop = 0;
    };
    int n = 0;
    bool create_version_on_update = false;
    vector<int> vec{};
    Node *create_child(Node *&curr){
        auto newNode = new Node();
        newNode->left = curr->left;
        newNode->right = curr->right;
        newNode->prop = curr->prop;
        newNode->val = curr->val;
        return newNode;
    }
    void lazy(int i, int j, Node *curr){
        if (!curr->prop)
            return;
        curr->val = (j - i + 1) * curr->prop;
        if (i != j){
            curr->left = create_child(curr->left);
            curr->right = create_child(curr->right);
            curr->left->prop = curr->prop;
            curr->right->prop = curr->prop;
        }
        curr->prop = 0;
    }
    Node *construct(int i, int j){
        auto newNode = new Node();
        if (i == j){
            newNode->val = vec[i];
        }
        else{
            int mid = i + (j - i) / 2;
            auto left = construct(i, mid);
            auto right = construct(mid + 1, j);
            newNode->val = left->val + right->val;
            newNode->left = left;
            newNode->right = right;
        }
        return newNode;
    }
    Node *update(int i, int j, int l, int r, int value, Node *curr){
        lazy(i, j, curr);
        if (i >= l && j <= r){
            Node *newNode = create_child(curr);
            newNode->prop += value;
            lazy(i, j, newNode);
            return newNode;
        }
        if (i > r || j < l){
            return curr;
        }
        auto newNode = new Node();
        int mid = i + (j - i) / 2;
        newNode->left = update(i, mid, l, r, value, curr->left);
        newNode->right = update(mid + 1, j, l, r, value, curr->right);
        newNode->val = newNode->left->val + newNode->right->val;
        return newNode;
    }
public:
    vector<Node *> ptrs{};
    int query(int i, int j, int l, int r, Node *curr = nullptr){
        if (curr == nullptr)
            curr = ptrs.back();
        lazy(i, j, curr);
        if (j < l || r < i){
            return 0;
        }
        if (i >= l && j <= r){
            return curr->val;
        }
        int mid = i + (j - i) / 2;
        return query(i, mid, l, r, curr->left) + query(mid + 1, j, l, r, curr->right);
    }
    void construct(const vector<int> &vec){
        if (vec.empty())
            return;
        n = vec.size();
        this->vec = vec;
        auto root = construct(0, n - 1);
        ptrs.push_back(root);
    }
    void update(int l, int r, int value, int version = -1){
        if (version == -1)
            version = ptrs.size() - 1;
        if (create_version_on_update)
            ptrs.push_back(update(0, n - 1, l, r, value, ptrs[version]));
        else
            ptrs[version] = update(0, n - 1, l, r, value, ptrs[version]);
    }
    int copy_version(int version) { 
        ptrs.push_back(create_child(ptrs[version])); 
        return ptrs.size()-1;
    }
};