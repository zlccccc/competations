#include <bits/stdc++.h>
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
using namespace std;
const int MAX=105;
int t;
int n,R,r;
int dis;
struct node{
    int x,y,dis,id;
    bool operator<(const node &z)const{
        return dis<z.dis;
    }
}a[MAX];
bool cmp(node a,node b){
    return a.id<b.id;
}
int lim,cnt;
vector<node>an;
#define pb push_back
char s[100005];
int main(){
    int T,n,m;
    int cnt1,cnt2;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        scanf("%s",s);
        m--;
        cnt1=0;
        cnt2=0;
        for(int i=1;i<=m;i++)
            if(s[i]=='R')
                cnt1++;
        for(int i=m;i<n-1;i++)
            if(s[i]=='L')
                cnt2++;
        printf("%d\n",min(cnt1,cnt2));
    }
    return 0;
}
/*
2
3 10 5
3 4
3 5
3 6
3 10 4
-7 -6
4 5
5 4
*/
