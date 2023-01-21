#define ar array
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct node{
	int y, val, sz, c, sum;
	node *lx, *rx;
	
	node(int x, int v) : val(x), sz(1), c(v), sum(v), lx(NULL), rx(NULL){
		y = uniform_int_distribution<int>(0, 2e9)(rng);
	}
};

struct RBST{
	void rec(node* a){
		a->sum = (a->lx != NULL ? a->lx->sum : 0) + (a->rx != NULL ? a->rx->sum : 0) + a->c;
	}
	node* merge(node* a, node* b){
		if(a == NULL) return b;
		if(b == NULL) return a;
		
		if(a->y > b->y){
			a->rx = merge(a->rx, b);
			rec(a);
			return a;
		} else {
			b->lx = merge(a, b->lx);
			rec(b);
			return b;
		} 
	}
	
	ar<node*, 2> split(node* a, int v){
		if(a == NULL) return {NULL, NULL};
		if(a->val < v){
			auto t = split(a->rx, v);
			a->rx = t[0]; rec(a);
			return {a, t[1]};
		} else {
			auto t = split(a->lx, v);
			a->lx = t[1]; rec(a);
			return {t[0], a};
		} 
	}
	
	bool is(node*&a, int x, int v){
		if(a == NULL) return false;
		if(a->val == x){
			a->c += v; rec(a);
			return true;
		}
		
		bool ok = 0;
		if(a->val < x) ok = is(a->rx, x, v);
		else ok = is(a->lx, x, v);
		rec(a);
		return ok;
	}
	
	void add(node*&root, int x, int v){
		if(is(root, x, v)) return;
		node* tmp = new node(x, v);
		auto tt = split(root, x);
		root = merge(tt[0], tmp);
		root = merge(root, tt[1]);
	}
	
	int get(node*&a, int x){
		if(a == NULL) return 0;
		if(a->val <= x){
			return (a->lx != NULL ? a->lx->sum : 0) + a->c + get(a->rx, x);
		} else {
			return get(a->lx, x);
		}
	}
	
	void print(node* a){
		if(a == NULL) return;
		print(a->lx);
		cout<<a->val<<" ";
		print(a->rx);
	}
};

