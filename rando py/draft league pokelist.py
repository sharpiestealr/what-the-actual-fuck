with open('sheet.txt') as f:
    sheet = f.readlines()

with open('swsh.txt') as g:
    swsh = g.readlines()

with open('armor.txt') as h:
    armor = h.readlines()

with open('tundra.txt') as i:
    tundra = i.readlines()

with open('others.txt') as j:
    others = j.readlines()

count = 0

print(len(sheet), len(swsh), len(armor), len(tundra), len(others))

while count != len(sheet):
    if (swsh[count] not in sheet):
        sheet.append(swsh[count])
    count+=1

count = 0

while count != len(sheet):
    if (tundra[count] not in sheet):
        sheet.append(tundra[count])
    count+=1

count = 0

while count != len(sheet):
    if (other[count] in sheet):
        sheet.append(other[count])
    count+=1

print("this is the new length of the list:", len(sheet))
print(sheet)