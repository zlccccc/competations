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
#include <unordered_map>
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

int n,m;
LL A[maxn],B[maxn];int fa[maxn];
inline int getfa(int x){
    if (fa[x]==x) return x;
    int ret=getfa(fa[x]);
    A[x]+=A[fa[x]];fa[x]=ret;
    return ret;
}
int addedge(int u,int v,int val){//u=v+val
    int x=getfa(u),y=getfa(v);
    if (x==y){
        if (A[u]-A[v]==val) return 1;
        return 0;
    }fa[x]=y;
    A[x]=val+A[v]-A[u];
    return 1;
}char ans[maxn];
unordered_map<LL,int> G[maxn];

char buffer[24000000],*buf=buffer;
void read(int &x){
    for(x=0;(*buf<'0'||*buf>'9')&&*buf!='-';++buf);
    int flag=1;if (*buf=='-') flag=-1,buf++;
    while('0'<=*buf&&*buf<='9')x=x*10+*buf-48,++buf;
    x*=flag;
}
int main(){
    int i,j,k;
    fread(buffer,1,24000000,stdin);
    read(n);read(m);
//    scanf("%d%d",&n,&m);getchar();
    FOR(i,1,n*2) fa[i]=i;
    REP(i,m){
//        puts("OK");
        int u,v,val;char c;
        read(u);
        while (c=*buf,c!='+'&&c!='-') buf++;buf++;
        read(v);read(val);
//        scanf("a[%d]%ca[%d]=%d",&u,&c,&v,&val);getchar();
        u++;v++;
        int x=getfa(u),y=getfa(u+n),X=getfa(v),Y=getfa(v+n);
        if (x!=y||X!=Y){
            if (c=='-'){
                int now=addedge(u,v,val);//u=v+val
                ans[i]=now+'0';if (!now) continue;
                addedge(u+n,v+n,-val);//-v=-u+val
            }else{
                int now=addedge(u,n+v,val);//u=-v+val
                ans[i]=now+'0';if (!now) continue;
                addedge(u+n,v,-val);//v=-u+val
            }
        }else{
            if (c=='-'){
                if (A[u]-A[u+n]-A[v]+A[v+n]==val*2) ans[i]='1';
                else ans[i]='0';
            }else{
                if (A[u]-A[u+n]+A[v]-A[v+n]==val*2) ans[i]='1';
                else ans[i]='0';
            }
        }
//        printf("%d %c %d = %d\n",u,c,v,val);
    }ans[m]='\0';
    puts(ans);
    FOR(i,1,n){
        int x=getfa(i),y=getfa(i+n);
        if (x!=y){
            if (x<=n) G[x][-A[i]]++;
            else G[y][-A[i+n]]++;
        }
    }FOR(i,1,n) if (fa[i]==i){
        auto ans=make_pair(0,0ll);
        for (auto now:G[i]) ans=max(ans,make_pair(now.second,now.first));
        B[i]=ans.second;
    }
//    FOR(i,1,n*2) printf("%d(%d) \n",A[i],fa[i]);puts("");
    FOR(i,1,n){
        double Ans;
        int x=getfa(i),y=getfa(i+n);
        if (x==y){
            Ans=(A[i]-A[i+n])/2.0;
        }else {
            if (x<=n) Ans=A[i]+B[x];
            else Ans=-A[i+n]-B[y];
        }
//        printf("cal %d : %d %d; %d %d\n",i,x.first,x.second,y.first,y.second);
        printf("%.1f\n",Ans);
    }
}
/*
2 4
a[0]+a[1]=2
a[1]-a[0]=1
a[0]-a[1]=-1
a[1]+a[0]=-1000
*/
