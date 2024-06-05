#사용자 정의 함수 제작하기 
mymax <- function(x, y){
  num.max <- x
  if(y>x){
    num.max <- y
  }
  return(num.max)
}

cat('5와 10중 더 큰 숫자는', mymax(5,10), '입니다.\n')

mymax(479234,180905)
a <- mymax(45,15)
b <- mymax(31,77)
print(a+b)

mymax(479234,180905,46546)


###############################################################################


# 매개변수의 기본값 설정
mydiv <- function(x, y=2){
  result <- x/y
  return(result)
}
mydiv(x=10, y=3)
mydiv(10,3)
mydiv(10)

mydiv2 <- function(x=4, y=2){
  result <- x/y
  return(result)
}
mydiv2()


###############################################################################


# 사용자정의 함수의 여러 값 반환
myfunc <- function(x, y){
  val.sum <- x+y
  val.mul <- x*y
  return(list(sum=val.sum, mul = val.mul))
  # 리턴값의 매개변수명(sum=, mul=같이)을 적어주면 출력할때 이름을 붙여줌
}
result <- myfunc(5,8)
s <- result$sum
m <- result$sum
cat('5+8 =', s, '\n')
cat('5+8 =', m, '\n')
print()
r <- val.sum # 사용자정의 함수의 지역변수 -> 외부에선 접근 불가능


###############################################################################


# 외부 파일에서 함수 불러오기
setwd('D:/HT_2405340102_PYD/ai_deeplearning/240605')
source('myfunc.R')

# 불러온 함수의 기능 사용
a <- mydiv(20,4)
b <- mydiv(30,4)
a+b
mydiv(mydiv(20,2), 5)


###############################################################################


