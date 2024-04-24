
# 벡터에서 원하는 자리 출력

d <- c(1, 4, 3, 7, 8)
d[c(1, 3, 5)]   # 1,3,5번째 출력
d[1:3]          # 1,2,3번째 ㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋ
d[seq(1, 5, 2)] # 홀수 번째 자료 출력 -> 1부터 5까지의 값을 2씩 건너뛴다
d[-2]           # -는 제외한다
d[-c(3:5)]      # 3,4,5번째 자리는 뺀다


-------------------------------------------------------------------------

  
# 열대로 인덱싱해서 원하는 정보 출력하기    

sales <- c(640, 720, 680, 540)
names(sales) <- c('M1', 'M2', 'M3', 'M4')
sales
sales[1]
sales['M2']
sales[c('M1', 'M4')]


-------------------------------------------------------------------------

  
# 복리를 계산하는 프로그램 
  
a <- c('Kim', 'Lee', 'Park', 'Choi', 'Seo')           # 기준 행 입력
one <- c(5000000, 450000, 4000000, 5500000, 6000000)  # 필요 데이터 입력1
ee <- c(3.5, 3, 4, 5, 4.5)                            # 필요 데이터 입력2
gi <- c(2, 2, 5, 7, 4)                                # 필요 데이터 입력1

names(one) <- a       # 기준행의 하위 행으로 넣어주기1
names(ee) <- a        # 기준행의 하위 행으로 넣어주기2
names(gi) <- a        # 기준행의 하위 행으로 넣어주기3
  
bok <- one[a] * (1 + ee[a] / 100 ) ^ gi[a]
# 원하는 연산 넣어주기 -> 기준행을 인덱스로 넣어주면 자동으로 열 이동함
bok     # 출력되는 정보는 기준행과 연산행 


-------------------------------------------------------------------------
  
  
# 정렬하는 함수
d <- c(1, 7, 4, 2, 3)
sort(d)                   # 오름차순
sort(d, decreasing=TRUE)  # 내림차순

sort(d)                         # 매개변수 표현 없음
sort(x=d)                       # 매개변수 앞에만 표현
sort(x=d, decreasing = FALSE)   # 매개변수 전체 표현 
  
  
-------------------------------------------------------------------------
  
  
# paste 사용하기1 : 변수 안에 문자열을 넣고, 
# sep 매개변수를 통해 중간에 들어가는 값 끼워 넣기
str <- paste('good', 'morning', sep=' / ')
str
  
  
# paste 사용하기2 : 변수로도 활용 가능하다!
a <- '나의 나이는'
b <- 20
c <- '입니다'
paste0(a, b, c, sep = ' ')
paste0(a, b, c, sep = ' ')
  
  
# paste 사용하기3 : 연속된 자료에 공통된 단일 자료 붙이기
a <- 1:12
b <- '월'
c <- paste(a, b, sep='')
c
  
  
# paste 사용하기4 : 응용!
sales <- c(750, 740, 760, 680, 700, 710, 850, 890, 700, 720, 690, 730)
names(sales) <- paste(1:12, '월', sep='')
sales

sales['7월']                # 인덱스로 접근해서 자료 뽑아오기
sales['1월']+sales['2월']   # 인덱스로 접근해서 뽑아온 자료로 연산

max.month <- sort(sales, decreasing=T)  
max.month[1]
# 오름차순으로 정렬해서 가장 매출액이 큰 달 찾기

sum(sales[1:6])
# 상반기 매출액 출력  


-------------------------------------------------------------------------
  
  
# 벡터 연산 : 연산자를 주면 각각 연산해줌
d <- c(1,4, 3, 7, 8)
2*d
d-5
3*d + 4


# 벡터연산2
# 연산이 가능하려면 벡터의 길이와 자료형이 같아야 함
x <- c(1, 2, 3, 4)
y <- c(5, 6, 7, 8)
x + y
x * y
z <- x + y
z


# 벡터연산3
m <- c(x, y)
m
n <- c(y, x)
n
p <- c(x, y, 90, 100)
p


# 벡터연산4
v1 <- c(1, 2, 3, 4)
v2 <- c('John', 'Jane', 'Tom')
v3 <- c(v1, v2)     # 벡터끼리 벡터로 같이 묶어주면 같이 합쳐짐
v3


