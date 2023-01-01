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
 
vi solve(int ch, V<vi> cp){
	int n = sz(cp), m = sz(cp[0]);
	V<vi> gd(n,vi(m,0));
	if(ch==-1) gd = V<vi>(n,vi(m,1));
	auto change = [&](int i, int j)->void{
		gd[i][j] = 1-gd[i][j];
		if(i-1>=0) gd[i-1][j] = 1-gd[i-1][j];
		if(i+1<n) gd[i+1][j] = 1-gd[i+1][j];
		if(j-1>=0) gd[i][j-1] = 1-gd[i][j-1];
		if(j+1<m) gd[i][j+1] = 1-gd[i][j+1];
	};
	if(ch!=-1) change(ch,0);
	for(int j=1; j<m; j++){
		for(int i=0; i<n; i++){
			if(gd[i][j-1]!=cp[i][j-1]) change(i,j);
		}
	}
	vi ret;
	for(int i=0; i<n; i++) ret.pb(gd[i][m-1]);
	return ret;
}
 
V<vi> T(V<vi> a){
	int n = sz(a), m = sz(a[0]);
	V < vi > b(m,vi(n));
	for(int i=0; i<n; i++) for(int j=0; j<m; j++) b[j][i] = a[i][j];
	return b;
}
 
vi gauss(V<vi> e){
	int n = sz(e);
	int j = 0;
	auto op = [&](vi &a, vi b){
		int m = sz(a);
		for(int i=0; i<m; i++) a[i] = a[i]^b[i];
	};
	
	vi where;
	for(int i=0; i<n; i++){
		int fd = -1;
		for(int k=j; k<n; k++) if(e[k][i]){
			fd = k; break;
		}
		if(fd!=-1){
			swap(e[fd],e[j]);
			for(int k=j+1; k<n; k++) if(e[k][i]) op(e[k],e[j]);
			where.pb(i);
			j++;
		}
	}
	vi ans(n,0);
	for(int i=j-1; i>=0; i--){
		int w = where[i];
		ans[w] = e[i][n];
		for(int k=w+1; k<n; k++) ans[w]^=(ans[k]&e[i][k]);
	}
	for(int i=0; i<n; i++){
		int v = 0;
		for(int j=0; j<n; j++) v^=(ans[j]&e[i][j]);
		if(v!=e[i][n]) return vi(n,-1);
	}
	return ans;
}
 
int main(){
  ios::sync_with_stdio(false);
#ifndef NEAL_DEBUG
  cin.tie(nullptr);
#endif
  /*freopen("names.txt", "r", stdin);
  freopen("names.csv", "w", stdout);*/
  int n,m;
  cin >> n >> m;
  bool sw=false;
  V< vi > a;
  if(n<=m){
  	a = V<vi>(n,vi(m));
  	for(int i=0; i<n; i++){
  		for(int j=0; j<m; j++){
  			string x; cin >> x; a[i][j] = x[0]=='W';
		}
	}
  }
  else{
  	sw = true;
  	a = V<vi> (m,vi(n));
  	for(int i=0; i<n; i++) for(int j=0; j<m; j++){
  		string x; cin >> x; a[j][i] = x[0]=='W';
	  }
	swap(n,m);
  }
  vi nat = solve(-1,a);
  for(int i=0; i<n; i++) nat[i]^=a[i][m-1];
  V<vi> changes;
  for(int i=0; i<n; i++){
  	changes.pb(solve(i,V<vi>(n,vi(m,0))));
  }
  changes.pb(nat);
  vi ans = gauss(T(changes));
  if(ans[0]==-1){
  	cout << "IMPOSSIBLE" << endl;
  	return 0;
  }
  V<vi> click(n,vi(m,0));
  V<vi> gd(n,vi(m,1));
  auto change = [&](int i, int j)->void{
  		click[i][j]^=1;
		gd[i][j] = 1-gd[i][j];
		if(i-1>=0) gd[i-1][j] = 1-gd[i-1][j];
		if(i+1<n) gd[i+1][j] = 1-gd[i+1][j];
		if(j-1>=0) gd[i][j-1] = 1-gd[i][j-1];
		if(j+1<m) gd[i][j+1] = 1-gd[i][j+1];
	};
	for(int i=0; i<n; i++) if(ans[i]) change(i,0);
	
	for(int j=1; j<m; j++){
		for(int i=0; i<n; i++){
			if(gd[i][j-1]!=a[i][j-1]) change(i,j);
			
		}
		
	}
	if(sw){
		for(int j=0; j<m; j++){
			for(int i=0; i<n; i++){
				if(click[i][j]) cout << "P ";
				else cout << "A ";
			}
			cout << endl;
		}
		return 0;
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(click[i][j]) cout << "P ";
			else cout << "A ";
		}
		cout << endl;
	}
}
