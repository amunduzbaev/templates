
typedef long long ll; 
const double pi = acos(-1);
const double eps = 1e-9;

struct vec_t{
	ll x, y;
	
	void rd(){
		cin >> x >> y;
	}
	
	vec_t(): vec_t(0, 0) {};
	vec_t(ll x, ll y): x(x), y(y) {};
	
	//~ vec operator / (const double& d) const{
		//~ return {x / d, y / d};
	//~ };
	
	bool operator < (const vec_t& b) const { 
		if(x != b.x) return x < b.x; 
		return y < b.y; 
	}
	vec_t operator - (const vec_t& b) const{ return {x - b.x, y - b.y}; }
	vec_t operator + (const vec_t& b) const{ return {x + b.x, y + b.y}; }
	ll operator * (const vec_t& b) const{ return x * 1ll * b.x + y * 1ll * b.y; }
	ll operator % (const vec_t& b) const{ return x * 1ll * b.y - y * 1ll * b.x; }
	double len() const { return sqrt(x * 1ll * x + y * 1ll * y); }
	ll len2() const { return x * 1ll * x + y * 1ll * y; }
};

struct line_t{
	ll a, b, c;
	
	void rd(){
		cin >> a >> b >> c;
	}
	
	line_t(): line_t(0, 0, 0) {}
	line_t(const ll& a, const ll& b, const ll& c): a(a), b(b), c(c) {}
	line_t(const vec_t& p1, const vec_t& p2){
		a = p2.y - p1.y;
		b = p1.x - p2.x;
		c = -(a * p1.x + b * p1.y);
	}
	
	double dis(const vec_t& p){
		vec_t n(a, b);
		return (p * n + c) / n.len();
	}
	
	ar<ll, 3> intersect(const line_t& x){
		return {vec_t(-c, b) % vec_t(-x.c, x.b), 
			vec_t(a, -c) % vec_t(x.a, -x.c), 
			vec_t(a, b) % vec_t(x.a, x.b)};
	}
};

struct seg_t{
	vec_t a, b;
	line_t L;
	
	void rd(){
		a.rd(), b.rd();
		L = line_t(a, b);
	}
	
	seg_t(): seg_t(vec_t(), vec_t()) {}
	seg_t(const vec_t& a, const vec_t& b): a(a), b(b) {
		L = line_t(a, b); 
	}
	bool is_in(const vec_t& p){
		return abs((a - p) % (b - p)) < eps && min((p - a) * (b - a), (p - b) * (a - b)) + eps > 0;
	}
	
	double dis(const vec_t& p){
		if((p - a) * (b - a) - eps < 0 || (p - b) * (a - b) - eps < 0){
			return min((p - a).len(), (p - b).len());
		} else {
			return abs(L.dis(p));
		}
	}
	
	double dis(seg_t seg){
		ar<ll, 3> P = L.intersect(seg.L);
		if(P[2]){
			vec_t p(P[0] * 1. / P[2], P[1] * 1. / P[2]);
			if(is_in(p) && seg.is_in(p)){
				return 0;
			}
		}
		
		return min({seg.dis(a), seg.dis(b), dis(seg.a), dis(seg.b)});
	}
};
struct ray_t{
	vec_t a, b;
	line_t L;
	
	void rd(){
		a.rd(), b.rd();
		L = line_t(a, b);
	}
	
	ray_t(): ray_t(vec_t(), vec_t()) {}
	ray_t(const vec_t& a, const vec_t& b): a(a), b(b) {
		L = line_t(a, b); 
	}
	bool is_in(const vec_t& p){
		return abs((a - p) % (b - p)) < eps && (p - a) * (b - a) + eps > 0;
	}
	
	double dis(const vec_t& p){
		if((p - a) * (b - a) - eps < 0){
			return (p - a).len();
		} else {
			return abs(L.dis(p));
		}
	}
	
	double dis(ray_t seg){
		ar<ll, 3> P = L.intersect(seg.L);
		if(P[2]){
			vec_t p(P[0] * 1. / P[2], P[1] * 1. / P[2]);
			if(is_in(p) && seg.is_in(p)){
				return 0;
			}
		}
		
		return min({seg.dis(a), dis(seg.a)});
	}
};

