
## if문 ##
job.type <- 'A'

if(job.type == 'B'){
  bonus <- 200
} else{
  bonus <- 100
}

print(bonus)


################################################################################


# else 생략
job.type <- 'A'
bonus <- 100
if(job.type == 'B'){
  bonus <- 200
}
print(bonus)

#--------------------#

a <- 10
if (a<5){
  print(a)
}else{
  print(a*10)
  print(a/10)
}

#--------------------#

a <- 10
b <- 20
if(a>5 & b>5){
  print(a+b)
}
if(a>5 | b>30){
  print(a*b)
}

#--------------------#

job.type <- 'A'
bonus <- 100
if(job.type == 'B'){
  bonus <- 200
}
print(bonus)


################################################################################


##회원등급 분류하고 혜택 부여하기##
library(svDialogs)
purchase <- dlgInput('Enter the purchase amount')$res
purchase <- as.numeric(purchase)

type <- NULL
ratio <- NULL

if(purchase >= 300000){
  type <- '플래티넘'
  ratio <- 0.07
}else if(purchase >= 200000){
  type <- '골드'
  ratio <- 0.05
}else if(purchase >= 100000){
  type <- '실버'
  ratio <- 0.03
}else{
  type <- '프렌즈'
  ratio <- 0.01
}

cat('고객님은', type,'회원으로 구매액의', ratio*100, '%가 적립됩니다.')
cat('낸 금액 :', purchase, ', 회원 등급 :', type, ', 회원 할인률 :', ratio )


################################################################################


## for문 : 다른언어와 다르게 0이 아닌 1부터 시작 ##
for(i in 1:5){
  print('*')
  print(i)
}

#--------------------#

for(i in 6:10){
  print(i)
}

#--------------------#

for(i in 1:9){
  print(i)
  cat('2 *', i, '=', 2*i, '\n')
  print('2 *', i, '=', 2*i, '\n')
}

#--------------------#

for(i in 1:20){
  if(i%%2 == 0){
    cat(i, ' ')
  }
}

#--------------------#

for(i in 1:20){
  if(i%%2 != 0){ #if(i%%2 == 1)
    cat(i, ' ')
  }
}

#--------------------#

#sum <- NULL
sum <- 0
for(i in i:100){
  sum <- sum + i
}
print(sum)


################################################################################


## for문으로 iris 구하기 ##
nrow <- nrow(iris) #iris dataset에서 행의 갯수 받아오기
mylabel <- c() #새로운 만들 빈 벡터 생성

for(i in 1:nrow){ # 모든 행들의 꽃잎의 길이를 조건검사해서 벡터 내용 넣어주기
  if(iris$Petal.Length[i] <= 1.6){
    mylabel[i] <- 'L'
  }else if(iris$Petal.Length[i] >= 5.1){
    mylabel[i] <- 'H'
  }else{
    mylabel[i] <- 'M'
  }
}

print(mylabel)
newds <- data.frame(iris$Petal.Length, mylabel)
head(newds)


################################################################################


## while문 사용해보기 ##
sum <- 0
i <- 1
while(i <= 100){
  sum <- sum +i
  i <- i+1
}
print(sum)


################################################################################


## apply(dataframe or vector, 1 or 2, 함수) : 
## dataframe or vector을 행/열 방향으로로 함수 적용
apply(iris[,1:4], 1, mean) # 행 방향으로 함수 적용
apply(iris[,1:4], 2, mean) # 열 방향으로 함수 적용


# 예제1 : 응시자 10명의 점수로 합격 여부 판단
sub1 <- c(14,16,12,20,8,6,12,18,16,10)
sub2 <- c(18,14,14,16,10,12,10,20,14,14)
sub3 <- c(44,38,30,48,42,50,36,52,54,32) # 3과목 각각 10명의 점수 넣기
score <- data.frame(sub1, sub2, sub3) #score라는 데이터프레임에 3개의 열 만들어줌

total <- apply(score, 1, sum) # total이라는 변수에 score데이터프레임의 행대로 합산
scoreset <- cbind(score, total) # scoreset이라는 데이터프레임에 score의 3열과 total의 한 행을 넣어줌

print(scoreset)

result <- c() # 합격자들을 담을 벡터 생성

for(i in 1:nrow(scoreset)){
  if(scoreset[i,1] < 20*0.4 | scoreset[i, 2] < 20*0.4 
     | scoreset[i, 3] < 20*0.4){ # 과락
    result[i] <- '불합격'
  }else if(scoreset[i,4] >= 60){ # 평균 이상이면 합격
    result[i] <- '합격'
  }else{ # 
    result[i] <- '불합격'
  }
  cat(i, '번째 응시생은', result[i], '입니다.\n')
}
