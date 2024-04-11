#!/usr/bin/env python
# coding: utf-8

# In[1]:


print("hello world")


# In[15]:


#20240307
#파이썬 기본 데이터 타입

a=1
b=2
c=a+b

print(c)


# In[8]:


import math

int(3.5)


# In[18]:


int(3.4)
2e3
float("1.6")
float("inf")
float("-inf")
bool(0)
bool(1)
bool("False")
a = None
a is None


# In[19]:


print("동해물과 백두산이 마르고 닳도록 하느님이 보우하사 우리나라 만세")

print("동해물과 백두산이 마르고 닳도록 하느님이 보우하사 우리나라 만세")

print("동해물과 백두산이 마르고 닳도록 하느님이 보우하사 우리나라 만세")


# In[20]:


korea = "동해물과 백두산이 마르고 닳도록 하느님이 보우하사 우리나라 만세"

print(korea)
print(korea)
print(korea)


# In[26]:


#산술연산자
a=1
b=4

c=a+b
d=a-b
e=a*b
f=a/b

print(c)
print(d)
print(e)
print(f)


# a=1
# 
# if a != 1:
#     print("1이 아님")
#     else:
#         print("1이다")

# In[33]:


a=1

if a != 1: 
    print("1이 아님") 
else: 
    print("1이다")


# In[34]:


a=1

if a<=2:
    print("a는 2보다 작거나 같다")


# In[38]:


a = 1
a *= 10
print(a)

b = 1
b /= 10
print(b)

c = 1
c += 10
print(c)

d = 1
d -= 10
print(d)


# In[54]:


x = True
y = False

if x and y :
    print("Yes")
else : 
    print("No")
    
if x or y :
    print("Yes")
else : 
    print("No")
    
if not x:
    print("Yes")
else : 
    print("No")
    
if not y:
    print("Yes")
else : 
    print("No")
    
if x and not y:
    print("Yes")
else : 
    print("No")


# In[51]:


a = 8
b = 11

c= a&b
d = a | b
e = a ^ b
f = ~b

print(c)
print(d)
print(e)
print(f)


# In[46]:


a= [1,2,3,4]
b = 3 in a
print(b)


# In[ ]:




