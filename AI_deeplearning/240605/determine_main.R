source('determine_function.R')

sub1 <- c(14,16,12,20,8,6,12,18,16,10)
sub2 <- c(18,14,14,16,10,12,10,20,14,14)
sub3 <- c(44,38,30,48,42,50,36,52,54,32)
score <- data.frame(sub1, sub2, sub3)

result <- determine(score)
result

result <- determine(head(score,3))
result
