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
			ar<int, 2> cur = {c[p[i]], c[(p[i] + (1 << k)) % n]};
			ar<int, 2> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
			cn[p[i]] = cn[p[i-1]];
			if(cur != prev) cn[p[i]]++;
		} swap(cn, c);
	} 
	
	//~ c.pop_back();
	return {p, c};
}

