#%% 절차적 실행
import time

class RacingCar : 
    carName = ''
    def __init__(self, name):
        self.carName = name

    def runCar(self):
        for _ in range(0,3):
            carStr = self.carName + '~~달립니다. \n'
            print(carStr, end = '')
            time.sleep(0.1)

car1 = RacingCar('@자동차1')
car2 = RacingCar('#자동차2')
car3 = RacingCar('$자동차3')

car1.runCar()
car2.runCar()
car3.runCar()
# %% 멀티 스레드
import threading
import time

class RacingCar : 
    carName = ''
    def __init__(self, name):
        self.carName = name

    def runCar(self):
        for _ in range(0,3):
            carStr = self.carName + '~~달립니다. \n'
            print(carStr, end = '')
            time.sleep(0.1)

car1 = RacingCar('@자동차1')
car2 = RacingCar('#자동차2')
car3 = RacingCar('$자동차3')

th1 = threading.Thread(target = car1.runCar)
th2 = threading.Thread(target = car2.runCar)
th3 = threading.Thread(target = car3.runCar)

th1.start()
th2.start()
th3.start()
# %%
# %% 멀티 스레드
import threading
import time

class RacingCar : 
    carName = ''
    def __init__(self, name):
        self.carName = name

    def runCar(self):
        for _ in range(0,3):
            carStr = self.carName + '~~달립니다. \n'
            print(carStr, end = '')
            time.sleep(0.1)


car = [RacingCar('@자동차1'), RacingCar('#자동차2'), RacingCar('$자동차3')]
car_threads = [threading.Thread(target = car[i].runCar) for i in range(3)]

for t in car_threads :
    t.start()

for t in car_threads :
    t.join()

# %%
import time
import threading

class calc:
    data = [x for x in range(10000)]
    def __init__(self, start, finish):
        self.start = start
        self.finish = finish
        self.sum = 0

    def runCalcSum(self):
        self.sum = 0
        print(f'sum range = {self.start}~{self.finish} start!\n')
        for i in range(self.start, self.finish):
            self.sum += self.data[i]
        print(f'sum range = {self.start}~{self.finish} finish!\n')

calc_1 = calc(0, 1000)
calc_2 = calc(1000, 2000)
calc_3 = calc(2000, 3000)
calc_4 = calc(3000, 4000)
calc_5 = calc(4000, 5000)