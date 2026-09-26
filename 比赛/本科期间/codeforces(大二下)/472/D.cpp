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
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define dbg(x) cout <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cout <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct fraction{
	LL A,B;
	fraction(){}
	fraction(int _A,int _B):A(_A),B(_B){}
	bool operator < (const fraction &B)const{
		if (B.B*this->B>0) return this->A*B.B < this->B*B.A;
		return this->A*B.B > this->B*B.A;
	}
}A[maxn];
pair<fraction,fraction> B[maxn];
int n,w;
int i,j,k;
LL ans;
int val[maxn];
inline int lowbit(int x) {return x&-x;}
void update(int x){
	// printf("upd:%d\n",x);
	for (;x<=n;x+=lowbit(x)) val[x]++;
}int query(int x){
	int ret=0;
	for (;x;x-=lowbit(x)) ret+=val[x];
	return ret;
}
int main(){
	scanf("%d%d",&n,&w);
	FOR(i,1,n){
		int x,v;
		scanf("%d%d",&x,&v);
		A[i]=fraction(x,v-w);
		B[i]=make_pair(fraction(x,-v-w),A[i]);
	}sort(A+1,A+n+1);
	sort(B+1,B+n+1);
	FOR(i,1,n){
		int pos=lower_bound(A+1,A+1+n,B[i].second)-A;
		ans+=query(pos);
		update(pos);
		// printf("pos %d:%I64d %I64d\n",pos,A[pos].A,A[pos].B);
		// dbgln(ans);
	}
	// FOR(i,1,n) printf("%d",B[i]);
	printf("%I64d\n",ans);
}
/*
*/
