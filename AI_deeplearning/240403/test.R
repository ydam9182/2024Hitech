total <- 5050
total
print(total)
cat('합계 : ', total)


a <- 10
b <- 20
c <- a+b
print(a)
print(b)
print(c)


abc <- 850
mid.sum <- 850


a <- sqrt(120)
a
sqrt <- 340
sqrt


age.1 <- 20
age.2 <- 25
print(age.1+age.2)
name.1 <- 'John'
print(name.1)
grade.1 <- '3'
print(age.1+grade.1)


5 > 3
2 > 7
TRUE + TRUE
a <- TRUE
b <- F
a
bs
a+b


addr <- NULL
print(addr)


a <- NA
b <- 'NA'
a
b


1/0
-2/0
sqrt(-5)


salt <- 50
water <- 100
result <- (salt / (salt+water)) * 100
result <- round(result, 2)
cat('소금 = ', salt, ', 물 = ', water, ': 농도 = ', result, "%")


score.1 <- 68; score.2 <- 95; score.3 <- 83; score.4 <- 76; score.5 <- 90
score.6 <- 80; score.7 <- 85; score.8 <- 91; score.9 <- 82; score.10 <- 70
total <- score.1 + score.2 + score.3 + score.4 + score.5 + score.6 + score.7 + score.8 + score.9 + score.10
avg <- total / 10
avg


score <- c(68, 95, 83, 76, 90, 80, 85, 91, 82, 70) #벡터의 활용(위치값이 중요!)
mean(score) # 평균값을 나타내는 함수 mean


x <- c(1, 2, 3)
y <- c('a', 'b', 'c')
z <- c(TRUE,TRUE, FALSE, TRUE)
x
y
z

w <- c(1,2,3,'a','b','c')
w


v1 <- 50:90
v1
v2 <- c(1,2,3, 50:90)
v2

v3 <- seq(1,101,3) #시작, 종료, 간격
v3
v4 <- seq(0.1, 1.0, 0.1)
v4

v5 <- rep(1, times = 5)
v5
v6 <- rep(1:5, times = 3)
v6
v7 <- rep(c(1,5,9), times = 3)
v7

v8 <- rep(c('a', 'b', 'c'), each = 3)
v8


absent <- c(8,2,0,4,1)
absent
names(absent)
names(absent) <- c('Mon', 'Tue', 'Wed', 'Tur', 'Fri')
absent
names(absent)


d <- c(1, 4, 3, 7, 8)
d
d[0]
d[1]
d[2]
d[3]
d[4]
d[5]
d[6]

d[c(1,3,5)] # 1, 3, 5번자리 출력
d[1:3] # 1~3자리 출력
d[seq(1,5,2)] # 홀수 번째 자리 출력, seq(1,5,2) == 1, 3, 5번째 자리 출력
d[-2] # -는 제외의 의미, 2번째 자리 제외하고 출력
d[-c(3:5)] # 3~5값은 제외하고 출력


sales <- c(640, 720, 680, 540)
names(sales) <- c('M1', 'M2', 'M3', 'M4')
sales
sales[1]
sales['M2']
sales[c('M1', 'M4')]


v1 <- c(1, 5, 7, 8, 9)
v1
v1[8] <- 3
v1
v1[c(1, 5)] <- c(10, 20)
v1
v1 <- c(100,200,300)
v1


customer <- c('Kim', 'Lee','Park', 'Choi', 'Seo')
deposit <- c(5000000,4500000,4000000,5500000,6000000)
rate <- c(3.5, 3, 4, 5, 4.5)
period <- c(2, 2, 5, 7, 4)

names(deposit) <- customer
names(rate) <- customer
names(period) <- customer

who <- customer

result <- deposit[who] * (1 + rate[who] / 100) ^ period[who]
result


y <- sqrt(100)
y


d <- c(1, 7, 4, 2, 3)
sort(d) # 오름차순으로 정리
sort(d, decreasing = TRUE) #내림차순으로 정리


sort(x=d, decreasing = FALSE)
sort(d, FALSE)


str <- paste('good', 'morning', 'hello', sep = '/') # sep = 중간에 끼워 넣을 문자
str


a <- '나의 나이는'
b <- 20
c <- '입니다'
paste(a, b, c, sep = ' ') # 매개변수 디폴트값 : sep = ' '


a <- 1:12
b <- '월'
c <- paste(a, b, sep= '')
c

sales <- c(750, 740, 760, 680, 700, 710, 850, 890, 700, 720, 690, 730)
names(sales) <- paste(1:12, '월', sep='')
sales

sales['7월']
sales['1월']+sales['2월']

max.month <- sort(sales, decreasing = T)
max.month
max.month[1]

sum(sales[1:6]) # 상반기 매출액
sales[1:6]

sum(sales[7:12]) # 하반기 매출액
sales[7:12]


