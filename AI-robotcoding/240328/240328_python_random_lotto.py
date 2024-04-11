#%%
# 로또번호 생성해보기
import random

# 1~10 사이의 정수 난수를 출력 / 6개
num1 = random.randint(1,45)
num2 = random.randint(1,45)
num3 = random.randint(1,45)
num4 = random.randint(1,45)
num5 = random.randint(1,45)
num6 = random.randint(1,45)

print(f'랜덤생성된 로또는 : {num1} {num2} {num3} {num4} {num5} {num6} 입니다')

# %%
# for 활용한 로또번호 생성해보기
import random

int_rand_array = [] #배열 선언(랜덤번호)
int_my_array = [] #배열 선언(내 번호 입력)

# 내 로또번호 만들기 (1 : 수동, 2 : 자동)
select = int(input("내 로또번호 생성하기(1:수동, 2:자동)"))

if select == 1:
    # 1~10 사이의 정수 난수를 출력 / 6개
    for i in range(0,6):
        int_my = int(input(f'1~45사이의 숫자 6개를 입력해보세요 {i+1}번 : '))
        int_my_array.append(int_my)
elif select == 2 :
        # 1~10 사이의 정수 난수를 출력 / 6개
    for i in range(0,6):
        int_my = random.randint(1,45)
        int_my_array.append(int_my)
else :
    print("다시 입력하세요")


int_my_array.sort()#오름차순으로 정렬
print(f'내 로또번호는 : {int_my_array}')

# 1~10 사이의 정수 난수를 출력 / 6개
for i in range(0,6):
    int_rand = random.randint(1,45)
    int_rand_array.append(int_rand)

int_rand_array.sort()#오름차순으로 정렬
print(f'당첨된 로또 번호는 : {int_rand_array}')

count = 0
for a in int_rand_array:
    for b in int_my_array:
        if a == b:
            count += 1

#num_count = int_rand_array.count(int_my_array) 
#count() : 괄호 안에 것과 일치한것의 갯수를 셈
print(f'내가 맞춘 로또번호는 : {count} 개')


# %%
