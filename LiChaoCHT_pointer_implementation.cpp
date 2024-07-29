struct line{
	ll m, b;
	
	line(){
		m = inf;
		b = INF;
	}
	
	line(ll m, ll b): m(m), b(b){
	}
	
	ll operator * (int x){
		return m * x + b;
	}
	
	int operator ^ (line x){
		return ceil((b - x.b) / (x.m - m));
	};
};

struct node{
	line l;
	node *lx, *rx;
	
	node(): l(line()), lx(NULL), rx(NULL){
	}
	
	node(line l): l(l), lx(NULL), rx(NULL){
	}
};

const int M = 1e9 + 5;

struct LiChao{
	void add(node* r, line l, int lx, int rx){
		if(r == NULL) { 
			r = new node(l); 
			return; 
		}
		
		if(lx == rx){
			if(r -> l * lx > l * lx) swap(r -> l, l);
			return;
		}
		if(l.m == r -> l.m){
			umin(r -> l.b, l.b);
			return;
		}
		
		int m = (lx + rx) >> 1;
		int ix = r -> l ^ l;
		if(ix <= m){
			if(r -> l * (m + 1) > l * (m + 1)) swap(r -> l, l);
			add(r -> lx, l);
		} else {
			if(r -> l * m > l * m) swap(r -> l, l);
			add(r -> rx, l);
		}
	} 
	
	void add(node* r, line l){
		add(r, l, 0, M);
	}
	
	ll get(node* r, int i, int lx, int rx){
		if(r == NULL) return INF;
		if(lx == rx) return r -> l * i;
		
		int m = (lx + rx) >> 1;
		if(i <= m) return min(r -> l * i, get(r -> lx, i, lx, m));
		else return min(r -> l * i, get(r -> rx, i, m + 1, rx));
	} 
	
	ll get(node* r, int i){
		return get(r, i, 0, M);
	}
};
