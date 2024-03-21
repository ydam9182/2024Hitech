# 남은 일생 계산기
# 1년은 365일, 52주, 12개월

age = input("당신의 나이는 몇살일까요? ")

age_as_int = int(age)

years_remaining = 90 - age_as_int
days_remaining = years_remaining * 365
week_remaining = years_remaining * 52
months_remaining = years_remaining * 12

print(months_remaining)

message = f"당신의 남은 {days_remaining} 날, {week_remaining} 주, {months_remaining} 월"

print(message)
