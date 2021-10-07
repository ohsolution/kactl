/**
 * Author: Cube219
 * Description: Persistent SegTree
 * Usage: 
 * Status: tested
 */
struct PST {
    struct Node {
        int l = -1, r = -1;
        ll v = 0;
    };
    vector<Node> t;
    int stLeaf;
    vector<int> root;
    void init(int n, ll* d) {
        t.clear();
        root.clear();
        root.push_back(1);

        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
        t.resize(stLeaf * 2 + 1);

        for(int i = 0; i < n; ++i) {
            t[stLeaf + i].v = d[i];
        }

        for(int i = 1; i < stLeaf; ++i) {
            t[i].l = i * 2;
            t[i].r = i * 2 + 1;
        }
    }

    ll findImpl(int cl, int cr, int l, int r, int node) {
        if(l <= cl && cr <= r) return t[node].v;
        else if(cr < l || r < cl) return 0;
        int m = (cl + cr) / 2;
        return findImpl(cl, m, l, r, t[node].l) + findImpl(m + 1, cr, l, r, t[node].r);
    }
    ll find(int l, int r, int version) {
        return findImpl(0, stLeaf - 1, l, r, root[version]);
    }

    void update(int idx, ll v) {
        int cl = 0, cr = stLeaf - 1;
        int node = root.back();

        int newnode = t.size();
        root.push_back(newnode);
        t.push_back(t[node]);

        while(cl != cr) {
            int m = (cl + cr) / 2;
            if(idx <= m) {
                cr = m;
                t[newnode].l = newnode + 1;
                newnode++;

                node = t[node].l;
                t.push_back(t[node]);
            } else {
                cl = m + 1;
                t[newnode].r = newnode + 1;
                newnode++;

                node = t[node].r;
                t.push_back(t[node]);
            }
        }
        t[newnode].v = v;
        newnode--;
        while(newnode >= root.back()) {
            t[newnode].v = t[t[newnode].l].v + t[t[newnode].r].v;
            newnode--;
        }
    }
};
