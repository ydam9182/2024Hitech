import multiprocessing.process
import time
import threading

class RacingCar:
    carName = ''
    def __init__(self,name):
        self.carName = name
    
    def runCar(self):
        for _ in range(3):
            carStr = self.carName +'~~~달립니다.\n'
            print(carStr,end='')
            time.sleep(0.1)

print('==MultiProcess==='*5)
if __name__ == "__main__":
    car1 = RacingCar('@자동차')
    car2 = RacingCar('#자동차')
    car3 = RacingCar('$자동차')
    cars = [car1, car2, car3]
    car_multiProcess = []
    for car in cars:
        mp = multiprocessing.Process(target= car.runCar)
        car_multiProcess.append(mp)

    start_time = time.time()
    #스레드 시작
    for t in car_multiProcess:
        t.start()
    # 스레드가 끝날 때 까지 기다림
    for t in car_multiProcess:
        t.join()

    # 스레드 실행 시간 측정을 위한 종료 시간 기록
    end_time = time.time()

    # 경과 시간 계산
    elapsed_time = end_time - start_time
    print(f"MultiProcess elapsed time: {elapsed_time:.4f} seconds")
    # %%
