print("Welcome to the tip calculator!")
total_bill = float(input("What was the total bill? $"))
tip_percent = int(input("How much tip would you like to give? 10, 12, or 15? "))
split_count = int(input("How many people to split the bill? "))
amount_payed = total_bill * (1 + (tip_percent/100))/ split_count
print(f"Each person should pay: ${amount_payed:.2f}")