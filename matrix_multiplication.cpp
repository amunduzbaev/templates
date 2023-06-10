struct mtx{
	vector<vector<int>> a;
	int m;
	mtx(int m): m(m){
		a.resize(m, vector<int>(m));
	}
	mtx(int m, int t): m(m){
		a.resize(m, vector<int>(m));
		for(int i=0;i<m;i++) a[i][i] = t;
	}
	
	mtx(){
	}
	
	mtx operator * (const mtx& b){
		mtx c(m);
		for(int i=0;i<m;i++){
			for(int j=0;j<m;j++){
				for(int k=0;k<m;k++){
					c.a[i][j] = (c.a[i][j] + a[i][k] * 1ll * b.a[k][j]) % mod;
				}
			}
		}
		
		return c;
	}
};

mtx bp(mtx a, ll b){
	mtx c(a.m, 1);
	while(b){
		if(b&1) c = c * a;
		a = a * a, b >>= 1;
	}
	
	return c;
}

