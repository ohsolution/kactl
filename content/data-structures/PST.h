/**
 * Author: ansol4328
 * Description: Persistent Segment Tree
 * Usage: 
 * a = minimum number of node at leaf level
 * b = total number of updating operation
 * rn = maximum number of root
 * To get the value of Kth segtree use qry(T.root[k],...)
 */
struct PST{
    struct Node{
        int sum, L, R;
    };
    vector<Node> tree;
    vector<int> root;
    int h, cnt, base;
    PST(int a, int b, int rn){
        h=cnt=base=1;
        while(base<a) base<<=1, h++;
        int tmp=base*2+h*b+5;
        tree.resize(tmp);
        root.resize(rn+5);
        root[0]=setup(1,base);
    }
    int setup(int ns, int nf){
        int k=cnt++;
        tree[k].sum=0;
        if(ns<nf){
            int mid=(ns+nf)>>1;
            tree[k].L=setup(ns,mid);
            tree[k].R=setup(mid+1,nf);
        }
        return k;
    }
    void update_Kth_tree(int k, int idx=-1, int v=-1){
        if(root[k]==0) root[k]=root[k-1];
        if(idx!=-1) root[k]=make(root[k],idx,v);
    }
    int make(int bef, int idx, int v, int ns=1, int nf=-1){
        if(nf==-1) nf=base;
        if(nf<idx || idx<ns) return bef;
        int k=cnt++;
        if(ns==nf) tree[k].sum=tree[bef].sum+v;
        else{
            int mid=(ns+nf)>>1;
            tree[k].L=make(tree[bef].L,idx,v,ns,mid);
            tree[k].R=make(tree[bef].R,idx,v,mid+1,nf);
            tree[k].sum=tree[tree[k].L].sum+tree[tree[k].R].sum;
        }
        return k;
    }
    int qry(int num, int st, int fn, int ns=1, int nf=-1){
        if(nf==-1) nf=base;
        if(nf<st || fn<ns) return 0;
        if(st<=ns && nf<=fn) return tree[num].sum;
        int mid=(ns+nf)>>1;
        return qry(tree[num].L,st,fn,ns,mid)+qry(tree[num].R,st,fn,mid+1,nf);
    }
};