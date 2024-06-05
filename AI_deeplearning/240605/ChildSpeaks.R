# 아이들 말문 트이는 시기
# 패키지 설치
install.packages('Stat2Data')
library(Stat2Data)
data(ChildSpeaks)
str(ChildSpeaks)  # 패키지의 정보 출력

# m1(나이점수)열을 추가해서 값 삽입
idx <- which(ChildSpeaks$Age < 9) 
ChildSpeaks[idx, 'm1'] <- 5
idx <- which(ChildSpeaks$Age >=  9 & ChildSpeaks$Age < 15)
ChildSpeaks[idx, 'm1'] <- 4
idx <- which(ChildSpeaks$Age >=  15 & ChildSpeaks$Age < 21)
ChildSpeaks[idx, 'm1'] <- 3
idx <- which(ChildSpeaks$Age >=  21 & ChildSpeaks$Age < 27)
ChildSpeaks[idx, 'm1'] <- 2
idx <- which(ChildSpeaks$Age >= 27)
ChildSpeaks[idx, 'm1'] <- 1
print(ChildSpeaks)

# m2(게젤점수)열을 추가해서 값 삽입
ChildSpeaks$m2 <- 0 
idx <- which(ChildSpeaks$Gesell < 70) 
ChildSpeaks$m2[idx] <- 1
idx <- which(ChildSpeaks$Gesell >= 70 & ChildSpeaks$Gesell < 90)
ChildSpeaks$m2[idx] <- 2
idx <- which(ChildSpeaks$Gesell >= 90 & ChildSpeaks$Gesell < 110)
ChildSpeaks$m2[idx] <- 3
idx <- which(ChildSpeaks$Gesell >= 110 & ChildSpeaks$Gesell < 130)
ChildSpeaks$m2[idx] <- 4
idx <- which(ChildSpeaks$Gesell >= 130)
ChildSpeaks$m2[idx] <- 5
print(ChildSpeaks)

# total(합산점수)열을 추가해서 값 삽입
ChildSpeaks$total <- ChildSpeaks$m1 + ChildSpeaks$m2
ChildSpeaks$result <- 0

idx <- which(ChildSpeaks$total < 3)
ChildSpeaks$result[idx] <- '매우느림'
idx <- which(ChildSpeaks$total >= 3 & ChildSpeaks$total < 5)
ChildSpeaks$result[idx] <- '느림'
idx <- which(ChildSpeaks$total >= 5 & ChildSpeaks$total < 7)
ChildSpeaks$result[idx] <- '보통'
idx <- which(ChildSpeaks$total >= 7 & ChildSpeaks$total < 9)
ChildSpeaks$result[idx] <- '빠름'
idx <- which(ChildSpeaks$total >= 9)
ChildSpeaks$result[idx] <- '매우빠름'
print(ChildSpeaks)

ChildSpeaks
ChildSpeaks[which.min(ChildSpeaks$total),]