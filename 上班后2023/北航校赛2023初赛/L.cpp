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


int wa[maxn],wb[maxn],wv[maxn],ws1[maxn];
int cmp(int *r,int a,int b,int l) {
    return r[a]==r[b]&&r[a+l]==r[b+l];
}
//sa->pos(后缀排名->pos)
void da(int *r,int *sa,int n,int m) {
    r[n++]=0;//使rank从1开始(sa[0]=n)
    int i,j,p,*x=wa,*y=wb,*t;
    REP_(i,m) ws1[i]=0;//pre-cmp
    REP_(i,n) ws1[x[i]=r[i]]++;//r->x
    rep_(i,1,m) ws1[i]+=ws1[i-1];
    rREP_(i,n) sa[--ws1[x[i]]]=i;//sort(计数排序)
    for (j=1,p=1; p<n; j<<=1,m=p) { //j->2^x
        p=0; rep_(i,n-j,n) y[p++]=i; //最后j个是不用加(显然)
        REP_(i,n) if (sa[i]>=j) y[p++]=sa[i]-j;//后缀顺序
        REP_(i,n) wv[i]=x[y[i]];//x+y->wv(由于后缀顺序)
        REP_(i,m) ws1[i]=0;
        REP_(i,n) ws1[wv[i]]++;
        rep_(i,1,m) ws1[i]+=ws1[i-1];
        rREP_(i,n) sa[--ws1[wv[i]]]=y[i];//sort(计数排序)
        t=x,x=y,y=t;
        p=1; x[sa[0]]=0;
        rep_(i,1,n) x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
    }
}

int rnk[maxn],height[maxn];
void calheight(int *r,int *sa,int n) {
    int i,j,k=0;
    FOR_(i,1,n) rnk[sa[i]]=i;
    REP_(i,n) {
        if (k) k--;
        j=sa[rnk[i]-1];
        while (r[i+k]==r[j+k]) k++;
        height[rnk[i]]=k;
    }
}

// const int mod = 1e9+7;
const int mod=998244353;
// int mod=1;
struct mint {
    long long x;
    mint():x(0) {}
    mint(long long x):x((x%mod+mod)%mod) {}
    // mint(long long x):x(x){}
    mint &fix() { x = (x%mod+mod)%mod; return *this;}
    mint operator-() const { return mint(0) - *this;}
    mint operator~() const { return mint(1) / *this;}
    mint &operator+=(const mint &a) { if ((x+=a.x)>=mod) x-=mod; return *this;}
    mint &operator-=(const mint &a) { if ((x+=mod-a.x)>=mod) x-=mod; return *this;}
    mint &operator*=(const mint &a) { (x*=a.x)%=mod; return *this;}
    mint &operator/=(const mint &a) { (x*=a.pow(mod-2).x)%=mod; return *this;}
    mint operator+(const mint &a)const { return mint(*this) += a;}
    mint operator-(const mint &a)const { return mint(*this) -= a;}
    mint operator*(const mint &a)const { return mint(*this) *= a;}
    mint operator/(const mint &a)const { return mint(*this) /= a;}
    mint pow(long long t) const {
        mint ret=1,cur=x;
        for (; t; t>>=1ll,cur=cur*cur)
            if (t&1) ret=ret*cur;
        return ret;
    }
    bool operator<(const mint &a)const { return x < a.x;}
    bool operator==(const mint &a)const { return x == a.x;}
};

struct BIT{
    mint A[maxn],B[maxn];
    inline int lowbit(int x){return x&-x;}
    void Add(int x,mint val,mint VAL){
        for (;x<maxn;x+=lowbit(x)) A[x]+=val,B[x]+=VAL;
    }
    void add(int l,int r,int val){
        if (l>r) return;
        Add(l,val,-mint(l-1)*val);
        Add(r+1,-val,mint(r)*val);
    }
    mint query(int x){
        mint ret=0;
        for (int i=x;x;x-=lowbit(x)) ret+=A[x]*i+B[x];
        return ret;
    }
    mint query(int l,int r){
        return query(r)-query(l-1);
    }
}bit;
// 还需要考虑value[l,r]==0的情况有多少种
// f[r]=0的时候,用前一个非0 pos计算即可
// 需要考虑A长度大于B长度; A长度等于B长度
int A[maxn],Count[maxn];
int sa[maxn];
int main() {
    int n;
    cin>>n;
    REP_(i,n) cin>>A[i];
    // reverse(A,A+n);
    REP_(i,n) A[i]++;
    da(A,sa,n,11);
    calheight(A,sa,n);
    REP_(i,n) A[i]--;
    // REP_(i,n) printf("%d ",A[i]); puts("<- reversed A");
    mint zeroResult=0;
    {
        mint zero=0;
        int cur=0;
        REP_(i,n) {
            cur++;
            if (A[i]!=0) Count[i]=cur,cur=0;
            else zero+=cur;
        }
        mint nonzero=mint(n)*(n+1)/2-zero;
        zeroResult=zero*nonzero;
        // cout<<zero.x<<"  "<<zeroResult.x<<" zero "<<endl;
    }
    mint notSameLength=0;
    {
        vector<int> length(n+2);
        REP_(i,n) length[n-i]=length[n-i+1]+Count[i];
        mint all=0;
        FOR_(i,1,n) {
            notSameLength+=all*length[i];
            all+=length[i];
        }
        // REP_(i,n) printf("%d ",Count[i]); puts("<- Count");
        // FOR_(i,1,n) printf("%d ",length[i]); puts("<- length (not-one)");
        // cout<<notSameLength.x<<"  <- not same length"<<endl;
    }

    mint sameLength=0;
    {
        vector<pair<int,int>> S; // stack
        S.push_back({0,0});
        int length=0;
        FOR_(_,1,n) {
            int x=sa[_];
            // printf(" === Start To solve ");
            // rep_(i,x,n) printf("%d ",A[i]);
            // printf(" height=%d; Count=%d\n",height[_],Count[x]);
            int left=length;
            while (S.back().second>height[_]) {
                int last=S.size()-1;
                int l=max(height[_],S[last-1].second)+1,r=S[last].second;
                // printf("should update %d -> %d; length=%d to %d\n",l,r,S[last].first,length);
                bit.add(l,r,length-S[last].first);
                left=S.back().first;
                S.pop_back();
            }
            // ans += Count[x] * query(1,n-x);
            mint cur=bit.query(1,n-x)*Count[x];
            sameLength+=cur;
            // printf("current update=%lld\n",cur.x);
            S.push_back({left,height[_]});
            S.push_back({length,n-x});
            length+=Count[x];
        }
        // cout<<sameLength.x<<"  <- same length"<<endl;
    }
    mint res=zeroResult+notSameLength+sameLength;
    cout<<res.x;
    return 0;
}
/*
10
0 5 2 3 0 2 1 9 0 0
*/