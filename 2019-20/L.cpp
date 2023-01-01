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
 
int solve(V<vi> adj, int minmsk){
	int n = sz(adj);
	int mk = 1ll << n;
	vi win(mk,-1);
	win[mk-1] = 0;
	
	auto calc = [&](int msk, const auto& self)->int{
		if(win[msk]!=-1) return win[msk];
		set < int > tr;
		for(int i=0; i<n; i++){
			if((msk>>i)&1) continue;
			int nmsk = msk + (1<<i);
			for(int j: adj[i]) nmsk|=(1<<j);
			tr.insert(self(nmsk,self));
 		}
 		int u = 0;
 		while(1){
		 if(tr.empty() or *tr.begin()!=u){
		 	win[msk] = u;
		 	break;
		 }
		 tr.erase(tr.begin());
		 u++;
		}
		return win[msk];
	};
	
	return calc(minmsk,calc);
}
 
int main(){
  ios::sync_with_stdio(false);
#ifndef NEAL_DEBUG
  cin.tie(nullptr);
#endif
  /*freopen("names.txt", "r", stdin);
  freopen("names.csv", "w", stdout);*/
  int n; cin >> n;
  V<string> gd(n);
  each(x,gd) cin >> x;
  
  V<vi> elem(n,vi(n,0));
  
  auto cote = [&](int i, int j)->int{
  	if(gd[i][j]=='*') return 0;
  	if(i-1>=0 and gd[i-1][j]=='*') return elem[i-1][j];
  	if(i+1<n and gd[i+1][j]=='*') return elem[i+1][j];
  	if(j-1>=0 and gd[i][j-1]=='*') return elem[i][j-1];
  	if(j+1<n and gd[i][j+1]=='*') return elem[i][j+1];
  	return 0;
  };
 
  
  
  auto dfs = [&](int i, int j, int c, const auto& self)->void{
  	if(i<0 or i>=n or j<0 or j>=n) return;
  	if(elem[i][j]) return;
  	if(gd[i][j]!='*') return;
  	elem[i][j] = c;
  	self(i-1,j,c,self); self(i+1,j,c,self);
  	self(i,j-1,c,self); self(i,j+1,c,self);
  };
  int c = 0;
  for(int i=0; i<n; i++){
  	for(int j=0; j<n; j++){
  		if(!elem[i][j] and gd[i][j]=='*') dfs(i,j,++c,dfs);
	}
  }
  
  auto pt = [&](int i, int j)->int{
  	if(gd[i][j]=='*') return 0;
  	if(i-1>=0 and gd[i-1][j]=='*') return elem[i-1][j];
  	if(i+1<n and gd[i+1][j]=='*') return elem[i+1][j];
  	if(j-1>=0 and gd[i][j-1]=='*') return elem[i][j-1];
  	if(j+1<n and gd[i][j+1]=='*') return elem[i][j+1];
  	return 0;
  };
  
  V<vi> id(n,vi(n,0));
  auto dfs2 = [&](int i, int j, int c, const auto& self)->void{
  	if(id[i][j]) return;
  	id[i][j] = c;
  	int ld = pt(i,j);
  	if(i-1>=0 and pt(i-1,j)==ld) self(i-1,j,c,self);
  	if(i+1<n and pt(i+1,j)==ld) self(i+1,j,c,self);
  	if(j-1>=0 and pt(i,j-1)==ld) self(i,j-1,c,self);
  	if(j+1<n and pt(i,j+1)==ld) self(i,j+1,c,self);
  };
  
  
  c = 0;
  for(int i=0; i<n; i++){
  	for(int j=0; j<n; j++){
  		if(pt(i,j)!=0 and !id[i][j]) dfs2(i,j,++c,dfs2);
	}
  }
  V< V<pi> > cb(c+1);
  //cout << endl;
  for(int i=0; i<n; i++){
  	for(int j=0; j<n; j++){
  		//cout << id[i][j] << ' ';
  		cb[id[i][j]].pb({i,j});
	  }
	  //cout << endl;
  }
  
  auto dist = [&](pi a, pi b)->int{
  	return abs(a.f-b.f)+abs(a.s-b.s);
  };
  
  int w = 0;
  for(int i=1; i<=c; i++){
  	int s = sz(cb[i]);
  	V<vi> adj(s);
  	for(int e=0; e<s; e++){
  		for(int v=0; v<s; v++){
  			if(dist(cb[i][e],cb[i][v])==1) adj[e].pb(v);
		}
	}
	int minmsk = 0;
	for(int e=0; e<s; e++){
		pi p = cb[i][e];
		if(gd[p.f][p.s]=='x') minmsk+=1ll<<e;
	}
	
	int ans = solve(adj,minmsk); //cout << "lol" _ ans _ i<< endl;
	w^=ans;
  }
  
  if(w) cout << "First player will win" << endl;
  else cout << "Second player will win" << endl;
}
