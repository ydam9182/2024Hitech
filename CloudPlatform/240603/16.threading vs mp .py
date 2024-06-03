import time
import threading
import multiprocessing

# 간단한 CPU 바운드 작업 예시
def cpu_bound_task(n):
    while n > 0:
        n -= 1

# I/O 바운드 작업 예시
def io_bound_task():
    time.sleep(1)

# Threading 벤치마크
def threading_benchmark(task, *args):
    threads = []
    start_time = time.time()
    for _ in range(4):
        t = threading.Thread(target=task, args=args)
        threads.append(t)
        t.start()
    for t in threads:
        t.join()
    end_time = time.time()
    print(f"Threading elapsed time: {end_time - start_time:.4f} seconds")

# Multiprocessing 벤치마크
def multiprocessing_benchmark(task, *args):
    processes = []
    start_time = time.time()
    for _ in range(4):
        p = multiprocessing.Process(target=task, args=args)
        processes.append(p)
        p.start()
    for p in processes:
        p.join()
    end_time = time.time()
    print(f"Multiprocessing elapsed time: {end_time - start_time:.4f} seconds")

if __name__ == "__main__":
    print("CPU-bound task benchmark")
    threading_benchmark(cpu_bound_task, 10**7)
    multiprocessing_benchmark(cpu_bound_task, 10**7)
    
    print("\nI/O-bound task benchmark")
    threading_benchmark(io_bound_task)
    multiprocessing_benchmark(io_bound_task)
