import turtle
import random

class turtle_shape :
    t = None
    colors = ['red', 'orange', 'yellow', 'green', 'blue', 'navy', 'purple'] 
    
    def __init__(self): # 기본적인 정보 기입
        self.t = turtle.Turtle('turtle')
        self.t.pencolor(random.choice(self.colors))
        self.t.color(random.choice(self.colors))
        self.step = 100

    def drawRec(self, x, y): # 그림 그리는 부분 - 서브로 넘겨줌
        pass

class t_Rectangle(turtle_shape):
    def __init__(self):
        turtle_shape.__init__(self)
    
    def drawRec(self, x, y): # 그림 그리는 부분 
        self.t.penup()
        self.t.goto(x, y)
        self.t.pendown()
        for _ in range(4):
            self.t.forward(self.step)
            self.t.right(90)
        self.t.write('END!')
        self.t.penup()

# 메인코드부
turtle.title('Rectangles')

ts = [t_Rectangle() for _ in range(10)] #거북이 9마리 생성
ts_pos = [(-200,200), (0,200), (200,200),
          (-200,0), (0,0), (200,0),
          (-200,-200), (0,-200), (200,-200)]

for t, ts_pos in zip(ts, ts_pos):
    t.drawRec(*ts_pos)

turtle.mainloop()