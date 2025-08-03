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
const LL maxn=1e5+107;
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
int n,m,q;
// char str[maxn];//倒着的

//sort: 第一关键字为length; 第二关键字是: i>i+1: pos; other: n+n-pos
//可以后缀平衡树维护rank; 也可以直接维护rank! 倒着来

int A[maxn];
int S[maxn],top;//倒着的
int id[maxn],val[maxn];
int ans[maxn];
int check(int s,int t){//i<j
	while (s&&t&&S[s]==S[t]) s--,t--;
	if (s&&t) return S[s]<S[t];
	else return 1;
}
int main() {
	int _,T;
	scanf("%d",&T);
	FOR(_,1,T){
		int i,j,k,n;
		scanf("%d",&n);
		FOR(i,1,n) scanf("%d",&A[i]);
		FOR(k,1,10){
			rFOR(i,1,n){
				string now=to_string(A[i]);
				if ((int)now.length()<k) continue;
				if ((int)now.length()>k) {
					rREP(j,now.length()) S[++top]=now[j];
				} else if ((int)now.length()==k){
					int pre=top;
					rREP(j,now.length()) S[++top]=now[j];
					if (check(top,pre)) val[i]=i;
					else val[i]=n+n-i;
				}
			}
		}
		// FOR(i,1,n) printf("%d ",val[i]); puts("<- val");//delete
		FOR(i,1,n) id[i]=i;
		sort(id+1,id+1+n,[](int i,int j){
			if (to_string(A[i]).length()!=to_string(A[j]).length())
				return to_string(A[i]).length()<to_string(A[j]).length();
			else return val[i]<val[j];
		});
		// FOR(i,1,n) printf("%d ",id[i]); puts("<- id");//delete
		FOR(i,1,n*50) ans[i]=0;
		int maxtop=1;
		FOR(i,1,n) {
			top=0; A[id[i]]=-1;
			rFOR(j,1,n) if (A[j]!=-1){
				string now=to_string(A[j]); int t;
				rREP(t,now.length()) ans[++top]+=now[t]-'0';
			} maxtop=max(top,maxtop);
			// rFOR(j,1,maxtop) printf("%d ",ans[j]); puts("");
			FOR(j,1,n) if (A[j]!=-1) printf("%d",A[j]); puts("");
		} 
		FOR(i,1,maxtop) {
			ans[i+1]+=ans[i]/10; ans[i]%=10;
			if (ans[maxtop+1]) maxtop++;
		}
		printf("Case #%d: ",_);
		rFOR(i,1,maxtop) printf("%d",ans[i]); puts("");
	}
}
/*
100
8
123 123 124 123126 124 122 122 123
8
123 123 122 122126 124 122 122 123
8
123 123 122 121126 124 122 122 123
*/