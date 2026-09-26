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
const LL M=998244353;
const LL maxn=1e6+7;
const double eps=0.00000001;
const double pi=acos(-1.0);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

#define MP make_pair
typedef pair<int,int> pii;
int n,m,i,j,k;
char a[507][507];
int f[507][507][2];
queue<pair<pii,int> > Q;
int ax[]={-1,1,0,0};
int ay[]={0,0,1,-1};
int main(){
    scanf("%d%d",&n,&m);
    REP(i,n) scanf("%s",a[i]);
    REP(i,n) REP(j,m){
        f[i][j][0]=f[i][j][1]=INF;
        if (a[i][j]=='S') Q.push(MP(MP(i,j),0)),f[i][j][0]=0;
    }while (Q.size()){
        auto now=Q.front();Q.pop();
        i=now.first.first;j=now.first.second;
        int t=now.second;
//        printf("%d %d %d;%c\n",i,j,t,a[i][j]);
        if (a[i][j]=='K'){t=1;f[i][j][1]=f[i][j][0];}
        REP(k,4){
            int x=i+ax[k],y=j+ay[k];
            if (0<=x&&x<n&&0<=y&&y<m&&f[x][y][t]==INF){
                if (a[x][y]=='.'||a[x][y]=='K'||a[x][y]=='S'||a[x][y]=='E'||(a[x][y]=='D'&&t)){
                    f[x][y][t]=f[i][j][t]+1;
                    Q.push(MP(MP(x,y),t));
                }
            }
        }
    }REP(i,n) REP(j,m){
        if (a[i][j]=='E'){
            int ans=min(f[i][j][0],f[i][j][1]);
            if (ans!=INF) printf("%d\n",ans);
            else puts("-1");
        }
    }
}
/*
4 12
WWWWWWWWWWWW
WE.W.S..W.KW
W..D..W....W
WWWWWWWWWWWW
*/
