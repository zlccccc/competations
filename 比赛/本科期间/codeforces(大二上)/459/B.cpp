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

int n,m;
int i,j,k;
int a[maxn];
vector<pair<int,char> > edge[maxn];
char f[107][107][255][2];
void dfs(int x,int y,char a,char mark){
    if (f[x][y][a][mark-'A']) return;
    if (mark=='A'){
        f[x][y][a][0]='B';
        for (auto e:edge[x]) if (e.second>=a){
            dfs(e.first,y,e.second,'B');
            if (f[e.first][y][e.second][1]==mark) f[x][y][a][0]=mark;
        }
    }else{
        f[x][y][a][1]='A';
        for (auto e:edge[y]) if (e.second>=a){
            dfs(x,e.first,e.second,'A');
            if (f[x][e.first][e.second][0]==mark) f[x][y][a][1]=mark;
        }
    }
}
int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,m){
        int u,v;char c;
        cin>>u>>v>>c;
        edge[u].push_back(make_pair(v,c));
    }FOR(i,1,n) FOR(j,1,n) dfs(i,j,'a','A');
    FOR(i,1,n){
        FOR(j,1,n) printf("%c",f[i][j]['a'][0]);
        puts("");
    }
}
/*
*/
