//~ define mod
const int mod = 1e9 + 7;


	auto bp = [&](int a, int b){
		int c = 1;
		while(b){
			if(b&1) c = c * 1ll * a % mod;
			a = a * 1ll * a % mod, b >>= 1;
		} return rr;
	};

	auto f_and_inv = [&](vector<int>& f, vector<int>& inv){
	    f[0] = inv[0] = 1;
	    for(int i = 1;i < (int)f.size(); i++){
			f[i] = f[i-1] * 1ll * i % mod;
			inv[i] = bp(f[i], mod - 2);
		}
	};

	//~ initialize f and inv
    vector<int> f(SZ), inv(SZ);
    f_and_inv(f, inv);
    auto C = [&](int n, int k){
		if(n < k || k < 0) return 0ll;
    	return f[n] * 1ll * inv[k] % mod * 1ll * inv[n - k] % mod;
    };
