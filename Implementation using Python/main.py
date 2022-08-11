# call the implementation from Implementation using Python/RedBlackTree.py
# Show menu for user and get user input

import RedBlackTree

def main():
    tree = RedBlackTree.RedBlackTree()
    while True:
        print("1. Insert")
        print("2. Delete")
        print("3. Search")
        print("4. Print")
        print("5. Exit")
        choice = int(input("Enter your choice: "))
        if choice == 1:
            key = int(input("Enter key: "))
            value = int(input("Enter value: "))
            tree.insert(key, value)
        elif choice == 2:
            key = int(input("Enter key: "))
            tree.delete(key)
        elif choice == 3:
            key = int(input("Enter key: "))
            print(tree.search(key))
        elif choice == 4:
            print(tree)
        elif choice == 5:
            break
        else:
            print("Invalid choice")

            