# 조건에 맞는 데이터 위치 탐색 : which
score <- c(76,84,69,50,95,60,82,71,88,84)
which(score == 69) 
which(score >=85)
max(score)
which.max(score)
min(score)
which.min(score)

idx <- which(score<=60) # 60이상인 값만 뽑아서 idx에 넣기 
score[idx] <- 0 # 원하는 값 삽입입
score 

idx <- which(score >= 80)
score.high <- score[idx]
score.high

score.high2 <- subset(score, score>=80)
score.high2

idx <- which(iris$Petal.Length > 5.0)
idx
iris.big <- iris[idx,]
iris.big
dim(iris.big)
nrow(iris.big)


score <- c(60,40,95,80)
names(score) <- c('John', 'Jane', 'Tom', 'David')
score
idx <- which.max(score)
names(score)[idx]


################################################################################


library(reshape2)

# 성별별로 구분
unique(tips$sex) # 데이터의 레벨이 뭐가 있는지 알려줌

idx <- which(tips[, 'sex'] == 'Female')
avg.female <- mean(tips[idx, 'tip'])
avg.female

idx <- which(tips[, 'sex'] == 'Male')
avg.male <- mean(tips[idx, 'tip'])
avg.male


###############################################################################


# 흡연자 기준으로 구분
unique(tips$smoker)

idx <- which(tips$smoker == 'Yes')
avg.smoker <- mean(tips[idx, 'tip'])
avg.smoker

idx <- which(tips$smoker == 'NO')
avg.nonsmoker <- mean(tips[idx, 'tip'])
avg.nonsmoker

unique(tips$smoker)[1]
unique(tips$smoker)[2]


###############################################################################


source('myfunc.R')
meanbycol.tip(tips, 'sex')

tips.new <- categorize.tip(tips)
head(tips.new)


