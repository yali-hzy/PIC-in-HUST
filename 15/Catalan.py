f = [1]
for n in range(1, 6):
    sum = 0
    for i in range(n):
        sum += f[i] * f[n - i - 1]
    f.append(sum)
print(f[5])