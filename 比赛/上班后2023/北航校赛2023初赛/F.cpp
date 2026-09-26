// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define REP_(I,N) for (int I=0,END=(N);I<END;I++)
#define rREP_(I,N) for (int I=(N)-1;I>=0;I--)
#define rep_(I,S,N) for (int I=(S),END=(N);I<END;I++)
#define rrep_(I,S,N) for (int I=(N)-1,START=(S);I>=START;I--)
#define FOR_(I,S,N) for (int I=(S),END=(N);I<=END;I++)
#define rFOR_(I,S,N) for (int I=(N),START=(S);I>=START;I--)

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
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
template<typename T>inline T gcd(T a, T b) {return b?gcd(b,a%b):a;}
template<typename T>inline void add_(T &A,int B,ll MOD) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T fastgcd(T a, T b) {
    int az=__builtin_ctz(a),bz=__builtin_ctz(b),z=min(az,bz),diff; b>>=bz;
    while (a) {
        a>>=az; diff=b-a; az=__builtin_ctz(diff);
        min_(b,a); a=abs(diff);
    }
    return b<<z;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
typedef array<int,4> ar4;
typedef array<int,3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

 // "1234567"
vector<string> Str={
    "1110111", // 0
    "0010010", // 1
    "1011101", // 2
    "1011011", // 3
    "0111010", // 4
    "1101011", // 5
    "1101111", // 6
    "1010010", // 7
    "1111111", // 8
    "1111011"  // 9
};

int f[10][10],g[10][10];
void init() {
    REP_(i,10) {
        REP_(j,10) {
            REP_(k,Str[i].size()) {
                if (Str[i][k]=='1'&&Str[j][k]=='0') f[i][j]++;
                if (Str[i][k]=='0'&&Str[j][k]=='1') g[i][j]++;
            }
        }
    }
    // REP_(i,10) {
    //     REP_(j,10) printf("(%d,%d) ",f[i][j],g[i][j]); puts("");
    // }
}
int k;
string A,B,C; int op;
map<array<int,5>,bool> MP;
bool Check(int id,int x,int y,int op,int add) {
    array<int,5> cur={id,x,y,op,add};
    if (MP.count(cur)) return MP[cur];
    // printf("check id=%d (%d %d) operation=%d add=%d\n",id,x,y,op,add);
    if (id==max(A.length(),max(B.length(),C.length()))) {
        if (add==0&&x==y) return true; else return false;
    }
    FOR_(a,0,9) FOR_(b,0,9) {
        int c=a+b*op+add,newadd=0;
        while (c<0) c+=10,newadd--;
        while (c>=10) c-=10,newadd++;
        if (id&&a==0&&id==A.length()-1) continue;  // 前导0
        if (id&&b==0&&id==B.length()-1) continue;  // 前导0
        if (id&&c==0&&id==C.length()-1) continue;  // 前导0
        if (id>=A.length()&&a!=0) continue;
        if (id>=B.length()&&b!=0) continue;
        if (id>=C.length()&&c!=0) continue;
        int ax=x,ay=y;
        if (id<A.length()) ax+=f[A[id]-'0'][a],ay+=g[A[id]-'0'][a];
        if (id<B.length()) ax+=f[B[id]-'0'][b],ay+=g[B[id]-'0'][b];
        if (id<C.length()) ax+=f[C[id]-'0'][c],ay+=g[C[id]-'0'][c];
        if (ax>k||ay>k) continue;
        // printf("dfs-down depth=%d a=%d; b=%d; c=%d; ax=%d; ay=%d;; %d -> %d\n",id,a,b,c,ax,ay,A[id]-'0',a);
        if (Check(id+1,ax,ay,op,newadd)) return MP[cur]=true;
    }
    return MP[cur]=false;
}
int solve() {
    string str;
    cin>>str>>k;  // 先修改加减
    A=B=C=""; MP.clear();
    {
        int start=0;
        for (;start<str.size();start++) {
            char &c=str[start];
            if (c=='+') {op=1; break;}
            if (c=='-') {op=-1; break;}
            A+=c;
        } start++;
        for (;start<str.size();start++) {
            char &c=str[start];
            if (c=='=') break;
            B+=c;
        } start++;
        for (;start<str.size();start++) {
            char &c=str[start];
            if (c=='=') break;
            C+=c;
        } start++;
    }
    reverse(A.begin(),A.end());
    reverse(B.begin(),B.end());
    reverse(C.begin(),C.end());

    // cout<<A<<" "<<B<<" "<<C<<endl;

    bool okay=false;
    if (Check(0,0,0,op,0)) okay=true; // 不更换op
    if (op==1&&Check(0,1,0,-1,0)) okay=true;
    if (op==-1&&Check(0,0,1,1,0)) okay=true;

    if (okay) puts("Yes");
    else puts("No");
    return 0;
}
int main() {
    init();
    int T; T=1;
    scanf("%d",&T);
    FOR_(_,1,T){
        solve();
    }
}
/*
5
5+6=9
1
1+1=999
4
547+283=192
2
0-0=0
3
111+222=33
5

*/