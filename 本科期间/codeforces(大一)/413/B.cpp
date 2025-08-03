#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
#include <cmath>
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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1,a*=a) ret=1ll*ret*a%M;return ret;}

struct node{
	int price,pos,i;
	operator <(const node&A)const{
		if (price==A.price) return pos<A.pos;
		return price<A.price;
	}
}k;
vector<node> A[4];
bool used[maxn];
int p[maxn];
int pos[4];
int n,m;
int i,j,t,d;
int tot1,tot2;
int main(){
	scanf("%d",&n);
	REP(i,n) scanf("%d",&p[i]);
	REP(i,n) {
		scanf("%d",&k.i);
		k.price=p[i];k.pos=i;
		A[k.i].push_back(k);
	}
	REP(i,n) {
		scanf("%d",&k.i);
		k.price=p[i];k.pos=i;
		A[k.i].push_back(k);
	}
	sort(A[1].begin(),A[1].end());
	sort(A[2].begin(),A[2].end());
	sort(A[3].begin(),A[3].end());
	scanf("%d",&m);
	REP(i,m){
		scanf("%d",&j);
		while (pos[j]<A[j].size()&&used[A[j][pos[j]].pos]) pos[j]++;
		if (pos[j]==A[j].size()){
			printf("-1 ");
			continue;
		}
		used[A[j][pos[j]].pos]=1;
		printf("%d ",A[j][pos[j]].price); 
	}
}
