iris_data <- iris[1:10, 1:4]

# apply 함수 활용하기 : 출력형태를 벡터 형태로 반환
apply(iris_data, 1, mean) # 행 방향으로 함수적용
apply(iris_data, 2, mean) # 열 방향으로 함수적용

# lapply 함수 활용하기 : 열단위로 출력형태를 list형태로 반환
# 형태 : lapply(dataframe, fuction, na.rm = F(NA값 제외))
lapply(iris_data, mean) # 행 방향으로 함수적용


# sapply 함수 활용하기 : 열단위로 출력형태를 list형태로 반환
# 형태 : sapply(dataframe, fuction, na.rm = F(NA값 제외))
sapply(iris_data, mean, simplify = T) # simplify = T : apply
sapply(iris_data, mean, simplify = F) # simplify = F : lapply