struct edge{
	int a, b, cap, f;
};

const int INF = 1e9;
struct Dinic{
	vector<edge> ee;
	vector<vector<int>> edges;
	int n, s, t;
	vector<int> vis, cur;
	queue<int> qq;
	
	Dinic(int n, int s, int t) : n(n), s(s), t(t){
		edges.resize(n);
		vis.resize(n);
		cur.resize(n);
	}
	
	void add_edge(int a, int b, int c){
		edges[a].push_back((int)ee.size());
		ee.push_back({a, b, c, 0});
		edges[b].push_back((int)ee.size());
		ee.push_back({b, a, 0, 0});
	}
	
	bool bfs(){
		while(!qq.empty()){
			int u = qq.front(); qq.pop();
			for(auto x : edges[u]){
				if(~vis[ee[x].b] || ee[x].f == ee[x].cap) continue;
				vis[ee[x].b] = vis[u] + 1;
				qq.push(ee[x].b);
			}
		}
		return vis[t] != -1;
	}
	
	int dfs(int u, int mn = 1e9){
		if(mn == 0) return 0;
		if(u == t) return mn;
		for(int& i=cur[u];i<(int)edges[u].size();i++){
			int x = edges[u][i];
			if(vis[u] + 1 != vis[ee[x].b] || ee[x].f == ee[x].cap) continue;
			int is = dfs(ee[x].b, min(mn, ee[x].cap - ee[x].f));
			if(is == 0) continue;
			
			ee[x].f += is;
			ee[x ^ 1].f -= is;
			return is;
		} return 0;
	}
	
	int max_flow(int K = INF){
		int res = 0;
		while(res < K){
			fill(vis.begin(), vis.end(), -1);
			vis[s] = 0; qq.push(s);
			if(!bfs()) break;
			fill(cur.begin(), cur.end(), 0);
			int rr;
			while((rr = dfs(s, K - res))){
				res += rr;
			}
		} return res;
	}
};

