/**
 * Author: Siddharth
 * Date: 2024-12-22
 * Description: sa st 0 is first state. Transition from i using sa st i next c
 */

#pragma once

struct SAState
{
    int len, link;
    map<char, int> next;
};

struct SuffixAutomaton
{
    vector<SAState> st;
    int sz, last;

    SuffixAutomaton()
    {
        sz = 1;
        st.resize(sz);
        st[0].len = 0;
        st[0].link = -1;
        last = 0;
    }

    void sa_extend(char c)
    {
        int cur = sz++;
        st.resize(sz);
        st[cur].len = st[last].len + 1;
        int p = last;
        while (p != -1 && !st[p].next.count(c))
        {
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if (p == -1)
        {
            st[cur].link = 0;
        }
        else
        {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len)
            {
                st[cur].link = q;
            }
            else
            {
                int clone = sz++;
                st.resize(sz);
                st[clone].len = st[p].len + 1;
                st[clone].next = st[q].next;
                st[clone].link = st[q].link;
                while (p != -1 && st[p].next[c] == q)
                {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }
};