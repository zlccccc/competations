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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

vector<int> H;
int n,m;
int l[maxn],r[maxn],now,L,R;
inline int getid(int x){
	return lower_bound(H.begin(),H.end(),x)-H.begin();
}
int T;
int i;
int ans,nowans;
int a[maxn];
int main(){
	while (~scanf("%d%d",&n,&m)){
		H.clear();
		REP(i,n){
			scanf("%d%d",&l[i],&r[i]);
			H.push_back(l[i]-1);
			H.push_back(l[i]);
			H.push_back(r[i]);
			H.push_back(r[i]+1);
		}
		sort(H.begin(),H.end());H.erase(unique(H.begin(),H.end()),H.end());
		REP(i,H.size()) a[i]=0;
		REP(i,n){
			a[getid(l[i])]++;
			a[getid(r[i]+1)]--;
		}
		n=H.size();
		rep(i,1,n) a[i]+=a[i-1];
//		REP(i,H.size()) printf("%d ",H[i]);puts("");
//		REP(i,H.size()) printf("%d ",a[i]);puts("");
		now=0;L=R=0;
		ans=0;
		REP(L,n){
			if (L!=0&&a[L]==0) now-=H[L]-H[L-1];
			if (a[L]==0) continue;
			while (R<n&&(a[R]!=0||m>=now+H[R]-H[R-1])){
				if (R!=0&&a[R]==0) now+=H[R]-H[R-1];
				R++;
			}
			nowans=H[R-1]+m-now-H[L]+1;
//			printf("%d %d %d  %d\n",L,R,now,nowans);
			ans=max(ans,nowans);
		}
		printf("%d\n",ans);
	}
}
/*
2
1 3
*/
