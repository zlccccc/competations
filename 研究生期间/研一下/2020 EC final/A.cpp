#include <sstream>
#include <fstream>
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
#include <cassert>
#include <bitset>
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
const LL maxn=1e6+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline ll powMM(ll a, ll b, ll mod=M) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

char str[maxn];
int bruteforce(string s) {
    int ret=0;
    int a1,a2,a3,a4,a5,a6,n=strlen(str);
    REP(a1,n) {
        rep(a2,a1+1,n) {
            rep(a3,a2+1,n) {
                rep(a4,a3+1,n) {
                    rep(a5,a4+1,n) {
                        rep(a6,a5+1,n) {
                            char t[7]; int mark=1,i,j;
                            t[0]=str[a1]; t[1]=str[a2]; t[2]=str[a3];
                            t[3]=str[a4]; t[4]=str[a5]; t[5]=str[a6];
                            REP(i,6) REP(j,6) if ((s[i]==s[j])!=(t[i]==t[j])) mark=0;
                            ret+=mark;
                            // cout<<"calc "<<s<<" "<<t<<"\n";
                        }
                    }
                }
            }
        }
    }
    return ret;
}
map<char,int> MP;
int A[maxn];
ll MOM[67][67],NAMO[67][67],NAMOM[67][67],NAM[67][67],OOM[67][67];
ll MO[67][67],NA[67],AX[67],CNT[67];
int namall,nam[67],namo[67],mom[67],namom[67],oom[67],na,mo[67],ax[67];
bool flag[67];
int main() {
    int n,ans=0;
    int tot=0,i,k;
    FOR(i,'a','z') MP[i]=tot++;
    FOR(i,'A','Z') MP[i]=tot++;
    FOR(i,'0','9') MP[i]=tot++;
    // printf("tot=%d\n",tot);
    scanf("%s",str);
    n=strlen(str);
    // printf("%d\n",bruteforce("namomo"));
    // printf("%d\n",bruteforce("namomo"));
    // printf("%d\n",bruteforce("namomo"));
    REP(i,n) A[i+1]=MP[str[i]];
    FOR(i,1,n) flag[A[i]]=1;
    FOR(i,1,n) {//left
        namall=0; na=0;
        REP(k,tot) if (k!=A[i]) {
            add_(na,CNT[k]);
            ax[k]=CNT[k];//axm
            add_(namall,(M+NA[k]-MO[A[i]][k])%M);//NAx-xax
            mo[k]=CNT[k];
            mom[k]=MO[A[i]][k];//MOM
            nam[k]=(((NA[k]-MO[A[i]][k])+(AX[k]-MO[k][A[i]]))%M+M)%M;//XAM and AXM
            //-(CNT[k]*(CNT[k]-1)/2)

            // oom[k]=CNT[k]*(CNT[k]-1)/2%M;//OOM
            namo[k]=NAM[A[i]][k];//XOM;OXM
            namom[k]=NAMO[A[i]][k];
            add_(ans,NAMOM[A[i]][k]);
        }
        // printf("%d ",namall); puts(" <- namall");
        // // REP(k,tot) if (flag[k]) printf("%d ",oom[k]); puts(" <- oom");
        // // REP(k,tot) if (flag[k]) printf("%d ",namall-nam[k]);
        // REP(k,tot) if (flag[k]) printf("%d ",nam[k]);
        // printf(" <- nam  "); printf("  namall=%d  ",namall);
        // REP(k,tot) if (flag[k]) {
        //     int a,b;
        //     int cnt=0;
        //     // FOR(a,1,i-1) FOR(b,a+1,i-1) if (A[a]!=k&&A[b]!=k&&A[a]!=A[i]&&A[b]!=A[i]) cnt++;
        //     FOR(a,1,i-1) FOR(b,a+1,i-1) if ((A[a]==k||A[b]==k)&&A[a]!=A[i]&&A[b]!=A[i]) cnt++;
        //     printf("%d ",cnt);
        // } printf(" should  ");
        // // REP(k,tot) if (flag[k]) printf("%lld ",NA[k]);
        // REP(k,tot)if (flag[k]) printf("%lld ",AX[k]); printf(" ax ");
        // REP(k,tot)if (flag[k]) printf("%d ",ax[k]);
        // puts("<- AX XA");
        // // REP(k,tot) printf("%d ",MO[k][A[i]]);
        // // REP(k,tot) if (flag[k]) printf("%d ",mo[k]); puts(" <- mo");


        add_(CNT[A[i]],1);
        add_(NA[A[i]],na);
        // REP(k,tot) if (k!=A[i]) add_(NAM[i][A[i]],(C1[k]-(ll)C0[k]*(C0[k]-1)/2)%M+M);//oox
        // REP(k,tot) if (k!=A[i]) add_(NAM[i][A[i]],M-MOM[i][k]);//xox
        // REP(k,tot) if (k!=A[i]) OOM[i][k]=(OOM[pre][k]+)%M;//oox
        // REP(k,tot) add_(NAM[i][k],NAM[i-1][k]);
        REP(k,tot) if (k!=A[i]) {
            add_(AX[k],ax[k]);
            add_(MO[k][A[i]],mo[k]);
            add_(NAM[k][A[i]],(namall-nam[k]+M)%M);
            add_(MOM[k][A[i]],mom[k]);
            // add_(OOM[k][A[i]],oom[k]);
            add_(NAMO[k][A[i]],namo[k]);
            add_(NAMOM[k][A[i]],namom[k]);
        }
    }
    // puts("");
    // FOR(i,1,n) {
    // FOR(i,1,n) {REP(k,tot) if (CNT[n][k]) printf("%d ",NAM[i][k]); puts(" <- NOM");} puts("");
    // FOR(i,1,n) {REP(k,tot) if (CNT[n][k]) printf("%d ",OOM[i][k]); puts(" <- OOM");} puts("");
    // REP(k,tot) PRE[k]=n+1;
    // rFOR(i,1,n) {//left
    //     int pre=PRE[A[i]];
    //     REP(k,tot) if (k!=A[i]) {
    //         MOM[i][k]=(MOM[pre][k]+(CNT[n][A[i]]-CNT[pre-1][A[i]])*(CNT[pre][k]-CNT[i][k]))%M;//xox;
    //         add_(ans,(NAM[i-1][k]+M-OOM[pid[i][k]][A[i]])*MOM[i][k]%M);
    //     }
    //     PRE[A[i]]=i;
    // }
    // FOR(i,1,n) {REP(k,tot) if (CNT[n][k]) printf("%d ",MOM[i][k]); puts(" <- MOM");} puts("");
    printf("%d\n",ans);
}
/*
owowohahah
wohahah
oohaha
hahaha
anmomomomomomo
abcdcdcdcdcdcd
ababababcdcdcdcdcdcd
aaabcdabcdabcd
*/