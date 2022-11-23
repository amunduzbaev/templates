//~ Z Function
vector<int> z_function(string s) {
    int n = (int) s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

//~ KMP or Prefix Funtionc
void compute_automaton(string s, vector<vector<int>>& aut) {
    s += '#';
    int n = s.size();
    vector<int> pi = prefix_function(s);
    aut.assign(n, vector<int>(26));
    for (int i = 0; i < n; i++) {
        for (int c = 0; c < 26; c++) {
            if (i > 0 && 'a' + c != s[i])
                aut[i][c] = aut[pi[i-1]][c];
            else
                aut[i][c] = i + ('a' + c == s[i]);
        }
    }
}

//~ Suffix Array 
#define ar array

ar<vector<int>, 2> sofa(string s){
	//~ s += "$";
	int n = s.size(), al = max(n, 256);
	vector<int> cnt(al), p(n), c(n);
	for(int i=0;i<n;i++) cnt[s[i]]++;
	for(int i=1;i<al;i++) cnt[i] += cnt[i-1];
	for(int i=0;i<n;i++) p[--cnt[s[i]]] = i;
	c[p[0]] = 0;
	for(int i=1;i<n;i++){
		c[p[i]] = c[p[i-1]];
		if(s[p[i]] != s[p[i-1]]) c[p[i]]++;
	}

	vector<int> cn(n), pn(n);
	for(int k=0;(1 << k) < n;k++){
		for(int i=0;i<n;i++) pn[i] = (p[i] - (1 << k) + n) % n;
		fill(cnt.begin(), cnt.end(), 0);
		for(int i=0;i<n;i++) cnt[c[pn[i]]]++;
		for(int i=1;i<al;i++) cnt[i] += cnt[i-1];
		for(int i=n-1;~i;i--) p[--cnt[c[pn[i]]]] = pn[i];
		cn[p[0]] = 0;
		for(int i=1;i<n;i++){
			cn[p[i]] = cn[p[i-1]];
			if(c[p[i]] != c[p[i-1]] || c[(p[i] + (1 << k)) % n] != c[(p[i - 1] + (1 << k)) % n]) cn[p[i]]++;
		} swap(cn, c);
	} 
	
	//~ c.pop_back();
	return {p, c};
}

//~ Aho Corasick
struct Coras{
	int last, al;
	vector<int> slink, def_, is;
	vector<vector<int>> bor;
	
	int add_(){
		slink.push_back(0), is.push_back(0);
		bor.push_back(def_);
		return last++;
	}
	
	Coras(int al) : al(al){
		def_.resize(al);
		last = 0;
		add_();
	}
	
	void add(string s){
		int r = 0;
		for(auto x : s){ x -= '0';
			if(bor[r][x]){
				r = bor[r][x];
			} else {
				r = bor[r][x] = add_();
			}
		}
		
		if(r) is[r] = 1;
	}
	
	void build(){
		queue<int> q;
		q.push(0);
		while(!q.empty()){
			int u = q.front(); q.pop();
			is[u] |= is[slink[u]];
			
			for(int i=0;i<al;i++){
				if(bor[u][i]){
					slink[bor[u][i]] = u ? bor[slink[u]][i] : 0;
					q.push(bor[u][i]);
				} else {
					bor[u][i] = bor[slink[u]][i];
				}
			}
		}
	}
	
	void vadd(vector<string> v){
		for(auto s : v) add(s);
	}
};
