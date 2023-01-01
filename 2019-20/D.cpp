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
 
mt19937_64 mt_rand(chrono::high_resolution_clock::now().time_since_epoch().count());
uniform_int_distribution<long long> rg(1,1e18);
 
struct base{
	int pt;
	base* nxt;
	base (){};
	base(int pt): pt(pt), nxt(nullptr){};
	base(int pt, base* nxt): pt(pt), nxt(nxt){};
};
 
void out(base* ft, int ct){
	if(!ft){
		cout << "False" << endl;
		exit(0);
	}
	if(ct==1){
		if(!(ft->nxt)){
			cout << "False" << endl;
			exit(0);
		}
	}
}
 
map < pi, int > ind;
V < pi > rind;
 
void init(){
	for(int i=0; i<50000; i++){
		rind.pb(pi{i,-1});
		ind[pi{i,-1}] = i;
	}
}
base* operate(string DNA){
	auto ft = new base(0);
	for(int i=1; i<50000; i++){
		ft = new base(i,ft);
	}
	each(x,DNA){
		if(x=='C') ft = new base(ft->pt,ft);
		if(x=='D'){
			ft = ft->nxt;
			out(ft,0);
		}
		if(x=='L'){
			out(ft,0);
			int pt = ft->pt;
			pi pt2 = rind[pt];
			if(pt2.s==-1) return nullptr;
			ft->pt = pt2.f;
		}
		if(x=='P'){
			out(ft,1);
			int a = ft->pt, b = ft->nxt->pt;
			int c; 
			if(ind.find(pi{a,b})!=ind.end()){
				c = ind[pi{a,b}];
				ft = ft->nxt; ft->pt = c;
			}
			else{
				c = sz(rind); rind.pb({a,b}); ind[pi{a,b}] = c;
				ft = ft->nxt; ft->pt = c;
			}
			
		}
		if(x=='R'){
			out(ft,0);
			int pt = ft->pt;
			pi pt2 = rind[pt];
			if(pt2.s==-1) return nullptr;
			ft->pt = pt2.s;
		}
		if(x=='S'){
			out(ft,1);
			int a = ft->pt, b = ft->nxt->pt;
			ft->pt = b; ft->nxt->pt = a;
		}
		if(x=='U'){
			out(ft,0);
			int pt = ft->pt;
			pi pt2 = rind[pt];
			if(pt2.s==-1) return nullptr;
			int a = pt2.f, b = pt2.s;
			ft->pt = b;
			ft = new base(a,ft);
		}
	}
	return ft;
}
 
int main(){
  ios::sync_with_stdio(false);
#ifndef NEAL_DEBUG
  cin.tie(nullptr);
#endif
  /*freopen("names.txt", "r", stdin);
  freopen("names.csv", "w", stdout);*/
  init();
  string a,b;
  cin >> a >> b;
  auto ft1 = operate(a), ft2 = operate(b);
  //cout << rind << endl;
  vi newid;
  map < pi, int > nmp;
  for(int i=0; i<sz(rind); i++){
  	int a = rind[i].f, b = rind[i].s;
  	if(a!=-1 and a<i) a = newid[a];
  	if(b!=-1 and b<i) b = newid[b];
  	if(a>b) swap(a,b);
  	if(nmp.find({a,b})!=nmp.end()) newid.pb(nmp[{a,b}]);
	else{
		nmp[{a,b}] = sz(nmp);
		newid.pb(nmp[{a,b}]);
	}
  }
  while(ft1 or ft2){
  	if(!ft1){
	  	if(!ft2) cout << "True" << endl;
	  	else cout << "False" << endl;
	  	return 0;
 	}
 	if(!ft2){
 		cout << "False" << endl;
 		return 0;
 	}
 	if(newid[ft1->pt] == newid[ft2->pt]){
 		out(ft1,0); out(ft2,0);
 		ft1 = ft1->nxt;
 		ft2 = ft2->nxt;
 		continue;
	}
 	cout << "False" << endl;
 	return 0;
  }
  cout << "True" << endl;
 
}
