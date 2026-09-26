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
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,pos,N) for (I=pos;I<N;I++)
#define rrep(I,pos,N) for (I=N-1;I>=pos;I--)
#define FOR(I,pos,N) for (I=pos;I<=N;I++)
#define rFOR(I,pos,N) for (I=N;I>=pos;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=4e4+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}

#define x x_x
#define y y_y
LL n,m,T;
LL i,j,k,t,ans;
priority_queue<LL> Q; 
int main(){
	scanf("%d",&T);
	while (T--){
		scanf("%d",&n);
		REP(i,n) {
			scanf("%d",&k);
			Q.push(-k);
		}
		ans=0;
		while (Q.size()>1){
			t=Q.top();Q.pop();t+=Q.top();Q.pop();
			Q.push(t);
			ans+=t;
//			printf("%d\n",t);
		}
		Q.pop();
		printf("%I64d\n",-ans);
	}
}
/*
*/
