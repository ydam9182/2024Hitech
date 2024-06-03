import turtle
import threading
import random
import time

# Function for each turtle to draw a square
def draw_square(t,x,y,size, color):
    t.penup()
    t.goto(x, y)
    t.pendown()
    t.color(color)
    t.begin_fill()
    for _ in range(4):
        t.forward(size)
        t.right(90)
    t.end_fill()



# Function to start drawing for a turtle
def start_timer(t, x,y,size,color):
    #timer = threading.Timer(0, lambda: draw_square(t, x,y,size,color))
    timer = threading.Thread(target=draw_square, args=(t, x,y,size,color))
    timer.start()
    
    

# Setup the screen
screen = turtle.Screen()
screen.bgcolor("white")

# Create 9 turtles
turtles = []
colors = ["red", "blue", "green", "yellow", "purple", "orange", "black", "pink", "brown"]
size = 200

for i in range(3):
    for j in range(3):
        t = turtle.Turtle()
        t.color(colors[i])
        t.penup()
        t.goto(i * 20 - 80, 0)  # Position turtles so they don't overlap
        t.pendown()
        turtles.append(t)

for i in range(3):
    for j in range(3):
        t = turtles[j*3+i]
        color = colors[j*3+i]
        x = -300 + j * (size + 10)
        y = 300 - i * (size + 10)
        start_timer(t,x,y,size,color)

# Keep the window open until it is closed by the user
screen.mainloop()
