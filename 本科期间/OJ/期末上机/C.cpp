#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <map>
#include <set>
#define REP(I,S,N) for (I=S;I<N;I++)
#define rREP(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
const int maxn=1e6+7;
const int INF=0x3f3f3f3f;
using namespace std;
typedef long long LL;
priority_queue<LL> Q;
int main(){
    int T,n,m,i,j,k;
    while (~scanf("%d",&n)){
        LL ans=0;
        FOR(i,1,n) scanf("%d",&k),Q.push(-k);
        while (Q.size()>1){
            LL t=Q.top();Q.pop();
            t+=Q.top();Q.pop();
            ans-=t;Q.push(t);
        }Q.pop();
        printf("%lld\n",ans);
    }
}