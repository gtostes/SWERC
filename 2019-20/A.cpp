#include<bits/stdc++.h>
using namespace std;
 
#define _ << ' ' <<
#define pb push_back
#define eb emplace_back
#define all(x) begin(x), end(x)
#define mp make_pair
#define f first
#define s second
#define sz(x) int((x).size())
#define each(x,A) for(auto &x: A)
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
using ll = long long;
using db = long double;
using pl = pair<ll,ll>;
using pi = pair<int,int>;
//using cd = complex<db>;
using vi = vector<int>;
using vd = vector<db>;
using vl = vector <ll>;
using str = string;
template<class T> using V = vector<T>; 
 
//const int MOD = 1e9+7;
 
template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << '{'; string sep; for (const auto &x : v) os << sep << x, sep = ", "; return os << '}'; }
template<typename T, size_t size> ostream& operator<<(ostream &os, const array<T, size> &arr) { os << '{'; string sep; for (const auto &x : arr) os << sep << x, sep = ", "; return os << '}'; }
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
 
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
 
#ifdef NEAL_DEBUG
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif
 
/*mt19937_64 mt_rand(chrono::high_resolution_clock::now().time_since_epoch().count());
uniform_int_distribution<long long> rg(1,1e18);*/
 
V<pi> d[1010];
 
int dist(pi a, pi b){
	ll v = (a.f-b.f)*(a.f-b.f)+(a.s-b.s)*(a.s-b.s);
	ll ans = sqrt(v);
	if(v!=ans*ans) ans++;
	return ans;
}
int B;
struct segtree{
  vi t;
  int n;
  segtree() {
    n=B;
    t.resize(2*n+2,1e6);
  }
 
  void modify(int p, int value) {  // set value at position p
    for (t[p += n] = value; p > 1; p >>= 1) t[p>>1] = min(t[p],t[p^1]);
  }
 
  int query(int l, int r) {
    int res = 1e6;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l&1) res = min(res,t[l++]);
      if (r&1) res = min(res,t[--r]);
    }
    return res;
  }
};
 
int main(){
  ios::sync_with_stdio(false);
#ifndef NEAL_DEBUG
  cin.tie(nullptr);
#endif
  /*freopen("names.txt", "r", stdin);
  freopen("names.csv", "w", stdout);*/
  int xs,ys,xd,yd; cin >> xs >> ys >> xd >> yd;
  cin >> B;
  int c0; cin >> c0;
  int t; cin >> t;
  vl c(t+1);
  c[0] = c0;
  for(int i=1; i<=t; i++) cin >> c[i];
  int n; cin >> n;
  V<pl> cd(n);
  for(int i=0; i<n; i++){
  	cin >> cd[i].f >> cd[i].s;
  	int l; cin >> l;
  	for(int j=0; j<l; j++){
  		int k,m; cin >> k >> m;
  		d[i].pb({k,c[m]});
  		d[k].pb({i,c[m]});
	}
  }
  pi S = mp(xs,ys); pi D = mp(xd,yd);
  ll ans = 1e6;
  if(dist(S,D)<=B) ans = c[0]*dist(S,D);
  else{
  	cout << -1 << endl;
  	return 0;
  }
  V<array<int,3>> que;
  V < segtree > el(n);
  for(int i=0; i<n; i++){
  	int dd = dist(S,cd[i]);
  	if(dd<B){
  		que.pb({i,dd,dd*c[0]});
  		el[i].modify(dd,dd*c[0]);
	}
  }
  for(int j=0; j<que.size(); j++){
  	int i = que[j][0], km = que[j][1], v = que[j][2];
  	int ex = dist(cd[i],D);
  	if(ex+km>B) continue;
  	ans = min(ans, v + ex*c[0]);
  	for(pi k: d[i]){
  		int dd = dist(cd[i],cd[k.f]);
  		int nkm = dd + km, nv = v+dd*k.s;
  		if(nkm<B and nv<el[k.f].query(0,nkm+1)){
  			que.pb({k.f,nkm,nv});
  			el[k.f].modify(nkm,nv);
		}
	}
  }
  cout << ans << endl;
}
