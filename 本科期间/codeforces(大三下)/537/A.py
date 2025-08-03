S = input()
T = input()
A = ['a', 'e', 'i', 'o', 'u']
if len(S) != len(T):
    print('No')
    exit()
for i in range(len(S)):
    if ((S[i] in A and T[i] not in A) or
            (S[i] not in A and T[i] in A)):
        print('No')
        exit()
print('Yes')