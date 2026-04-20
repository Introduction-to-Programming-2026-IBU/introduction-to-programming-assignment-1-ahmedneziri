
menu = {
    1: ("Apple",  0.50),
    2: ("Banana", 0.30),
    3: ("Milk",   1.20),
    4: ("Bread",  2.00),
}

cart  = {}   # { item_name: quantity }
total = 0.0

# Display the menu
print("--- Shop Menu ---")
for number, (name, price) in menu.items():
    print(f"{number}. {name:<10} ${price:.2f}")
print("5. Done")

# Shopping loop
while True:
    try:
        choice = int(input("\nChoose an item (1-5): "))
        
        if choice == 5:
            break
            
        if choice in menu:
            item_name, item_price = menu[choice]
            
            # Add to cart dictionary
            if item_name in cart:
                cart[item_name] += 1
            else:
                cart[item_name] = 1
                
            # Update running total
            total += item_price
            print(f"Added {item_name} to cart.")
        else:
            print("Invalid choice, try again.")
            
    except ValueError:
        print("Please enter a valid number.")

# Print the receipt
print("\n--- Receipt ---")
if not cart:
    print("Your cart is empty.")
else:
    for item, qty in cart.items():
        # Retrieve the price from the menu to show line totals if desired
        # Finding the price by matching the name in the menu dict
        price = next(p for n, p in menu.values() if n == item)
        print(f"{item:<10} x{qty}  (${price * qty:.2f})")

print("-" * 20)
print(f"Total: ${total:.2f}")
print("Thank you for shopping!")