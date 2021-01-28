#!/usr/bin/python3
# nlantau, 2020-04-17
# Start value
x1 = float(input("Enter start x value: ")) # 1.5
y1 = float(input("Enter start y value: ")) # 2.5
z1 = float(input("Enter start z value: ")) # 3

# First equation
a1 = float(input("Enter x: "))
b1 = float(input("Enter y: "))
c1 = float(input("Enter z: "))
d1 = float(input("Enter HL: "))
# Second Equation
a2 = float(input("Enter x: "))
b2 = float(input("Enter y: "))
c2 = float(input("Enter z: "))
d2 = float(input("Enter HL: "))
# Third Equation
a3 = float(input("Enter x: "))
b3 = float(input("Enter y: "))
c3 = float(input("Enter z: "))
d3 = float(input("Enter HL: "))

# Calculate equation
def x_equation(a,b,c,d,x,y,z):
    if a != 0 and b != 0 and c != 0:
        if a < 0:
            return -(((b*y)/a) + ((c*z)/a) - (d/a))
        if a > 0:
           return -((b*y)/a) - ((c*z)/a) + (d/a)
    if a != 0 and b != 0 and c == 0:
        if a < 0:
            return ((b*y)/a) + (d/a)
        if a > 0:
           return -((b*y)/a) + (d/a)
    if a != 0 and b == 0 and c != 0:
        if a < 0:
           return ((c*z)/a) + (d/a)
        if a > 0:
           return -((c*z)/a) + (d/a)  
    
# Let user enter amount
iterations = int(input("Enter amount of iterations: "))

# print as many maddafakking iterations as you'd like 
for i in range(iterations):
    x = x_equation(a1,b1,c1,d1,x1,y1,z1)
    y = x_equation(b2,a2,c2,d2,y1,x1,z1)
    z = x_equation(c3,a3,b3,d3,z1,x1,y1)
    x1 = x
    y1 = y
    z1 = z
    print(i+1,'\t',format(x1, '.4f'),'\t\t', format(y1,'.4f'),'\t\t', format(z1,'.4f')) 