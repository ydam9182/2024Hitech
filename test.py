# #print(len("hello"))

# print(len("12345"))

# print("hello"[0])

# #%%
# a= 123
# print(type(a))


# # %%
# a = int(input("숫자1 입력 :"))
# print(type(a))
# b = int(input("숫자2 입력 :"))
# print(type(b))
# c = a+b
# print(type(c))
# print("두 숫자의 합은 : " + str(c))

# %%
# a = input("두자릿수 숫자입력 :")
# print("두 자리의 합은 : " + str(int(a[0])+int(a[1])))
a = input("두 자릿수 숫자입력 : ")

if len(a) != 2:
    print("두 자릿수를 입력하세요")
else:
    num1 = int(a[0])
    num2 = int(a[1])
    sum = num1 + num2
    print("두 자리의 합 :" + str(sum))

