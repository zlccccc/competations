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
#include <list>
#include <unordered_map>
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
const LL maxn=5e5+107;
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

ll getid(char s[]) {
	int len=strlen(s),i; ll ret=0;
	REP(i,len) ret=ret*10+s[i]-'0';
	ret+=len*10000000000ll;
	// printf("ret=%lld\n",ret);
	return ret;
}
int v[maxn];
//id: pair<id.ans>
typedef list<pair<int,ll> >::iterator lit;
unordered_map<ll,lit> MP;//MP:pair<id,time>; Q:pair<time,id>
list<pair<int,ll> > Q;
int main() {
	int T,_; T=1;
	scanf("%d",&T);
	FOR(_,1,T){
		int i,q,m;
		scanf("%d%d",&q,&m);
		Q.clear(); MP.clear();
		REP(i,q) {
			int opt; char s[20];
			scanf("%d%s%d",&opt,s,&v[i]);
			ll id=getid(s);
			if (opt==0) {
				unordered_map<ll,lit>::iterator it=MP.find(id);
				if (it!=MP.end()) {
					v[i]=v[it->second->first];
					lit pos=MP[id];
					Q.erase(pos);
					MP.erase(id);
				} 
				Q.push_back(make_pair(i,id));
				lit nxt=Q.end(); nxt--;
				MP[id]=nxt;
				printf("%d\n",v[i]);
				if ((int)MP.size()>m) {
					id=Q.begin()->second;
					Q.pop_front();
					MP.erase(id);
				}
			} else {
				unordered_map<ll,lit>::iterator itt=MP.find(id);
				if (itt!=MP.end()) {
					lit it=MP[id];
					if (v[i]==1) {
						it++; if (it==Q.end()) {
							puts("Invalid");
							continue;
						}
					} else if (v[i]==-1) {
						if (it==Q.begin()) {
							puts("Invalid");
							continue;
						} it--;
					} 
					// printf("query id=%lld\n",it->second);
					printf("%d\n",v[it->first]);
				} else {
					puts("Invalid");
				}
			}
			// for (auto v:Q) printf("inside: %d %lld\n",v.first,v.second); 
		}
	}
}
/*

*/