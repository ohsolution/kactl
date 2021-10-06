/**
 * Author: max804
 * Description: Lazy segment tree
 * Time: O(\log N).
 * Usage: sg.init(n); sg.initv(idx, v); sg.build();
 *        sg.find(l, r); sg.add(l, r, v);
 */
#pragma once

class SegTree
{
public:
    vector<ll> t, lazy;
    int stLeaf;
    void init(int n) {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
        t.resize(stLeaf * 2);
        lazy.resize(stLeaf * 2);
    }
    void initv(int idx, ll v) {
        t[stLeaf + idx] = v;
    }
    void build() {
        for(int i = stLeaf - 1; i > 0; --i) {
            t[i] = t[i * 2] + t[i * 2 + 1];
        }
    }
    void push(int l, int r, int node) {
        if(lazy[node] == 0) return;
        if(node < stLeaf) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        t[node] += (r - l + 1) * lazy[node];
        lazy[node] = 0;
    }
    ll findImpl(int cl, int cr, int l, int r, int node) {
        push(cl, cr, node);
        if(cr < l || r < cl) return 0;
        if(l <= cl && cr <= r) return t[node];
        int m = (cl + cr) / 2;
        return findImpl(cl, m, l, r, node * 2) + findImpl(m + 1, cr, l, r, node * 2 + 1);
    }
    void addImpl(int cl, int cr, int l, int r, int node, ll v) {
        push(cl, cr, node);
        if(cr < l || r < cl) return;
        if(l <= cl && cr <= r) {
            lazy[node] += v;
            push(cl, cr, node);
            return;
        }
        int m = (cl + cr) / 2;
        addImpl(cl, m, l, r, node * 2, v);
        addImpl(m + 1, cr, l, r, node * 2 + 1, v);
        t[node] = t[node * 2] + t[node * 2 + 1];
    }
    ll find(int l, int r) {
        return findImpl(0, stLeaf - 1, l, r, 1);
    }
    void add(int l, int r, ll v) {
        addImpl(0, stLeaf - 1, l, r, 1, v);
    }
};
