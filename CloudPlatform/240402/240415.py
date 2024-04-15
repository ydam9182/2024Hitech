#%%

a = [] # 빈 list 선언
print(f'a = {a}, type(a) = {type(a)}')

a = [1,2,3] # 선언과 초기화
print(f'a = {a}, type(a) = {type(a)}')

a[0] = 10
a[1] = 20
a[2] = 30 # a의 데이터 변경
print(f'a = {a}, type(a) = {type(a)}')
a.append(10)
a.append(20)
a.append(30)
print(f'a = {a}, type(a) = {type(a)}')

a1 = a[0:1]
print(f'a1 = {a1}, type(a1) = {type(a1)}')
a2 = a[0:2]
print(f'a2 = {a2}, type(a2) = {type(a2)}')
a3 = a[0:3]# list 데이터 가져오기 -> slice 
print(f'a3 = {a3}, type(a3) = {type(a3)}')
# %%
a, b, c, d = 0, 0, 0, 0
sum = 0
a = int(input('1번째 숫자를 입력하시오 : '))
b = int(input('2번째 숫자를 입력하시오 : '))
c = int(input('3번째 숫자를 입력하시오 : '))
d = int(input('4번째 숫자를 입력하시오 : '))

sum = a + b + c + d
print('총합은 ', sum, ' 입니다.')
print('총합은 %d 입니다.' % sum)
print(f'총합은 {sum} 입니다')

# %%
# 위의 코드 a, b, c, d를 list append를 이용한 for문으로 변경하시오

list_A = []
sum = 0

for i in range(1, 4+1, 1):
    add = int(input(f'{i}번째 숫자를 입력하시오 :'))
    sum += add
    list_A.append(add)
    # list_A.append(int(input(f'{i}번째 숫자를 입력하시오 :')))
    # sum += list_A[i]

print(f'리스트 결과값 : {list_A}')
print(f'리스트 총합 : {sum}')

# %%
n = 10

val = []
for _ in range(n):
    val.append(int(input('값을 입력하시오(정수): ')))

print(f'val = {val}')
# %%
# 구구단 2단을 two_dan = [] 리스트에 넣어서
# 그 결과를 출력하시오(use for)

two_dan = [2, 4, 6, 8, 10, 12, 14, 16, 18]
sum = 0

for i in range(1, 9+1, 1):
    print(f'2 x {i} = {two_dan[i-1]}')
    sum += two_dan[i-1]

print(f'- 1) 총합 : {sum} \n')

# %%
dan = 2
two_dan = [x for x in range(dan, dan*10, dan)]
print(two_dan)

sum = 0
for i in range(1, 9+1, 1):
    sum += two_dan[i-1]

print(' - 2) 총합 : ', sum)

# %%
two_dan = []
sum = 0

for i in range(1, 9+1, 1):
    two_dan.append(2*i)
    print(f'2 x {i} = {two_dan[i-1]}')
    sum += two_dan[i-1]

print(f'- 3) 총합 : {sum}')
# %%
# 구구단을 gugudan = [ _2dan, _3dan, ... , _9dan]으로 만들어서 출력
# _2dan = [2, 4, ..., 18]
# _3dan = [3, 6, ..., 27]
# _9dan = [9, 18, ..., 81]

gugudan = []

for i in range(2, 9+1) :
    dan = [i*x for x in range(1, 9+1)]
    #gugudan += dan
    gugudan.append(dan)

print(gugudan)
# %%
# gugudan을 가로로 출력하시오
# dan_start = 5, finish = 8
# step_start = 3, finish = 7

gugudan = []
for dan in range(5, 8+1):
    res = [step*dan for step in range(3, 7+1)]
    gugudan.append(res)

print(gugudan)
# %%
# gugudan을 가로로 출력하시오(2)
# dan_start = 5, finish = 8
# step_start = 3, finish = 7

gugudan = []
res = []
for dan in range(5, 8+1):
    line = ''
    for step in range(3, 7+1):
        res.append(dan*step)
        gugudan.append(res)
        line += f'{dan} * {step} = {res}'
        line += '\t'
    print(line)

print(gugudan)
quest1 = int(input('행을 입력 : '))
quest2 = int(input('열을 입력 : '))

print(gugudan[quest1-1][quest2-1])
# %%
