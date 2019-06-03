f = open("no.txt")

array = []
array1 = []

for line in f:
    for num in line.rstrip().split(","):
        array.append(num)

print(array)

for x in enumerate(array):
    if x == '0':
        a = 0
        array1.append(a)
    elif x == '-1':
        a = -1
        array1.append(a)
    elif x == '100':
        a = 3
        array1.append(a)
    else:
        continue
print(array1)

f.close()