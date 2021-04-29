n = int(input())
a = list(map(int, input().split()))
b = list(map(int, input().split()))
ans = 0
for i in range(n):
    ans += a[i] * b[i]
base = ans
for i in range(n):
    for j in (i - 1, i):
        cur = base
        k = i + 1
        while j >= 0 and k < n:
            cur -= (a[j] - a[k]) * (b[j] - b[k])
            ans = max(ans, cur)
            j -= 1
            k += 1
print(ans)
