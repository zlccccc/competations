#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <string>
#include <cstring>
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> pii;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3f;
const int maxn=1e6+7;

int len2;
int S[maxn<<2];
int lowbit(int x){return x&-x;}
int sum(int x){
    int ret=0;
    while (x) ret+=S[x],x-=lowbit(x);
    return ret;
}
int sum(int l,int r){
    return sum(r)-sum(l-1);
}
void add(int x){
    while (x<=len2) S[x]++,x+=lowbit(x);
}
vector<int> pos[maxn];
char s[maxn],str[maxn];
int p[maxn];
int main(){
    int i,j,T;
	scanf("%d",&T);
    while (T--){
        scanf("%s",s);
        int len1=strlen(s);
        len2=0;
        str[0]='+';
        str[1]='%';
        REP(i,len1+1){
            str[i*2+2]=s[i];
            str[i*2+3]='%';
        }len2=len1*2+2;
        int id=0,mx=0;
        FOR(i,1,len2-1){
            if (mx>i) p[i]=min(p[2*id-i],mx-i);
            else p[i]=1;
            while (str[i+p[i]]==str[i-p[i]]) p[i]++;
            if (p[i]+i>mx) mx=p[i]+i,id=i;
        }
        LL ans=0;
 //       FOR(i,1,len2-1) if (str[i]=='%'&&p[i]>=5) ans++;
        REP(i,len1-3) if (s[i]==s[i+2]&&s[i+1]==s[i+3])ans++;
        FOR(i,1,len2-1) if (str[i]!='%') pos[p[i]].push_back(i);
 //       FOR(i,0,len2) printf("%2c",str[i]);puts("");
//        FOR(i,0,len2) printf("%2d",p[i]);puts("");
//        printf("%d ",ans);
        rFOR(i,6,len2){
            for (int q=0;q<pos[i].size();q++){
                int v=pos[i][q];
                ans+=sum(v-(i-2),v-4);
                ans+=sum(v+4,v+(i-2));
                add(v);
            }
        }
 //       puts("OK");
        printf("%lld\n",ans);
        FOR(i,0,len2) S[i]=0;
        FOR(i,0,len2) pos[i].clear();
    }
	return 0;
}
/*
*/
