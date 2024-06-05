mydiv <- function(x, y){
  result <- x/y
  return(result)
}

library(reshape2)
meanbycol.tip <- function(tips, colname){
  value <- unique(tips[, colname]) 
  # tips테이블에서 colname열의 중복제외된 값 받아오기
  result <- list()  # 값을 저장할 리스트 제작
  for(i in 1:length(value)){ # 추출된 값을 기준으로 반복문
    idx <- which(tips[,colname] == value[i])
    # 
    result[i] <- mean(tips[idx, 'tip'])
  }
  names(result) <- value
  return(result)
}


meanbycol.tip2 <- function(tips, colname){
  result <- list()
  for(i in 1:length(value)){
    idx <- which(tips[,colname] == unique(tips[, colname])[i])
    result[i] <- mean(tips[idx, 'tip'])
  }
  names(result) <- value
  return(result)
}


categorize.tip <- function(tips){
  tip_ratio <- tips$tip / tips$total_bill * 100
  class <- c()
  
  for(i in 1:nrow(tips)){
    if(tip_ratio[i] < 10){
      class[i] <- 1
    }else if(tip_ratio[i] < 15){
      class[i] <- 2
    }else if(tip_ratio[i] < 20){
      class[i] <- 3
    }else{
      class[i] <- 4
    }
  }
  tips.new <- cbind(tips, type = class, ratio = tip_ratio)
  return(tips.new)
}
