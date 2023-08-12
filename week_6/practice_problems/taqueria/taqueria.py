
# Taqueria Menu
taqueria_menu = {
    "Baja Taco": 4.00,
    "Burrito": 7.50,
    "Bowl": 8.50,
    "Nachos": 11.00,
    "Quesadilla": 8.50,
    "Super Burrito": 8.50,
    "Super Quesadilla": 9.50,
    "Taco": 3.00,
    "Tortilla Salad": 8.00
}

# Order
total_cost = 0

while True:
    try:
        item = input("Order: ").title()
        if item in taqueria_menu.keys():
            total_cost += taqueria_menu[item]
            print(f"Total: ${total_cost:.2f}")
        else:
            pass
    except EOFError:
        print('\n')
        break


