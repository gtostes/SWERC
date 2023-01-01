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
 
int main(){
  ios::sync_with_stdio(false);
#ifndef NEAL_DEBUG
  cin.tie(nullptr);
#endif
  /*freopen("names.txt", "r", stdin);
  freopen("names.csv", "w", stdout);*/
  int n,m,t; cin >> n >> m >> t;
  V<vi> adj(n);
  vi pos(n,0);
  vi at(n,-1);
  V<pi> que;
  for(int i=0; i<m; i++){
  	int a,b; cin >> a >> b;
  	if(a==t) continue;
  	if(b!=t) adj[b].pb(a);
  	if(b==t){
  		pos[a]=1;
  		at[a] = a;
  		que.pb({a,a});
  	}
  }
  for(int k=0; k<sz(que); k++){
  	int i = que[k].f, e = que[k].s;
  	for(int j: adj[i]){
  		if(at[j]==n) continue;
  		if(at[j]==-1){
  			at[j] = e;
  			que.pb({j,e});
		}
		if(at[j]!=-1 and at[j]!=e){
			at[j] = n;
			que.pb({j,e});
		}
	}
  }
  vi ans;
  for(int i=0; i<n; i++){
  	if(pos[i] and at[i]==i) ans.pb(i);
  }
  cout << sz(ans) << endl;
  each(x,ans) cout << x << endl;
}
