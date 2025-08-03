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
	LL A[3][3];
	node(){
		A[0][0]=1;A[0][1]=0;A[0][2]=0;
		A[1][0]=0;A[1][1]=1;A[1][2]=0;
		A[2][0]=0;A[2][1]=0;A[2][2]=1;
	}
	node operator*(node X)const{
		node ret;
		for(int i=0;i<=2;i++)
			for(int j=0;j<=2;j++)
				ret.A[i][j]=(A[i][0]*X.A[0][j]+A[i][1]*X.A[1][j]+A[i][2]*X.A[2][j])%M;
		return ret;
	}
}mul[2],ans;
char val[maxn];
node sum[maxn<<2];
bool flip[maxn<<2];
void rev(node &x){
	swap(x.A[1][0],x.A[0][1]);
	swap(x.A[1][1],x.A[0][0]);
	swap(x.A[2][1],x.A[2][0]);
}
void pushdown(int x){
	if (flip[x]){
		flip[x<<1]^=1;
		flip[x<<1|1]^=1;
		rev(sum[x<<1]);
		rev(sum[x<<1|1]);
		flip[x]=0;
	}
}
void pushup(int x){
	sum[x]=sum[x<<1]*sum[x<<1|1];
}
void build(int x,int l,int r){
	flip[x]=0;
	if (l==r){
		if (val[l]=='1') sum[x]=mul[1];
		if (val[l]=='0') sum[x]=mul[0];
		return;
	}
	int mid=(l+r)/2;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	pushup(x);
}
void update(int x,int l,int r,int L,int R){
	if (l<=L&&R<=r){
		flip[x]^=1;
		rev(sum[x]);
		return;
	}
	int mid=(L+R)/2;
	pushdown(x);
	if (mid>=l) update(x<<1,l,r,L,mid);
	if (r>mid) update(x<<1|1,l,r,mid+1,R);
	pushup(x);
}
node query(int x,int l,int r,int L,int R){
	if (l<=L&&R<=r) return sum[x];
	node ret;
	int mid=(L+R)/2;
	pushdown(x);
	if (mid>=l) ret=ret*query(x<<1,l,r,L,mid);
	if (r>mid) ret=ret*query(x<<1|1,l,r,mid+1,R);
	pushup(x);
	return ret;
}
int n,m;
int i,j,k;
int main(){
	mul[0].A[1][0]=1;
	mul[0].A[2][0]=1;
	mul[1].A[0][1]=1;
	mul[1].A[2][1]=1;
	int T;
	scanf("%d",&T);
	while (T--){
		scanf("%d%d",&n,&m);
		scanf("%s",val+1);
		build(1,1,n);
		REP(i,m){
			int l,r;
			scanf("%d%d%d",&k,&l,&r);
			if (k==1){
				update(1,l,r,1,n);
			}else{
				ans=query(1,l,r,1,n);
//				printf("%d %d %d\n",ans.A[0][0],ans.A[0][1],ans.A[0][2]);
//				printf("%d %d %d\n",ans.A[1][0],ans.A[1][1],ans.A[1][2]);
//				printf("%d %d %d\n",ans.A[2][0],ans.A[2][1],ans.A[2][2]);
				printf("%lld\n",(ans.A[2][0]+ans.A[2][1])%M);
			}
		}
	}
}
/*
*/

