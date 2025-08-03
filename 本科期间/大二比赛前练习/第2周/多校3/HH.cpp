#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <utility>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef long long LL;
typedef unsigned long long ULL;
const LL maxn=15e6+7;
const LL M=1e9+7;
const LL INF=0x3f3f3f3fll;
const double eps=0.000001;

//维护val //left,right各一个 
int T;
int l,r;
int l0,l1,r0,r1;
int n,k;
LL ans;
int a[maxn];
int nxt[maxn][2];
LL num[maxn];
LL num11[maxn],num00[maxn],num01[maxn];
int cnt;
void insert(int x){
    int now=0,i;
    rREP(i,32){
        int mark=((x&(1<<i))!=0);
        if (!nxt[now][mark]) nxt[now][mark]=++cnt;
        if (nxt[now][1]&&mark==1) num11[nxt[now][1]]+=num[nxt[now][1]];
        if (nxt[now][0]&&mark==0) num00[nxt[now][0]]+=num[nxt[now][0]];
        if (nxt[now][1]&&nxt[now][0]){
            num01[nxt[now][1]]+=num[nxt[now][0]];
        }
        now=nxt[now][mark];
        num[now]++;
    }
}
void calc(int x){
    int now=0,i;
    rREP(i,32){
        int mark=((x&(1<<i))!=0);
        if (mark==1&&nxt[now][0]) ans+=num00[nxt[now][0]];
        if (mark==0&&nxt[now][1]) ans+=num11[nxt[now][1]];
        if (!nxt[now][mark]) return;
        now=nxt[now][mark];
    }
}
int main()
{
    int i;
    scanf("%d",&T);
    while (T--){
        ans=0;
        cnt=0;
        scanf("%d",&n);
        FOR(i,1,n) scanf("%d",&a[i]);
        FOR(i,1,n){
            calc(a[i]);
            insert(a[i]);
            printf("%d ",ans);
        }
        printf("%lld\n",ans);
        FOR(i,0,cnt) num[i]=num00[i]=num11[i]=num01[i]=nxt[i][0]=nxt[i][1]=0;
    }
}
/*
5
5
1 5 4 2 3
*/
