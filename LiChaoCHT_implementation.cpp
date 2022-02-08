#define int long long
struct node{
	int m, c;
	
	int v(int x){
		return (m * x + c);
	}
	
	int in(node b){
		return floor((double)(b.c - c) / (double)(m - b.m));
	}
};

struct LiChaoST{
	vector<node> tree;
	vector<int> qq;
	int n;
	
	void init(int sz, vector<int>& q){
		n = sz;
		tree.resize(n * 4, {(int)1e9, (int)1e9});
		qq = q;
		sort(qq.begin(), qq.end());
	}
	
	void add(node v, int lx, int rx, int x){
		if(lx == rx) { tree[x] = v; return; }
		if(tree[x].m == v.m){
			if(tree[x].m > v.m) tree[x] = v;
			return;
		}
		int m = (lx + rx)>>1;
		int in = v.in(tree[x]);
		if(in < qq[m+1]){
			if(tree[x].v(qq[m+1]) > v.v(qq[m+1])) swap(tree[x], v);
			add(v, lx, m, x<<1);
		} else {
			if(tree[x].v(qq[m]) > v.v(qq[m])) swap(tree[x], v);
			add(v, m+1, rx, x<<1|1);
		}
	} void add(node v){
		add(v, 0, n - 1, 1);
	}
	
	int get(int i, int lx, int rx, int x){
		if(lx == rx) return tree[x].v(qq[i]);
		int m = (lx + rx)>>1;
		if(i <= m) return min(get(i, lx, m, x<<1), tree[x].v(qq[i]));
		else return min(get(i, m+1, rx, x<<1|1), tree[x].v(qq[i]));
	} int get(int i) { return get(i, 0, n - 1, 1); }
}; 

