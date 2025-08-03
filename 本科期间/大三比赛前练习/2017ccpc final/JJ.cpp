#include <bits/stdc++.h>
#define maxn 2020
#define inf 0x3f3f3f3f
#define REP(i,x,y) for(int i=x;i<(y);i++)
#define RREP(i,x,y) for(int i=x;i>(y);i--)
using namespace std;
typedef long long ll;
typedef pair<int,ll> pii;
int n,m,cnt[maxn],vis[maxn];
ll x,dis[maxn];
vector<pii>e[maxn];
int spfa() {
    memset(dis,0x3f,sizeof(dis));
    memset(cnt,0,sizeof(cnt));
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++) e[0].push_back(make_pair(i,0));
    cnt[0]++;
    dis[0]=0;vis[0]=1;
    queue<int>que;
    que.push(0);
    while(!que.empty()) {
        int now=que.front();que.pop();
        for(int i=0;i<e[now].size();i++) {
            int nxt=e[now][i].first;ll len=e[now][i].second;
            if(dis[nxt]>dis[now]+len) {
                dis[nxt]=dis[now]+len;
                if(!vis[nxt]) {
                    vis[nxt]=1;
                    que.push(nxt);
                    cnt[nxt]++;
                    if(cnt[nxt]>n+1) return -1;
                }
            }
        }
        vis[now]=0;
    }
}
int main()
{
    int T,cas=1;scanf("%d",&T);
    while(T--) {
        scanf("%d %d",&n,&m);
        for(int i=0;i<=n;i++) e[i].clear();
        scanf("%I64d",&x);
        REP(i,1,m+1) {
            int A,B,C,D;scanf("%d %d %d %d",&A,&B,&C,&D);
            if(A==B) {
                if(C==D) {
                    e[D].push_back(make_pair(A,-x));
                    e[B].push_back(make_pair(C,x));
                }
                else {
                    e[B].push_back(make_pair(C,x-1));
                    e[D].push_back(make_pair(A,-x-1));
                }
            }
            else {
                if(C==D) {
                    e[B].push_back(make_pair(C,x-1));
                    e[D].push_back(make_pair(A,-x-1));
                }
                else {
                    e[B].push_back(make_pair(C,x-1));
                    e[D].push_back(make_pair(A,-x-1));
                }
            }
        }
        REP(i,1,n)
            e[i+1].push_back(make_pair(i,-1));
        int flag=spfa();
        printf("Case #%d: ",cas++);
        if(flag==-1) puts("IMPOSSIBLE");
        else {
            for(int i=2;i<=n;i++) {
                if(i!=2) printf(" ");
                printf("%I64d",dis[i]-dis[i-1]);
            }
            puts("");
        }
    }
}