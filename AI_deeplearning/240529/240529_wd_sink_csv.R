library(svDialogs)
user.input <- dlgInput('Input income')$res
user.input
income <- as.numeric(user.input) #as.numeric 문자열을 숫자로 바꿈
income
tax <- income * 0.05
cat('세금 : ', tax)


###############################################################################


## print와 cat의 차이점 ##
x<-26
y <- '입니다'
z <- c(10, 20, 30, 40)
print(x, '\n')
print(y, '\n')
print(z, '\n')
cat(x,y, '\n')
print(iris[1:5,])
print(x,y)


###############################################################################


## bmi 출력하기 ##
# 정보 입력 : svDialogs패키지를 이용해서 ui 만들어줌
height <- dlgInput('Input height(cm)')$res
weight <- dlgInput('Input weight(kg)')$res

# 숫자형으로 형변환
height <- as.numeric(height)
weight <- as.numeric(weight)

height <- height/100
bmi <- weight/(height^2)

cat('입력한 키는 ', height*100, 'cm, 몸무게는 ', weight, 'kg입니다. \n', sep="")
cat('BMI는 ', bmi, '입니다.', sep="")


###############################################################################


## 작업폴더 접근하기 ##
getwd() # 현재 위치
setwd('D:/Rworks') # 위치 바꾸기(절대 경로로 지정)
getwd()


###############################################################################


## 작업폴더 접근해서 파일 불러오기 ##
setwd('R:/Rworks/air')
air <- read.csv('airquality.csv', header=F) 
#header = T : 첫째행을 feature로 표현해줌
#header = F : 첫째행을 일반 행으로 인식
head(air)
class(air)


###############################################################################


## 작업폴더를 설정하고 기존 데이터에서 원하는 정보 추출해서 저장 ##
setwd('D:/Rworks/iris')
my.iris <- subset(iris, Species == 'setosa')
write.csv(my.iris, 'my_iris.csv', row.names=F)


###############################################################################


## 엑셀로 데이터를 불러와서 헤더 출력하기 ##
install.packages('xlsx')
library(xlsx)
air <- read.xlsx('D:/Rworks/air/airquailty.xlsx', header = T, sheetIndex = 1)
head(air)


###############################################################################
  
  
## 다이아몬드 데이터셋 ##
# 작업 경로 설정
setwd('D:/Rworks/shiny') 

#ggplot2 불러오기 
library(ggplot2)
str(diamonds)

# 원하는 정보(품질 프리미엄, 무게 2캐럿 이상) 추출
diamonds.new <- subset(diamonds, cut == 'Premium' & carat >= 2)

# 뽑은 정보를 파일로 저장
write.csv(diamonds.new, 'shiny_diamonds.csv', row.names = F)

# 저장한 파일을 새로운 변수에 저장
diamonds.load <- read.csv('shiny_diamonds.csv', header=T)

# 저장한 변수에서 원하는 값 추출출
diamonds.new <- subset(diamonds.load, color != 'D')

# 추출한 데이터를 새로운 csv파일로 저장장
write.csv(diamonds.new, 'shiny_diamonds_pyd.csv', row.names=F)


###############################################################################


## 실행 결과를 파일로 출력하기 ##

setwd('D:/Rworks/sink')
print('Begin work')

# 변수 값 대입
a <- 10; b <- 20

# result.txt라는 파일 생성해서 값을 삽입할수 있게 허용
sink('result.txt', append = T)  # 파일로 출력 시작
# append = T : 내용에 맨 마지막에 이어서 붙임
# append = F : 내용을 삭제하고 넣기
cat('a+b=', a+b, '\n')  # 내용 삽입
sink() # 파일 출력 정지

cat('hello world \n') #rstudio에서 출력

# result.txt라는 파일 생성해서 값을 삽입할수 있게 허용
sink('result.txt', append = T)
cat('a*b=', a*b, '\n') # 내용 삽입
sink() # 파일 출력 정지

print('End work')

# result.txt라는 파일 생성해서 값을 삽입할수 있게 허용
sink('result.txt', append = T)
cat('흑흑 망햇다\n') # 내용 삽입
sink() # 파일 출력 정지


###############################################################################


## table 읽어오기 ##
setwd('D:/Rworks/air')
air2 <- read.table('airquality.txt', header = T, sep = ' ')
head(air2)
head(air2, 3) # 원하는 갯수만큼만 출력력


###############################################################################


## bmi 계산하기2 ##
setwd('D:/Rworks/sink')
library(svDialogs)
height <- dlgInput('Input height(cm) ')$res
weight <- dlgInput('Input weight(kg) ')$res

height <- as.numeric(height)
weight <- as.numeric(weight)

height <- height / 100
bmi <- weight/(height^2)

# sink함수를 통해서 정보들 저장
sink('bmi.txt', append = T)
cat(height*100, weight, bmi)
cat('\n')
sink()

# 저장한 파일을 불러와서 테이블을 만들고 새로운 테이블 형성
result <- read.table('bmi.txt', sep = " ")
result

names(result) <- c('height', 'wieght', 'bmi')
write.table(result, 'bmi_new.txt', row.names = F)


###############################################################################


## 자동차 금액 ##
setwd('D:/Rworks/car')
library(svDialogs)
carprice.new <- read.csv('carprice.csv', header=T)
str(carprice.new) # 파일 내의 정보 확인

input.type <- dlgInput('Input type')$res # 자동차타입 입력
input.city <- dlgInput('Input MPG.city')$res # 시내주행 연비
input.city <- as.numeric(input.city) # 연비는 숫자로 형변환

#원하는 데이터 추출하고 확인
result <- subset(carprice.new, Type == input.type & MPG.city >= input.city)
print(result)

sink('search.txt', append=T) # 파일 만들어서 입력 가능하게 하게
print(result) # 내용 입력
sink() # 파일 닫기기
write.csv(result, 'search.csv', row.names=F)


###############################################################################
