#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}


int n,m;
int i,j;
char c;
int a[maxn],pos[maxn];
set<int> S;
set<int>::iterator it;
int ans;
int main(){
	while (~scanf("%d",&n)){
		ans=-1;S.clear();
		memset(a,0,sizeof(a));
		memset(pos,0,sizeof(pos));
		FOR(i,1,n){
			cin>>c;
			if (c=='?') S.insert(i);
			else {
				cin>>j;
				if (c=='I'){
					if (!a[j]) a[j]=1;
					else{
						it=S.upper_bound(pos[j]);
						if (it!=S.end()) S.erase(*it);
						else if (ans==-1) ans=i;
					}pos[j]=i;
				}
				else{
					if (a[j]) a[j]=0;
					else{
						it=S.upper_bound(pos[j]);
						if (it!=S.end()) S.erase(*it);
						else if (ans==-1) ans=i;
					}pos[j]=i;
				}
			}
		}
		printf("%d\n",ans);
	}
}
/*
*/
