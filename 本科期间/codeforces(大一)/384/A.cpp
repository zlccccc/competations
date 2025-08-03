#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
    char s[100002];
    int n,i;
    int a,b;
    scanf("%d%d%d",&n,&a,&b);
    scanf("%s",s);
    if (s[a-1]==s[b-1]) printf("0");
    else printf("1");
    return 0;
}
