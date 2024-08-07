const int M = 1e6 + 5;

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

struct LiChao{
	node* add(node* r, line l, int lx, int rx){
		if(r == NULL) { 
			r = new node(l); 
			return r; 
		}
		
		if(lx == rx){
			if(r -> l * lx > l * lx) swap(r -> l, l);
			return r;
		}
		if(l.m == r -> l.m){
			umin(r -> l.b, l.b);
			return r;
		}
		
		int m = (lx + rx) >> 1;
		int ix = r -> l ^ l;
		if(ix <= m){
			if(r -> l * (m + 1) > l * (m + 1)) swap(r -> l, l);
			r -> lx = add(r -> lx, l, lx, m);
		} else {
			if(r -> l * m > l * m) swap(r -> l, l);
			r -> rx = add(r -> rx, l, m + 1, rx);
		}
		
		return r;
	} 
	
	node* add(node* r, line l){
		return add(r, l, 0, M);
	}
	
	ll get(node* r, int i, int lx, int rx){
		if(r == NULL) return INF;
		//~ cout<<i<<" "<<r -> l.m<<" "<<r -> l.b<<"\n";
		if(lx == rx) return r -> l * i;
		
		int m = (lx + rx) >> 1;
		if(i <= m) return min(r -> l * i, get(r -> lx, i, lx, m));
		else return min(r -> l * i, get(r -> rx, i, m + 1, rx));
	} 
	
	ll get(node* r, int i){
		return get(r, i, 0, M);
	}
};
