#include <sstream>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <utility>
#include <cassert>
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)

#define DEBUG
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline ll powMM(ll a, ll b, ll mod=M) {
	ll ret=1;
	for (; b; b>>=1ll,a=a*a%mod)
		if (b&1) ret=ret*a%mod;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

string str[27];
vector<pair<string,int> > V;
int prefix[maxn];
int main(){
	int n,i;
	scanf("%d",&n);
	FOR(i,1,n) cin>>str[i];
	V.push_back(make_pair("",0));
	FOR(i,1,n) {
		vector<pair<string,int> > tmp;
		int l=str[i].size();
		int sta,j;
		rep(sta,1,(1<<l)) {
			string now="";
			REP(j,l) if ((sta>>j)&1) now+=str[i][j];
			int pos=lower_bound(V.begin(),V.end(),make_pair(now,0))-V.begin()-1;
			// cout<<now<<pos;
			if (pos<0) continue;
			tmp.push_back(make_pair(now,V[pos].second+(int)now.size()));
		} sort(tmp.begin(), tmp.end());
		rep(j,1,(int)tmp.size()) tmp[j].second=max(tmp[j].second,tmp[j-1].second);
		V.swap(tmp);
		if (!V.size()) break;
		// for (auto now:V) cout<<"("<<now.first<<" "<<now.second<<"); "; puts("");
	} int ans=-1;
	for (auto now:V) ans=max(ans,now.second);
	printf("%d\n",ans);
}
/*
3
AAAA
AAAA
AAAA
*/