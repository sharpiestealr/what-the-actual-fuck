import math

def snell_descartes(n1, n2, t1):
    st2 = n1*math.sin(t1)/n2
    print(st2)
    t2 = math.asin(st2)
    print(t2)
    graus = float((t2*180)/math.pi)
    return graus

n1, n2, t1 = 1, 2, 30

t2 = snell_descartes(n1, n2, t1)

print(t2)