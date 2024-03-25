#%%
# 조건문과 반복문

# 구구단 출력하시오

#for i in range(2, 9+1, 1):
#    for j in range(1, 9+1, 1):
#        print(str(i) + " * " + str(j) + " = " + str(i*j))

for i in range(2, 9+1, 1):
    for j in range(1, 9+1, 1):
        #print(str(i) + " * " + str(j) + " = " + str(i*j))
        msg = f'{i} * {j} = {i*j}'
        print(msg)
        


# %%
# 구구단 형태 넣기
# start = 2, finish = 6