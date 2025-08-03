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
const LL maxn=1000000+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

#include<cstdio>
#include<cstring>
#include<cmath>
#define maxn 1010
#define ll long long
#define bas 100000000
#define mem(a,b) for(ll i=0;i<=len;i++)a[i]=b[i];
#define mes(a)   for(ll i=0;i<=len;i++)a[i]=0;
using namespace std;
ll len,a[maxn],l[maxn],r[maxn],mid[maxn],ans[maxn],x[maxn];
char s[maxn];
ll max(ll x,ll y){
    return x>y?x:y;
}
void plu(ll a[maxn],ll b[maxn]){
    ll c[maxn];mes(c);
    c[0]=max(a[0],b[0]);
    for(int i=1;i<=c[0];i++){
        c[i]+=a[i]+b[i];
        if(c[i]>=bas){
            c[i+1]++;c[i]%=bas;
        }
    }
    if(c[c[0]+1])c[0]++;
    mem(mid,c);
}
void Plu(ll a[maxn],ll b){
    ll p=1,c[maxn];mes(c);
    mem(c,a);c[p]++;
    while(c[p]>=bas){
        c[p]%=bas;c[p+1]++;p++;
    }
    if(c[c[0]+1])c[0]++;
    mem(l,c);
}
void miu(ll a[maxn],ll b){
    ll p=1,c[maxn];mes(c);
    mem(c,a);c[p]--;
    while(c[p]<0){
        c[p]+=bas;c[p+1]--;p++;
    }
    if(c[c[0]]==0)c[0]--;
    mem(r,c);
}
void mul(ll a[maxn],ll b[maxn],ll c[maxn]){
    for(int i=1;i<=a[0];i++){
        for(int j=1;j<=b[0];j++){
            c[i+j-1]+=a[i]*b[j];
            if(c[i+j-1]>=bas){
                c[i+j]+=c[i+j-1]/bas;
                c[i+j-1]%=bas;
            }
        }
        ll len=i+b[0];
        while(c[len]>=bas){
            c[len+1]+=c[len]/bas;
            c[len]%=bas;len++;
        }
    }
    for(int i=a[0]+b[0];i>=1;i--)
        if(c[i]){
            c[0]=i;break;
        }
}
void div(ll a[maxn],ll b){
    ll c[maxn];mes(c);
    for(int i=a[0];i>=1;i--){
        c[i]=a[i+1]%b*bas+a[i];
        c[i]=c[i]/b;
    }
    for(int i=a[0];i>=1;i--)
        if(c[i]){
            c[0]=i;break;
        }
    mem(a,c);
}
bool cmp(ll a[maxn],ll b[maxn]){
    if(a[0]>b[0])return 0;
    if(a[0]<b[0])return 1;
    for(ll i=a[0];i>=1;i--){
        if(a[i]>b[i])return 0;
        if(a[i]<b[i])return 1;
    }
    return 1;
}
bool Judge(){
    memset(x,0,sizeof(x));
    mul(mid,mid,x);
    return cmp(x,a);
}
void solve2()
{
    scanf("%s",s);
    a[0]=strlen(s);len=a[0];x[0]=0;
    for(int i=1;i<=a[0];i++)
        a[i]=s[a[0]-i]-'0';
    for(int i=1;i<=len;i+=8)
        x[++x[0]]=a[i+7]*10000000+a[i+6]*1000000+a[i+5]*100000+
        a[i+4]*10000+a[i+3]*1000+a[i+2]*100+a[i+1]*10+a[i];
    mem(a,x);
    mem(r,a);r[0]=a[0]/2+1;
    while(cmp(l,r)){
        plu(l,r);
        div(mid,2);
        if(Judge()){
            mem(ans,mid);
            Plu(mid,1);
        }
        else miu(mid,1);
    }
//    printf("%lld",ans[ans[0]]);
//    for(ll i=ans[0]-1;i>=1;i--)
//        printf("%08lld",ans[i]);
    printf("%d\n",ans[1]%2);
}
int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        solve2();
    }
}
/*
*/
