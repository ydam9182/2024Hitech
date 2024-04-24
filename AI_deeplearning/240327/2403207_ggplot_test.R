#ggplot2 패키지 설치
#install.packages('ggplot2') # 처음 install시 최초 1회만 실행

#ggplot2 불러오기
library(ggplot2) # 각 파일에서 사용할때마다 로드 필요
ggplot(data = iris, aes(x = Petal.Length, y = Petal.Width)) + geom_point()