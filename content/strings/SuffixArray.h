/**
 * Author: Siddharth
 * Date: 2024-12-22
 * Description: Suffix Array
 */

#pragma once

#include "../data-structures/SparseTable.h"

struct SuffixArray
{
    vector<int> p,c,_lcp;
    SparseTable* st;
    int n;
    void count_sort(vector<int>& p, vector<int>&c)
    {
        int n = p.size();
        vector<int> cnt(n), pos(n), p_new(n);
        for(auto x:c)cnt[x]++;
        pos[0] = 0;
        for(int i=1;i<n;i++)pos[i] = pos[i-1] + cnt[i-1];
        for(auto x:p)p_new[pos[c[x]]++] = x;
        p = p_new;
    }

    SuffixArray(string s) : n(s.length() + 1)
    {
        p.assign(n,0),c.assign(n,0),_lcp.assign(n,0);
        s += (char)31;
        vector<pair<int,int>> a(n);
        for(int i=0;i<n;i++)a[i] = {s[i],i};
        sort(all(a));
        for(int i=0;i<n;i++) p[i] = a[i].second;
        c[p[0]] = 0;
        for(int i=1;i<n;i++) {
            if(a[i].first == a[i-1].first)c[p[i]] = c[p[i-1]];
            else c[p[i]] = c[p[i-1]] + 1;
        }

        for(int k=0;1<<k < n; k++) {
            for(int i=0;i<n;i++) {
                p[i] = (p[i] - (1<<k) + n)%n;
            }
            count_sort(p,c);
            vector<int> c_new(n);
            c_new[p[0]] = 0;
            for(int i=1;i<n;i++) {
                pair<int,int> now = {c[p[i]],c[(p[i] + (1<<k))%n]};
                pair<int,int> prev = {c[p[i-1]],c[(p[i-1] + (1<<k))%n]};
                if(now == prev)c_new[p[i]] = c_new[p[i-1]];
                else c_new[p[i]] = c_new[p[i-1]] + 1;
            }
            c = c_new;
        }

        for(int i=0,k=0;i<n-1;i++)
        {
            int j = p[c[i]-1];
            while(s[j + k] == s[i + k])k++;
            _lcp[c[i] - 1] = k;
            k&&k--;
        }
        st = new SparseTable(_lcp);
    }

    int lcp(int i, int j)
    {
        if(i == j) return n - 1 - i;
        int l = c[i];
        int r = c[j];
        if(l > r)swap(l,r);
        return st->query_val(l,r - 1);
    }
};