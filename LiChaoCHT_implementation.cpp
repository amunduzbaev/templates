const int N = 1e5 + 5;
const int M = 1e9 + 5;

struct line{
	int m, b;
	
	int operator * (int x){
		return m * x + b;
	}
	
	int operator ^ (line x){
		return ceil((b - x.b) / (x.m - m));
	};
};

struct LiChao{
	line tree[N * 30];
	int last, L[N * 30], R[N * 30];
	LiChao(){
		last = 0;
		//~ for(int i=0;i<(N*30);i++) tree[i] = {M, M * M};
	}
	
	void add(line v, int lx, int rx, int x){
		if(lx == rx){
			if(tree[x] * lx > v * lx) swap(tree[x], v);
			return;
		}
		if(v.m == tree[x].m){
			tree[x].b = min(tree[x].b, v.b);
			return;
		}
		
		int m = (lx + rx) >> 1;
		int ix = tree[x] ^ v;
		if(ix <= m){
			if(tree[x] * (m + 1) > v * (m + 1)) swap(tree[x], v);
			add(v, lx, m, (L[x] ? L[x] : L[x] = ++last));
		} else {
			if(tree[x] * m > v * m) swap(tree[x], v);
			add(v, m + 1, rx, (R[x] ? R[x] : R[x] = ++last));
		}
	} void add(lint v){
		add(v, 0, M, 0);
	}
	
	int get(int i, int lx, int rx, int x){
		if(lx == rx) return tree[x] * i;
		int m = (lx + rx) >> 1;
		if(i <= m && L[x]) return min(tree[x] * i, get(i, lx, m, L[x]));
		if(m < i && R[x]) return min(tree[x] * i, get(i, m + 1, rx, R[x]));
		return tree[x] * i;
	} int get(int i){
		return get(i, 0, M, 0);
	}
}tree;

change max / min
