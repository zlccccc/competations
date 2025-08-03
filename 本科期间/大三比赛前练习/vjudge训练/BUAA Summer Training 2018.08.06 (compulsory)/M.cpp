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
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
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
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
int n,m,q;
char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}


struct node{
	int x,y,p;
	node(int x=0,int y=0,int p=0):x(x),y(y),p(p){};
}T[maxn]; int tot;
vector<int> V;
int MAX[maxn];
inline int lowbit(int x) {return x&-x;}
inline void add(int x,int val){
	for (;x<=(int)V.size();x+=lowbit(x)) max_(MAX[x],val);
}
inline int get(int x){
	int ret=-INF;
	for (;x;x-=lowbit(x)) max_(ret,MAX[x]);
	return ret;
}
inline int getid(int x){
	return lower_bound(V.begin(),V.end(),x)-V.begin()+1;
}
int main() {
	int i;
	scanf("%d",&n);
	int x,y;
	int xh,yh,xw,yw;
	scanf("%d%d%d%d",&xh,&yh,&xw,&yw);
	int mask=1;
	if (xh>xw) swap(xh,xw),swap(yh,yw);
	if (yh>yw) yh=-yh,yw=-yw,mask=-1;
	T[++tot]=node(xh,yh,0);
	T[++tot]=node(xw,yw,2);
	V.push_back(yh); V.push_back(yw);
	while (n--){
		scanf("%d%d",&x,&y);
		y*=mask;
		T[++tot]=node(x,y,1);
		V.push_back(y);
	}
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(), V.end()),V.end());
	FOR(i,0,(int)V.size()) MAX[i]=-INF;
	sort(T+1,T+1+tot,[](node A,node B){
		if (A.x!=B.x) return A.x<B.x;
		if (A.y!=B.y) return A.y<B.y;
		return A.p<B.p;
	});
	FOR(i,1,tot){
		if (T[i].p==0) add(getid(T[i].y),0);
		else{
			int now=get(getid(T[i].y));
			if (T[i].p==2) return 0*printf("%d\n",now);
			add(getid(T[i].y),now+1);
		}
	}
}
/*
*/
