
# dataframe
dim(iris) #
nrow(iris)
ncol(iris)
colnames(iris)
head(iris)
tail(iris)

str(iris) #전체 정보
iris[,5] # 5열에 있는 값 전체
levels(iris[,5]) # 5열에서 중복된 값 제거한 레벨
table(iris[,"Species"]) #품종 종류별로 행에 몇개 있는지

colSums(iris[,-5]) 
colMeans(iris[,-5])
rowSums(iris[,-5])[1:2]
rowMeans(iris[,-5])


--------------------------------------------------------------------------------


#transpose function
z <- matrix(1:20, nrow=4, ncol=5)  
z
t(z)

t(iris)
t(mtcars)


--------------------------------------------------------------------------------

  
#subset : 조건에 맞는 데이터만 추출 
IR.1 <- subset(iris, Species == "setosa")
IR.1
IR.2 <- subset(iris, Sepal.Length>5.0 & Sepal.Width>4.0)

IR.2
IR.2[,c(2,4)]

IR.3 <- subset(iris, Species == "virginica")
#IR.3 <- subset(iris, Species == levels(iris[,5])[3])
IR.3


--------------------------------------------------------------------------------


# matrix의 연산 
a <- matrix(1:20, 4, 5)
b <- matrix(21:40, 4, 5)
a
b

2*a
a+b
a <- a*3
b <- b-5
a
b


--------------------------------------------------------------------------------
    

# Using class 
class(iris)
is.matrix(iris) # is it matrix?
is.data.frame(iris) # is it dataframe?

class(state.x77)
is.matrix(state.x77)
is.data.frame(state.x77)

class(mtcars)
is.matrix(mtcars)
is.data.frame(mtcars)


# matrix -> dataframe
is.matrix(state.x77)
st <- data.frame(state.x77)
head(st)
class(st)

# dataframe -> matrix
is.data.frame(iris[,1:4])
iris.m <- as.matrix(iris[,1:4])
head(iris.m)
class(iris.m)
# matrix는 행과 열로 표현, dataframe은 행 이름으로 표현

iris[,"Species"] # 벡터-매트릭스,데이터프레임
iris[,5] # 벡터-매트릭스,데이터프레임
iris["Species"] #데이프레임-데이터프레임
iris[5] # 데이터프레임-데이터프레임
iris$Species # 벡터-데이터프레임


--------------------------------------------------------------------------------

# example of dataframe 1
class(trees)
colnames(trees)
str(trees)
dim(trees)

girth.mean <- mean(trees$Girth)

candidate <- subset(trees, Girth >= grith.mean & Height > 80 & Volume > 50)
candidate
nrow(candidate)


--------------------------------------------------------------------------------


# example of dataframe 2
install.packages('reshape2') # tips의 기본정보 확인
library(reshape2)
tips
str(tips)
head(tips)
tail(tips)

# table : 원하는 정보를 뽑는다
table(tips[,"smoker"]) # table(tips$smoker)
table(tips[,"time"])  # table(tips$time)
table(tips[,"day"])  # table(tips$day)
levels(tips[,"smoker"])

# tips 속의 점심과 저녁의 데이터를 따로 뽑아냄
dinner <- subset(tips, time == 'Dinner')
lunch <- subset(tips, time == 'Lunch')

# 점심과 저녁의 각각 일별 횟수
table(dinner$day)
table(lunch$day)

# 점심과 저녁의 total_bill, tip, size의 열별 평균값 구함
colMeans(dinner[c('total_bill','tip','size')])
colMeans(lunch[c('total_bill','tip','size')])

# tips의 전체 금액 중 팁의 비율 구하기
tip.rate <- tips$tip/tips$total_bill
mean(tip.rate)

# 점심과 저녁의 각각의 전체 금액 중 팁 비율 구하기
lunch.tiprate <- lunch$tip/lunch$total_bill
mean(lunch.tiprate)
round(mean(lunch.tiprate), 2) # 소숫점 2째자리까지만 출력
dinner.tiprate <- dinner$tip/dinner$total_bill
mean(dinner.tiprate)
round(mean(dinner.tiprate), 2) # 소숫점 2째자리까지만 출력

