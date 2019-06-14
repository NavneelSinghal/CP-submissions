l = [int(a) for a in input().split()]
x = l[0]
y = l[1]
z = l[2]
t1 = l[3]
t2 = l[4]
t3 = l[5]
r1 = abs(x-y)*t1
r2 = abs(x-z)*t2+abs(x-y)*t2+3*t3
if(r1<r2):
    print("NO")
else:
    print("YES")