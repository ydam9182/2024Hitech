#16.threading_calc.py
import time
import threading
class Calc:
    data=[x for x in range(10000)]
    def __init__(self, start, finish):
        self.start = start
        self.finish = finish
        self.sum = 0
    def runCalcSum(self):
        self.sum=0
        print(f'sum range = {self.start}~{self.finish} start !!!\n')
        for i in range(self.start, self.finish):
            self.sum += self.data[i]
        print(f'sum range = {self.start}~{self.finish} = {self.sum} finish !!!\n')
        time.sleep(0.1)

calc_1 = Calc(0,1000)
calc_2 = Calc(1000,2000)
calc_3 = Calc(2000,3000)
calc_4 = Calc(3000,4000)
calc_5 = Calc(4000,5000)

start_time = time.time()
calc_1.runCalcSum()
calc_2.runCalcSum()
calc_3.runCalcSum()
calc_4.runCalcSum()
calc_5.runCalcSum()
end_time = time.time()
elapsed_time = end_time - start_time
print(f"SQE::Total elapsed time: {elapsed_time:.4f} seconds")



print('===='*10)
# 스레드를 생성하고 실행
calcs = [calc_1, calc_2, calc_3, calc_4, calc_5]
calc_threads = []
for calc in calcs:
    t = threading.Thread(target=calc.runCalcSum)
    calc_threads.append(t)

# 스레드를 시작
start_time = time.time()
for t in calc_threads:
    t.start()
# 모든 스레드가 끝날 때까지 기다림
for t in calc_threads:
    t.join()
end_time = time.time()
elapsed_time = end_time - start_time
print(f"THREAD::Total elapsed time: {elapsed_time:.4f} seconds")