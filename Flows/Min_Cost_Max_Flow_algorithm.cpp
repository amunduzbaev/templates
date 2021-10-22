const int INF = 1e9;

struct edge{
	int a, b, cap, cost, f;
};
 
struct MCMF{
	vector<edge> ee;
	vector<vector<int>> edges;
	int n, s, t;
	queue<int> qq;
	
	MCMF(int n, int s, int t) : n(n), s(s), t(t){
		edges.resize(n);
	}
	
	void add_edge(int a, int b, int c, int cost){
		edges[a].push_back((int)ee.size());
		ee.push_back({a, b, c, cost, 0});
		edges[b].push_back((int)ee.size());
		ee.push_back({b, a, 0, -cost, 0});
	}
	
	void spfa(int u, vector<int>& d, vector<int>& p){
		vector<bool> is(n);
		d.resize(n, INF), p.resize(n, -1);
		d[u] = 0;
		queue<int> qq; qq.push(u);
		while(!qq.empty()){
			int u = qq.front(); qq.pop();
			is[u] = 0;
			for(auto x : edges[u]){
				if(d[ee[x].b] <= d[u] + ee[x].cost || ee[x].f == ee[x].cap) continue;
				d[ee[x].b] = d[u] + ee[x].cost;
				p[ee[x].b] = x;
				if(!is[ee[x].b]){
					qq.push(ee[x].b);
					is[ee[x].b] = 1;
				}
			}
		}
	}
	
	ar<int, 2> min_cost(int K = INF){
		int cost = 0, res = 0;
		while(res < K){
			vector<int> d, p;
			spfa(s, d, p);
			if(d[t] == INF) break;
			int u = t, mn = K - res;
			while(u != s){
				mn = min(ee[p[u]].cap - ee[p[u]].f, mn);
				u = ee[p[u]].a;
			}
			
			res += mn, cost += d[t] * mn, u = t;
			while(u != s){
				ee[p[u]].f += mn;
				ee[p[u] ^ 1].f -= mn;
				u = ee[p[u]].a;
			}
		}
		return {res, cost};
	}
};

