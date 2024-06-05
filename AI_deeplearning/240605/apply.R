

# apply 적용하기
apply(iris[,1:4], 1 ,mean) # 행 방향으로 함수적용
apply(iris[,1:4], 2 ,mean) # 열 방향으로 함수적용 


###############################################################################


#apply 적용하기2
sub1 <- c(14,16,12,20,8,6,12,18,16,10)
sub2 <- c(18,14,14,16,10,12,10,20,14,14)
sub3 <- c(44,38,30,48,42,50,36,52,54,32)
score <- data.frame(sub1, sub2, sub3)

total <- apply(score, 1, sum)
scoreset <- cbind(score, total)
print(total)
print(scoreset)

result <- c()
for(i in 1:nrow(scoreset)){
  if(scoreset[i,1] < 20*0.4 | scoreset[i,2] < 20*0.4 | scoreset[i,3] < 60*0.4){
    result[i] <- '불합격'
  } else if(scoreset[i,4] >= 60){
    result[i] <- '합격'
  } else{
    result[i] <- '불합격'
  }
  cat(i,'번째 응시생은', result[i], '입니다.\n')
}
