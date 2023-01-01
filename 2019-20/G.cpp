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
 
int cg[210][210];
 
int main(){
  ios::sync_with_stdio(false);
#ifndef NEAL_DEBUG
  cin.tie(nullptr);
#endif
  /*freopen("names.txt", "r", stdin);
  freopen("names.csv", "w", stdout);*/
  int s, l, n;
  cin >> s >> l >> n;
  V<string> ani(s);
  each(x,ani) cin >> x;
  sort(all(ani));
  map < string, int > mp;
  for(int i=0; i<sz(ani); i++) mp[ani[i]] = i;
  for(int i=0; i<l; i++){
  	string a,b; cin >> a >> b;
  	cg[mp[a]][mp[b]] = 1;
  	cg[mp[b]][mp[a]] = 1;
  }
  for(int i=0; i<s; i++) cg[i][s] = cg[s][i] = 1;
  vi a(n);
  for(int i=0; i<n; i++){
  	string s; cin >> s; 
	a[i] = mp[s];
  }
  V<vi> pos(s);
  for(int i=n-1; i>=0; i--){
  	pos[a[i]].pb(i);
  }
  vi mx(s,-1);
  for(int i=0; i<s; i++){
  	int &j = mx[i];
  	while((j+1)<n and cg[a[j+1]][i]) j++;
  }
  vi ans;
  for(int i=0; i<n; i++){
  	int mn = s;
  	for(int j=0; j<s; j++){
  		if(pos[j].empty()) continue;
  		if(pos[j].back()==mx[j]+1){
  			mn = min(mn,j);
		}
	}
	ans.pb(mn);
	a[pos[mn].back()] = s;
	pos[mn].pop_back();
	for(int i=0; i<s; i++){
		int &j = mx[i];
		while((j+1)<n and cg[a[j+1]][i]) j++;
	}
  }
  each(x,ans) cout << ani[x] << ' ';
  cout << endl;
 
}
