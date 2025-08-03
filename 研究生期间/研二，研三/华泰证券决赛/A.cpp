#include <bits/stdc++.h>
typedef long long ll;
#define FOR(I,S,N) for (I=S;I<=N;I++)
const int maxn=1e5+7;
int A[maxn];
char s[maxn];
int main() {
    int n,prev=0;
    scanf("%d",&n);
    ll ans=0; int i;
    FOR(i,1,n) {
        scanf("%s",s);
        if (s[0]!='?') {
            int val;
            sscanf(s,"%d",&val);
            if (prev) ans+=abs(val-prev);
            prev=val;
        }
    }
    printf("%lld\n",ans);
}
/*
6
1 1 ? 5 1 4

*/ 