#for문 활용하기
for(i in 1:20){
  if(i%%2==0){
    cat(i, ' ')
  }
}


###############################################################################


#for문 활용하기2
norow <- nrow(iris)
mylabel <- c()
for(i in i:norow){
  if(iris$Petal.Length[i] <= 1.6){
    mylabel[i] <- 'L'
  } else if (iris$Petal.Length[i] >= 5.1){
    mylabel[i] <- 'H'
  } else {
    mylabel[i] <- 'M'
  }
}
print(mylabel)
newds <- data.frame(iris$Petal.Length, mylabel)
head(newds)

newds2 <- cbind(iris, mylabel)
head(newds2)


###############################################################################


#for문 활용하기
# 합산 누적
sum <- 0
i <- 1
while(i <=100){
  sum <- sum+i
  i <- i+1
}
print(sum)


###############################################################################
