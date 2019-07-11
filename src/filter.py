f = open("map_downsample.txt")

array = []
array1 = []

for line in f:
    for num in line.rstrip().split(","):
        array.append(num)

#print(array)

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
my = ",".join(map(str,array1))
print(my)
#print(array1)

with open("new.txt","w") as writer:
    for i in my:
        writer.write(i)

#for i in range(len(array1)):
    #file.write("%f " % (my[i]))
#file.close()

 