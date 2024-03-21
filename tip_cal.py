# 팁 계산기

print("----Tip Calculator")

order = float(input("Total pay : "))
tip = int(input("Tip Percent(10, 12, 15) : "))
people = int(input("How many people to pay? : "))

tip_as_percent = tip / 100
total_tip = order * tip_as_percent
total_bill = total_tip + order
bill_per_person = total_bill/people

final_bill = round(bill_per_person,2)
print(f"Total bill per person : {final_bill} $")