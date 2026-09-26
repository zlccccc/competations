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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,i;
int pos[maxn];
char c[maxn];
int fa[maxn],F[maxn];
int pre[255],len[255];
LL ans;
int main(){
	scanf("%d",&n);
	FOR(i,1,n) cin>>pos[i]>>c[i];
	FOR(i,1,n){
    	if (c[i]=='G'){
        	if (pre['B']){
            	ans+=pos[i]-pre['B'];
            	len['B']=max(len['B'],pos[i]-pre['B']);
            }if (pre['R']){
            	ans+=pos[i]-pre['R'];
            	len['R']=max(len['R'],pos[i]-pre['R']);
            }if (pre['G']){
            	if (len['B']+len['R']>pos[i]-pre['G']){
                	ans-=len['B']+len['R'];
                	ans+=pos[i]-pre['G'];
                }
            }pre['B']=pre['R']=pos[i];
        	len['B']=len['R']=0;
        }else if (pre[c[i]]){
        	ans+=pos[i]-pre[c[i]]; 
        	len[c[i]]=max(len[c[i]],pos[i]-pre[c[i]]);
        }pre[c[i]]=pos[i];
    } 
	printf("%I64d\n",ans);
}
/*d
*/
