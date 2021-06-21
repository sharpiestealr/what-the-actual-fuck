#foi mal pelicano
#não deu mesmo
#eu tentei mexer no código da aula e tudo
#mas eu realmente não consegui





#xy, xt, yt
#pra fres sim e não

# Importa bibliotecas
import math
import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import odeint

# SEU CÓDIGO

# Definição dos parâmetros
g = 10 # [m/s^2]
m = 0.200 # [kg]
l0 = 0.3 # [m]
r = 0.1 # [m]
a = math.pi*(r**2) # [m^2]
cd = 1.5 
p = 1 # [kg/m^3]
k = 10 # [N/m]

# Função de equações diferenciais (a ser utilizada pela odeint)
def EquacoesDiferenciais(lista, t):
    # Desmembra lista
    dxdt = lista[0]
    d2xdt2 = lista[1]
    dydt = lista[2]
    d2ydt2 = lista[3]      
    # Equações diferenciais
    dxdt=vx 
    d2xdt2=(((3*k*(math.sqrt((a)**2+()**2)-l0)*(yb-ya))/math.sqrt((rb-ra)**2+(yb-ya)**2))-ma*g)/ma
    dydt=vy
    d2ydt2=(((-3*k*(math.sqrt((rb-ra)**2+(yb-ya)**2)-l0)*(yb-ya))/math.sqrt((rb-ra)**2+(yb-ya)**2))-mb*g)/mb 
    # Regrupa lista de derivadas
    dlistadt = [dxdt, d2xdt2, dydt, d2ydt2]
    # Returna lista de derivadas
    return dlistadt 


# Condições iniciais
x0 = 0.55
dxdt0 = 0 
y0 = 0
dydt0 = 0
S0 = [x0, dxdt0, y0, dydt0]

# Lista de tempo
dt = 0.01
t = np.arange(0,20,dt)

# Utiliza a função odeint
S=odeint(EquacoesDiferenciais, S0, t)

# Plota o gráfico
plt.plot(t, S[:,0], label="$y_a$ - Posição do anel")
plt.plot(t, S[:,2], label="$y_b$ - Posição da barra")
plt.title('Saltador')
plt.xlabel('Tempo (s)')
plt.ylabel('Posição (m)')
plt.legend()
plt.grid(True)
plt.show()