# 벡터연산5
d <- c(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
sum(d)          # 자료들의 합
sum(2*d)        # 합에 *2
length(d)       # 자료들의 전체 갯수
mean(d[1:5])    # 1~5번째 수의 평균값
max(d)          # 자료들의 최대값
min(d)          # 자료들의 최솟값
sort(d)         # 자료들의 오름차순
sort(d, decreasing=FALSE)          # 자료들의 오름차순
sort(d, decreasing=TRUE)           # 자료들의 내림차순

v1 <- median(d)           # 자료들의 중간값
v1
v2 <- sum(d)/length(d)    # 자료들의 중간값
v2


-------------------------------------------------------------------------


# 벡터에 논리연산자 적용
d <- 1:9  # 값 입력
d >= 5    # 5보다 큰 값 출력(TRUE, FALSE)
d>5
d[d>5]    # 5보다 큰 값 출력(숫자)
sum[d>5]  # 5보다 큰 값들의 합
sum[d[d>5]]
d==5

condi <- d > 5 & d < 8
d[condi]
condi


-------------------------------------------------------------------------


# 벡터연산 응용

espresso <- c(4, 5, 3, 6, 5, 4, 7)  
americano <- c(63,68,64,68,72,89,94)
latte <- c(61, 70, 59, 71, 71, 92, 88)
# 각 자료 입력

sale.espresso <- 2 * espresso
sale.americano <- 2.5 * americano
sale.latte <- 3.0 * latte
# 각 자료의 값 계산

sale.day <- sale.espresso + sale.americano + sale.latte
# 기준벡터에 각 계산치 넣기
names(sale.day) <- c('Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat', 'Sun')
# 데이터에 인덱싱 해주기
sale.day # 요일별 매출액 출력

sum(sale.day) # 매출액의 합산

sale.mean <- mean(sale.day) # 매출액의 평균치

names(sale.day[sale.day >= sale.mean]) # 평균 이상인 요일 구하기


-------------------------------------------------------------------------
  

# 팩터

bt <- c('A', 'B', 'B', 'O', 'AB', 'A')  # 문자형 벡터 bt 정의
bt.new <- factor(bt)                    # 팩터 bt.new
bt
bt.new                        # 자료들의 최대값
bt[5]                         # 벡터 bt의 5번째 값
bt.new[5]                     # 팩터 bt.new의 5번째 값
levels(bt.new)
as.integer(bt.new)            # 팩터 bt.new의 값을 숫자형으로 변경
bt.new[7] <- 'B'              # 팩터에 기존에 있던 값이므로 삽입 가능
bt.new[8] <- 'C'              # 팩터에 기존에 있던 값이 아니므로 삽입 불가
bt.new


-------------------------------------------------------------------------


# 리스트 활용
  
h.list <- c('balling', 'tennis', 'ski')   # 벡터에 값 저장
person <- list(name= 'Tom', age = 25, student = TRUE, hoppy = h.list)
# 리스트 생성
person            # 리스트에 저장된 내용 모두 출력
person[[1]]         # 리스트의 첫번째 값 출력
person$name       # 리스트에서 값의 이름이 name인 값 출력
person[[4]][3]      # 리스트의 네번째 값 출력


-------------------------------------------------------------------------
  

# 리스트 응용
  
cafe <- list(espresso = c(4, 5, 3, 6, 5, 4, 7),
             americano = c(63, 68, 64, 68, 72, 89, 94),
             latte = c(61, 70, 59, 71, 71, 92, 88),
             price = c(2.0, 2.5, 3.0),
             menu = c('espresso', 'americano', 'latte'))
# 자료들을 리스트로 제작해서 하나의 변수에 넣어줌

cafe$menu <- factor(cafe$menu)
#카페 메뉴를 팩터화

names(cafe$price) <- cafe$menu
#카페 메뉴를 가격에 인덱싱

sale.espresso <- cafe$price['espresso'] * cafe$espresso
sale.americano <- cafe$price['americano'] * cafe$americano
sale.latte <- cafe$price['latte'] * cafe$latte

sale.day <- sale.espresso + sale.americano + sale.latte #요일별 매출액
names(sale.day) <- c('Mon', 'Tue', 'Wed', 'Tur', 'Fri', 'Sat','Sun')
sum(sale.day)                              # 총 매출액
sale.mean <- mean(sale.day)               # 평균 매출액
names(sale.day[sale.day >= sale.mean])    # 평균 매출액 이상인 요일 추출


-------------------------------------------------------------------------
