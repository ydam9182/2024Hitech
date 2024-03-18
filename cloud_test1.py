print('hello world!!')

#%%
print('hello world!!')
# %%
a= 'a'
print(a, type(a))
a='aasdfasdf'
print(a, type(a))
a=1
print(a, type(a))
a=123.456
print(a, type(a))
# %%
a=1
b=2
c=a+b
print(f'{a}+{b}={c}')
# %%
# list > array/data/read+write
# tuple > array/data/read only
# dic > 사전/search/data/read+write

a = (1,2,3,4,5)
print(a, type(a))
a=[1,2,3,4,5]
print(a, type(a))
a={'a':1, 'b':2, 'c':3, 'd':4, 'e':5}
print(a, type(a))

#%%
#operator
# +-*% / 4칙연산
# ** / //

a = 5
print(a**3, type(a))
print(a//2, type(a))
print(a/2, type(a))

#%%
import os
print('this is calculation program')
a = input('in a :')
b = input('in b :')
op = input('in op(+,-,*,/,//,**) :')
c = a+b
print(f"{a}+{b}={c}", type(a),type(b),type(c))
# input이 문자열로 반환하는 이유 : 
#  숫자와 문자를 모두 포함가능한 자료형이기 때문
# %%
# 위 문제를 해결하는 방법 : 
# 형변환 type-casting > str to int

import os
print('this is calculation program')

a = input('in a :')
a = int(a)
print(type(a))

b = input('in b :')
b = int(b)
print(type(b))

op = input('in op(+,-,*,/,//,**) :')
# 제어문(조건문, 반복문) : if from python <-> if /switch from c/c++
if(op == '+'):
    c = a+b
elif (op == '-'):
    c = a-b
elif (op == '*'):
    c = a*b
elif (op == '/'):
    c = a/b
elif (op == '//'):
    c = a//b
elif (op == '**'):
    c = a**b
else :
    print('만족하는 op가 없습니다')

print(f"{a}{op}{b}={c}")


#%%


