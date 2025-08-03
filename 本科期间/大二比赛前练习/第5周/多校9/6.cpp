#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <stack>
#include <queue>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL maxn=1e5+7;
const double eps=0.00000001;
const LL INF=0x3f3f3f3f;
const LL INFF=0x1f3f3f3f3f3f3f3fll;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
inline LL min(LL a,LL b) {return a>b?b:a;}
inline LL max(LL a,LL b) {return a<b?b:a;}
inline LL abs(LL a,LL b) {return a>0?a:-a;}
inline double abs(double a) {return a>0?a:-a;}
inline LL powMM(LL a,LL b){
    LL ret=1;
    while (b){
        if (b&1) ret=ret*a%M;
        a=a*a%M;
        b>>=1;
    }
    return ret;
}
struct node{
	int n,len;
	node(int _n=0,int _len=0){len=_len;n=_n;} 
	bool operator <(const node &A)const{
		if (len==0) return 1;
		if (A.len==0) return 0
		if (len==A.len) return n>A.n;
		return len>A.len;
	}
};
priority_queue<node> Q;
vector<node> E[maxn],F[maxn];
int n,m,q;
int cnt1[maxn],cnt2[maxn];
node len1[maxn],len2[maxn];
int U[maxn];
int i,j;
int main(){
	int T;
	scanf("%d",&T);
    while (T--){
    	scanf("%d%d",&n,&m);
    	REP(i,m){
    		int u,v,len;
    		scanf("%d%d%d",&u,&v,&len);
    		E[u].push_back(node(v,len));
    		F[u].push_back(node(u,len));
		}
		FOR(i,1,n) len1[i]=len2[i]=INF;
		scanf("%d",&q);
		REP(i,q) scanf("%d",&U[i]);
		REP(i,q) Q.push(node(U[i],0));
		while (Q.size()){
			node now;
			for (node x:E[now.n]){
				if (node(now.n,now.len+x.len)<cnt2[x.n]){
					len2[x.n]=node(now.n,now.len+x.len);
				}
				if (len1[x.n]<len2[x.n]) swap(len1[x.n],len2[x.n]);// '<' <==> '>'
			}
		}
		REP(i,q) Q.push(node(U[i],0));
		while (Q.size()){
			node now;
			for (node x:F[now.n]){
				if (node(now.n,now.len+x.len)<cnt2[x.n])
					len2[x.n]=node(now.n,now.len+x.len);
				if (len1[x.n]<len2[x.n]) swap(len1[x.n],len2[x.n]);// '<' <==> '>'
			}
		}
	}
}
/*
*/

