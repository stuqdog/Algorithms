from random import randint
from collections import Counter

def integer(arr):
    new = [0 for x in range(10001)]
    a = 0
    for x in arr:
        new[x] += 1
    for i, x in enumerate(new):
        for _ in range(x):
            arr[a] = i
            a += 1
    return arr

def insertion(arr):
    for x in range(1, len(arr)):
        temp = arr[x]
        i = x
        while i > 0 and arr[i-1] > temp:
            arr[i] = arr[i-1]
            i -= 1
        arr[i] = temp
    return arr


def merge(arr):
    if len(arr) == 1:
        return arr
    left = merge(arr[:len(arr) // 2])
    right = merge(arr[len(arr) // 2:])
    l = r = 0
    new = []
    while len(new) < len(arr):
        if l >= len(left):
            new += right[r:]
        elif r >= len(right):
            new += left[l:]
        elif left[l] < right[r]:
            new.append(left[l])
            l += 1
        else:
            new.append(right[r])
            r += 1
    return new

test = []
for i in range(10000):
    test.append(randint(0, 10000))
print(merge(test))
#print(insertion(test))
#print(integer(test))
#print(sorted(test))
