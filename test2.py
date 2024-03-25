# %%
# 구구단 가로형태로 출력하시오
# 2*1=2  3*1=3  4*1=4 ...
# 2*2=4  3*2=6  4*3=12 ...

Dan_start = 2
Dan_finish = 9
Step_start = 1
Step_finish = 9

for step in range (Step_start, Step_finish+1, 1):
    msg = ''
    for dan in range(Dan_start, Dan_finish+1, 1):
        result = dan * step
        msg += f'{dan} * {step} = {result} \t'
    print(msg)

# %%
# 구구단 가로형태로 출력하시오
# 2*1=2  3*1=3  4*1=4 ...
# 2*2=4  3*2=6  4*3=12 ...

#input
Dan_start = 2
Dan_finish = 9
Step_start = 1
Step_finish = 9
lines = ''

#fuction
for step in range (Step_start, Step_finish+1, 1):
    msg = ''
    for dan in range(Dan_start, Dan_finish+1, 1):
        result = dan * step
        msg += f'{dan} * {step} = {result} \t'
    lines += msg + '\n'

#output
print(lines)
    
# %%
# Q3.GUGUDAN 형태로 출력하시오
# GuGuDan Start = 2 dan, Finish = 6 dan
# GuGuDan Step Start = 5, Finish = 8 step
# 2 * 5 = 10  2 * 6 = 12   ... 2 * 8 = 16
# 6 * 5 = 30  6 * 6 = 36   ... 6 * 8 = 48


#input
Dan_start = 2
Dan_finish = 6
Step_start = 5
Step_finish = 8
lines = ''

#fuction
for dan in range(Dan_start, Dan_finish+1, 1):
    msg = ''
    for step in range (Step_start, Step_finish+1, 1):
        result = dan * step
        msg += f'{dan} * {step} = {result} \t'
    lines += msg + '\n'

#output
print(lines)
# %%
# %%
# Q3.GUGUDAN 형태로 출력하시오
# GuGuDan Start = 2 dan, Finish = 6 dan
# GuGuDan Step Start = 5, Finish = 8 step
# 2 * 5 = 10  2 * 6 = 12   ... 2 * 8 = 16
# 6 * 5 = 30  6 * 6 = 36   ... 6 * 8 = 48

#input
Dan_start = 2
Dan_finish = 9
Step_start = 1
Step_finish = 9
lines = ''

#fuction
for dan in range(Dan_start, Dan_finish+1, 1):
    msg = ''
    if(dan >= 2 and dan <= 6):
        for step in range (Step_start, Step_finish+1, 1):
            if(step >= 5 and step <= 8):
                result = dan * step
                msg += f'{dan} * {step} = {result} \t'
        lines += msg + '\n'

#output
print(lines)
# %%

for i in range(1, 5+1, 1):
    print('*'*i)
# %%

digits_max = 5
for i in range(digits_max,0,-1):
    msg_empty = f' '*(i-1)
    msg_star = f'*'*(digits_max-i+1)
    print(i, msg_empty+msg_star)

# %%
