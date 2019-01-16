'''
from collections import OrderedDict 
Length = ""
def removeDupWithOrder(str): 
    return "".join(OrderedDict.fromkeys(str))

def lenOfString(str):
    Length = len("".join(OrderedDict.fromkeys(str)))
    return Length

print "Resulting String ",removeDupWithOrder("pwwkew")
print "Length of String ", lenOfString("pwwkew")
'''

def repeat(line):
    found = ''
    for char in line:
        if not char in found:
            found = found + char
        else:
            break
    return found

def findlongest(f):
    for line in f:
        longestfound = ''
        longestfoundlen = 0
        for k in range(len(line)):
            candidate = repeat(line[k:])
            if len(candidate) > longestfoundlen:
                longestfound = candidate
                longestfoundlen = len(candidate)
    print( len(longestfound))

f = ['pwwkew']
findlongest(f)
