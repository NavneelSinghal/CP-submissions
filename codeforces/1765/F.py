n, k = map(int, input().split())

x,w,c = [],[],[]

for _ in range(n):
    xi, wi, ci = map(int, input().split())

    x.append(xi)
    w.append(wi)
    c.append(ci)

ind = list(range(n))
ind.sort(key = lambda u: x[u])

best = []

for ii in range(n):
    i = ind[ii]

    poss = [-w[i]]

    for jj in range(ii):
        j = ind[jj]

        value = best[jj]

        dx = (x[i] - x[j]) / 100
        ay = (c[i] + c[j]) / 2

        poss.append(value + dx * ay * k - w[i])

    best.append(max(poss))


best.append(0)
print(max(best))
