def dispute(j, g, r, w):
    dis = (j*(abs(500-g))**(1/3))/((6-r)**w)
    return dis

def gift(e, j, p, g, r):
    gif = e*(j+p)*(abs(500-g))**(1/3)/(6-r)
    return gif

print("welcome to the super special calculator! \n for any complaints about the formula, @jack over it, i just coded this thing \n")
calc = input("would you like to run a dispute calc or a gift card calc? \n type dispute or gift ")

if (calc == "dispute"):
    j = int(input("what's their joke rating? "))
    g = float(input("how many google results does this game have? please give the result in millions! "))
    r = float(input("how many stars does the game have? please type 4 if you cannot find a rating. "))
    w = float(input("how nice was this player? 0 = nice, 1 = average, 2 = rude. decimals are accepted. "))

    dis = dispute(j, g, r, w)

    print("\nthis player's dispute score is: ", dis)

elif (calc == "gift"):
    gif = 0
    for i in range (1, 6):
        print("for round ", i)
        e = float(input("did they enjoy the tournament? 1 = yes, 0.5 = no "))
        j = int(input("what's their joke rating? "))
        p = float(input("what's the player's rating? "))
        g = float(input("how many google results does this game have? please give the result in millions! "))
        r = float(input("how many stars does the game have? please type 4 if you cannot find a rating. "))
        quagnag = float(input("did they play a quagnag mirror? 1 = yes, 0 = no"))

        gif = gif + gift(e, j, p, g, r) + quagnag*gift(e, j, p, g, r)

    print("\nthis player's gift card score is: ", gif)
