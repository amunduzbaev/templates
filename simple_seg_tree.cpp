struct node_st{
	//~ write the nodes
	
	int f, sum;
	
	node_st(): f(0), sum(0){
	}
	
	node_st(int f, int sum): f(f), sum(sum){
	}
};

struct ST{
	int N;
	vector<node_st> tree;
	
	ST(int N): N(N){
		//~ initialize tree
		tree.resize(N << 2);
	}
	
	node_st upd(node_st a, node_st b){
		node_st res;
		
		//~ update with children values
		//~ a and b
		
		return res;
	}
	
	void push(int x, int lx, int rx){
		if(lx == rx) return;

		//~ initialize push function
		
		return;
	}
	
	void set(int i, node_st v, int lx, int rx, int x){
		if(lx == rx){
			tree[x] = v;
			return;
		}
		
		int m = (lx + rx) >> 1;
		push(x, lx, rx);
		
		if(i <= m) set(i, v, lx, m, x << 1);
		else set(i, v, m + 1, rx, x << 1 | 1);
		
		tree[x] = upd(tree[x << 1], tree[x << 1 | 1]);
	}
	
	void set(int i, node_st v){
		set(i, v, 0, N, 1);
	}
	
	void add(int l, int r, int v, int lx, int rx, int x){
		if(lx > r || rx < l) return;
		if(lx >= l && rx <= r){
			tree[x].f += v;
			tree[x].sum += v * 1ll * (rx - lx + 1);
			return;
		}
		
		int m = (lx + rx) >> 1;
		push(x, lx, rx);
		
		add(l, r, v, lx, m, x << 1);
		add(l, r, v, m + 1, rx, x << 1 | 1);
		
		tree[x] = upd(tree[x << 1], tree[x << 1 | 1]);
	}
	
	void add(int l, int r, int v){
		add(l, r, v, 0, N, 1);
	}
	
	node_st res;
	
	void get(int l, int r, int lx, int rx, int x){
		if(lx > r || rx < l) return;
		if(lx >= l && rx <= r){
			res = upd(res, tree[x]);
			return;
		}
		
		int m = (lx + rx) >> 1;
		push(x, lx, rx);
		get(l, r, lx, m, x << 1);
		get(l, r, m + 1, rx, x << 1 | 1);
	}
	
	int get(int l, int r){
		//~ initialize res
		
		get(l, r, 0, N, 1);

		//~ return res
	}
};
