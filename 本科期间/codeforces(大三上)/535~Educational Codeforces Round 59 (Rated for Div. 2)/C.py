n,k=map(int,input().split())
A=list(map(int,input().split()))
S=input()
ans=j=0
n=len(S)
for i in range(n):
    if (i==n-1 or S[i]!=S[i+1]):
        ans+=sum(sorted(A[j:i+1])[-k:])
        # print(j, i)
        j=i+1
print(ans)