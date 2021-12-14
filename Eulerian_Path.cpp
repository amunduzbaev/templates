#include "bits/stdc++.h"
using namespace std;

#define ar array

const int N = 2e5 + 5;
vector<int> edges[N];

signed main(){
	ios::sync_with_stdio(0); cin.tie(0);
	
	int n, m; cin>>n>>m;
	vector<ar<int, 2>> e(m);
	for(int i=0;i<m;i++){
		cin>>e[i][0]>>e[i][1];
		edges[e[i][0]].push_back(i);
		edges[e[i][1]].push_back(i);
	}
	
	int s = 1;
	ar<int, 2> p = {-1, -1};
	for(int i=1;i<=n;i++){
		if(!edges[i].empty()) s = i;
		if((int)edges[i].size() % 2 == 0) continue;
		if(p[0] == -1) p[0] = i;
		else if(p[1] == -1) p[1] = i;
		else { cout<<"NO\n"; return 0; }
	}
	
	if(~p[0]){
		edges[p[0]].push_back(m);
		edges[p[1]].push_back(m);
		e.push_back(p), m++;
	}
	
	vector<int> used(m), res;
	function<void(int)> dfs = [&](int u){
		while(!edges[u].empty()){
			int i = edges[u].back(); edges[u].pop_back();
			if(used[i]) continue;
			used[i] = 1;
			dfs(e[i][0] ^ e[i][1] ^ u);
		}
		
		res.push_back(u);
	};
	
	dfs(s);
	if(~p[0]){
		for(int i=0;i+1<(int)res.size();i++){
			if((res[i] == p[0] && res[i+1] == p[1]) || (res[i] == p[1] && res[i+1] == p[0])){
				vector<int> tmp;
				tmp.insert(tmp.end(), res.begin() + i + 1, res.end());
				tmp.insert(tmp.end(), res.begin(), res.begin() + i);
				swap(res, tmp);
			}
		}
	}
	
	for(int i=1;i<=n;i++){
		if(edges[i].empty()) continue;
		cout<<"NO\n"; return 0;
	}
	
	cout<<"YES\n";
	for(auto x : res) cout<<x<<" ";
	cout<<"\n";
}
