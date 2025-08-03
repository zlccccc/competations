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
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

int n;
int A[maxn];
struct node {
	int x,y,z;
	node(int _x,int _y,int _z):x(_x),y(_y),z(_z) {}
};
vector<node> ans,mor;
vector<int> changes,tmp;
int pre[maxn],vis[maxn];
queue<int> Q;
bool calc(int val,int len) {//还有个base
	int i;
	tmp.push_back((1<<0)|(1<<1)|(1<<2));
	tmp.push_back((1<<0)|(1<<2)|(1<<4));
	tmp.push_back((1<<0)|(1<<3)|(1<<6));
	tmp.push_back((1<<0)|(1<<4)|(1<<8));
	tmp.push_back((1<<0)|(1<<5)|(1<<10));
	tmp.push_back((1<<0)|(1<<6)|(1<<12));
	tmp.push_back((1<<0)|(1<<7)|(1<<14));
	tmp.push_back((1<<0)|(1<<8)|(1<<16));
	REP(i,15) for (int v:tmp) if ((v<<i)<(1<<len))
			changes.push_back(v<<i);
	// printf("%d\n",(int)changes.size());
	// pr2(val,len);
	// printf("len=%d\n",len);
	Q.push(0); vis[0]=1;
	while (Q.size()) {
		int x=Q.front(); Q.pop();
		for (int trans:changes)
			if (!vis[x^trans]){
				// pr2(trans,len); pr2(x^trans,len); puts("");
				pre[x^trans]=x;
				vis[x^trans]=1;
				Q.push(x^trans);
			}
	} if (vis[val]) {
		// printf("val=%d\n",val);
		for (int x=val; x; x=pre[x]) {
			int nowtrans=x^pre[x];
			// pr2(nowtrans,len);
			tmp.clear();
			REP(i,len) if ((nowtrans>>i)&1) tmp.push_back(i);
			mor.push_back(node(tmp[0],tmp[1],tmp[2]));
		}
		return 1;
	} // 得有base
	return 0;
}
bool rev;//reversed
inline int g(int x) {
	if (rev) return n-x+1;
	else return x;
}
void _flip(int x,int y,int z) {
	x=g(x); y=g(y); z=g(z);
	// printf("flip: %d %d %d\n",x,y,z);
	ans.push_back(node(x,y,z));
	A[x]^=1; A[y]^=1; A[z]^=1;
}
int l,r;
inline void reverse() {
	int tmp=l;
	l=n-r+1; r=n-tmp+1;
	rev^=1;
}
int main() {
	int i;
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",&A[i]);
	l=1,r=n;
	while (l+16<=r) {
		if (A[g(l)]&&A[g(l+1)]&&A[g(l+2)]) {
			_flip(l,l+1,l+2);
			l+=3;
		} else if (A[g(l)]&&A[g(l+2)]) {
			_flip(l,l+2,l+4);
			l+=3;
		} else if (A[g(l)]&&A[g(l+1)]) {
			//wait
			if (A[g(r)]&&A[g(r-1)]&&!A[g(r-2)]) {
				if ((l+r)&1) {
					_flip(l,(l+r-1)/2,r-1);
					_flip(l+1,(l+1+r)/2,r);
				} else {
					_flip(l,(l+r)/2,r);
					_flip(l+1,(l+r)/2,r-1);
				} l+=3; r-=3;
			} else reverse();
		} else if (A[g(l)]) {
			_flip(l,l+3,l+6);
			l+=3;
		} else {
			l++;
		}
		// printf("l=%d,r=%d\n",l,r);
	} int val=0;
	FOR(i,l,r) val|=A[g(i)]<<(i-l);
	if (calc(val,r-l+1)) {
		puts("YES");
		for (node x:mor) _flip(x.x+l,x.y+l,x.z+l);
		printf("%d\n",(int)ans.size());
		for (node x:ans) printf("%d %d %d\n",x.x,x.y,x.z);
		// FOR(i,1,n) printf("%d ",A[i]);
	} else {
		puts("NO");
	}
}
/*
30
0 1 0 0 0 1 1 0 1 1 1 1 0 1 1 0 1 0 1 1 1 1 1 0 0 0 1 0 0 0 0 0 1 0 1 1 1 0 0 0 

26
0 1 0 0 0 1 1 0 1 1 1 1 0 1 1 0 1 0 0 0 0 0 0 0 1 1 
*/