#include <bits/stdc++.h>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
 
#define DEBUG
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
const LL maxn=2e5+107;

int n,m;
vector<pair<pii,int> > ans;
queue<pair<pii,int> > Q;
int A[1007][1007];
void check(int x,int y) {//check if could paint
    if (x==0||y==0||x==n||y==m) return;
    int col=-1,dx,dy;
    REP(dx,2) REP(dy,2) {
        if (A[x+dx][y+dy]!=col&&A[x+dx][y+dy]!=-1&&col!=-1) return;
        else if (col==-1) col=A[x+dx][y+dy];
    }
    if (col==-1) return;
    REP(dx,2) REP(dy,2) A[x+dx][y+dy]=-1;
    Q.push(make_pair(make_pair(x,y),col));
    ans.push_back(make_pair(make_pair(x,y),col));
}
int main() {
    /*to solve the problem*/
    int i,j;
    scanf("%d%d",&n,&m);
    FOR(i,1,n) FOR(j,1,m) scanf("%d",&A[i][j]);
    FOR(i,1,n-1) FOR(j,1,m-1) check(i,j);
    while (Q.size()) {
        auto now=Q.front(); Q.pop();
        int x=now.first.first,y=now.first.second;
        // printf("paint %d %d %d\n",x,y,now.second);
        // if (A[x][y]==-1&&A[x+1][y]==-1&&A[x][y+1]==-1&&A[x+1][y+1]==-1) continue;//at least paint one
        check(x-1,y-1); check(x-1,y); check(x-1,y+1);
        check(x,y-1); check(x,y+1);
        check(x+1,y-1); check(x+1,y); check(x+1,y+1);
    }
    FOR(i,1,n) FOR(j,1,m) if (A[i][j]!=-1) return 0*puts("-1");
    printf("%d\n",(int)ans.size());
    reverse(ans.begin(), ans.end());
    for (auto now:ans) printf("%d %d %d\n",now.first.first,now.first.second,now.second);
}
/*
*/