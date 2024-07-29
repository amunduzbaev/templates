struct SparseTable{
	vector<int> a;
	vector<vector<int>> mn, mx;
	int N, M;
	
	SparseTable(vector<int> a): a(a){
		N = a.size();
		M = __lg(N) + 1;
		mn.resize(N, vector<int>(M));
		mx.resize(N, vector<int>(M));
		
		for(int i=0;i<N;i++){
			mx[i][0] = mn[i][0] = a[i];
		}
		
		for(int j=1;j<M;j++){
			for(int i=0;i + (1 << (j - 1)) < N;i++){
				mx[i][j] = max(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]);
				mn[i][j] = min(mn[i][j - 1], mn[i + (1 << (j - 1))][j - 1]);
			}
		}
	}
	
	int min_(int l, int r){
		if(l > r) return inf;
		int lg = __lg(r - l + 1);
		return min(mn[l][lg], mn[r - (1 << lg) + 1][lg]);
	}
	
	int max_(int l, int r){
		if(l > r) return inf;
		int lg = __lg(r - l + 1);
		return max(mx[l][lg], mx[r - (1 << lg) + 1][lg]);
	}
};
