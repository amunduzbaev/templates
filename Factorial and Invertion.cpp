void FINV(vector<int>& f, vector<int>& inv){
    auto bp = [&](int a, int b){
		int rr = 1;
		while(b){
			if(b&1) rr = rr * 1ll * a % mod;
			a = a * 1ll * a % mod, b >>= 1;
		} return rr;
    };
    
    f[0] = inv[0] = 1;
    for(int i=1;i<(int)f.size();i++) f[i] = f[i-1] * 1ll * i % mod, inv[i] = bp(f[i], mod - 2);
}

//~ in low

    vector<int> f(n + 1), inv(n + 1);
    FINV(f, inv);
    auto C = [&](int n, int k){
      return f[n] * 1ll * inv[k] % mod * 1ll * inv[n - k] % mod;
    };
