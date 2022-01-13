count = 0
check = []

with open('players.txt') as f:
    players = f.readlines()

check.append(players[0])

while (count != len(players)):
    if count > 0:
        if players[count] in check:
            count += 1
        else:
            if players[count][0] == "@":
                print("-grole {0}SERIES".format(players[count]))
            else:
                print("-grole @{0}SERIES".format(players[count]))
            
            check.append(players[count])
            count += 1
    else:
        print("-grole @{0}SERIES".format(players[count]))
        check.append(players[count])
        count += 1