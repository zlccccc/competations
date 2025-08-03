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
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

//struct node{
//	int l,r,val;
//}T[maxn*200];
//void Update(int x,int pos,int L,int R){
//	if (!x) x=cnt;
//	if (L==R) T[x].val++,return;
//	int mid=(L+R)/2;
//	if (mid>=pos) Update(T[x].l,pos,L,mid);
//	else Update(T[x].r,pos,mid+1,R);
//}
//void Query(int x,int pos,int L,int R){
//	if (!x) return 0;
//	if (L==R) return T[x].val;
//	int mid=(L+R)/2;
//	if (mid>=pos) return Query(T[x].l,pos,L,mid);
//	else return Query(T[x].r,pos,mid+1,R);
//}
//int root[maxn];
int n,m;
int i,j,k;
map<int,int> MP[maxn];
inline int lowbit(int x){
	return x&-x;
}
void update(int val){
	
}
int query(int pos,int val){
	
}
inline int gethash(int pos,int len){
	int i,ret=0;
	rep(i,pos,pos+len) ret=ret*26+a[i];
	return ret;
}
int query(int l,int r,int val){
	if (r-len>l) return 0*puts("-1");
	return query()
}
void solve(int x){
	
}
int main(){
	int T;
	scanf("%d",&T);
	while (T--) solve();
}
/*
*/
