
# 벡터의 활용
age <- c(28, 17, 35, 46, 23, 67, 30, 50)
age

young <- min(age)
old <- max(age)

# cat : 문자열과 변수를 한번에 출력해주는 함수
cat('가장 젊은 사람의 나이는 ', young,'이고, ',
    '가장 나이든 사람의 나이는 ', old,'입니다. \n')

getwd()

--------------------------------------------------------------------------------
  

# svDialogs 활용하기 1
# 패키지 설치 = GUI 만들어주는 패키지
install.packages('svDialogs')
library(svDialogs)

# 값을 문자형으로 입력받아서 변수에 할당
user.input <- dlgInput('Input icome')$res # dlgInput('텍스트박스 위 메세지')
user.input
class(user.input) # 받은 변수의 자료형이 무엇인지 확인

# 받은 변수를 숫자형으로 형변환
income <- as.numeric(user.input) 
income
class(income)  # 받은 변수의 자료형이 무엇인지 확인

tax <- income * 0.1 # 변환한 숫자로 연산 가능
cat('세금 : ', tax) # 출력
cat('총 금액 : ', tax+income)


--------------------------------------------------------------------------------
  

# print와 cat의 활용
x <- 26
y <- '입니다'
z <- c(10,20,30,40)

print(x)
print(y)
print(z)
print(iris[1:5,])
print(x,y)

cat(x,'\n')
cat(y,'\n')
cat(z,'\n')
cat(x,y,'\n')
cat(iris[1:5,],'\n')


--------------------------------------------------------------------------------
  

# svDialogs 활용하기 2
library(svDialogs)
height <- dlgInput('Input hegiht(cm)')$res
weight <- dlgInput('Input weight(kg)')$res

height <- as.numeric(height)
weight <- as.numeric(weight)

height <- height/100
bmi <- weight/(height^2)

cat('입력한 키는 ', height*100, 'cm, 몸무게는 ', weight, 'kg입니다. \n', 
    sep="")
cat('BMI는 ', bmi, ' 입니다.', sep="")


--------------------------------------------------------------------------------
  

# 작업폴더 설정하기 1
getwd() # 현재 위치 확인
setwd('D:\\Rworks') # 새로운 저장위치로 이동(경로지정시 '/'을 쓰거나 '\\'을 씀)
getwd()


--------------------------------------------------------------------------------
  

# 작업폴더 설정하기 2
setwd('D:/Rworks')
air <- read.csv('airquality.csv', header = T)
head(air)
class(air)
str(air)


--------------------------------------------------------------------------------
  

# csv파일에 데이터 쓰기
setwd('D:/Rworks')

# 세토사만 추출
my.iris <- subset(iris, Species == 'setosa') 
# csv 파일에 데이터 저장
write.csv(my.iris, 'my_iris.csv', row.names=F) 

# 버지니카만 추출
my.iris <- subset(iris, Species == levels(iris[,5])[3]) 
# csv 파일에 데이터 저장 / row.names = T이면 행의 숫자 적어줌
write.csv(my.iris, 'my_iris_virginica.csv', row.names=T) 


--------------------------------------------------------------------------------