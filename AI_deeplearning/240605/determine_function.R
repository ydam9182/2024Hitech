determine <- function(score){
  total <- apply(score, 1, sum)
  scoreset <- cbind(score, total)
  result <- c()
  for(i in 1:nrow(scoreset)){
    if(scoreset[i,1] < 20*0.4 | scoreset[i,2] < 20*0.4 | scoreset[i,3] < 60*0.4){
      result[i] <- '불합격'
    } else if(scoreset[i,4] >= 60){
      result[i] <- '합격'
    } else{
      result[i] <- '불합격'
    }
    #cat(i,'번째 응시생은', result[i], '입니다.\n')
  }
  return(result)
}
