#include "doll.h"

#include "bits/stdc++.h"
using namespace std;

void create_circuit(int m, vector<int> a) {
	vector<int> c(m + 1, -1);
	if((int)a.size() == 1) { 
		c.assign(m + 1, 0);
		
		c[0] = a[0];
		answer(c, {}, {});
		return;
	}

	c[0] = a[0];
	a.erase(a.begin());
	a.push_back(0);
	
	int n = a.size();
	int x_ = __lg(n);
	
	if((1 << x_) < n) x_++;
	
	vector<int> x, y;
	int last = 0;
	
	auto get = [&](){
		x.push_back(0);
		y.push_back(0);
		last++;
		
		return last;
	};
	
	function<int(int, int, vector<int>)> buildTree = [&](int l, int r, vector<int> a){
		if((int)a.size() == 0){
				return -1;
		}
		if(l == r){
			assert((int)a.size() == 1);
			return 0;
		}
		
		int m = (l + r) >> 1;
		int r_sz = min(r - m, (int)a.size());
		int goLeft = (int)a.size() - r_sz;
		
		vector<int> goL(goLeft), goR(r_sz);
		
		int root = get();
		
		x[root - 1] = buildTree(l, m, goL);
		y[root - 1] = buildTree(m + 1, r, goR);
		
		return -root;
	};
	
	buildTree(0, (1 << x_) - 1, a);
	
	vector<int> dir(last, 0);
	
	function<int(int, int)> simulate = [&](int root, int value){
		if(root >= 0){
			return value;
		}
		
		root = -root;
		
		dir[root - 1] ^= 1;
		if(dir[root - 1] != 0){
			x[root - 1] = simulate(x[root - 1], value);
		} else {
			y[root - 1] = simulate(y[root - 1], value);
		}
		
		return -root;
	};
	
	for(int i=0;i<(int)a.size();i++){
		simulate(-1, a[i]);
	}
	
	assert(last <= n + x_);
	
	answer(c, x, y);
	
	return;
}

