f = open("no.txt")

array = []
array1 = []

for line in f:
    for num in line.rstrip().split(","):
        array.append(num)

print(array)

a = 0
for x in array:
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


f.close()

print(array1)

file = open("new.txt","w")
for i in range(len(array1)):
    file.write("%i " % (array1[i]))
file.close()

 