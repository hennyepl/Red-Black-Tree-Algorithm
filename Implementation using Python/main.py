# call the implementation from RedBlackTree.py
# Show menu for user and get user input

# import the RedBlackTree class from RedBlackTree.py
from RedBlackTree import RedBlackTree

# Print Menu options

def print_menu():
    print("1. Insert")
    print("2. Delete")
    print("3. Search")
    print("4. Print")
    print("5. Exit")
    print("")

# Get user input
# Return the user input as an integer
# If the input is not an integer, keep asking for input
# If the input is an integer, return the input
# If the input is not 1-5, keep asking for input

def get_input():
    while True:
        try:
            user_input = int(input("Enter your choice: "))
            if user_input < 1 or user_input > 5:
                print("Invalid input. Please enter a number between 1 and 5.")
                continue
            else:
                return user_input
        except ValueError:
            print("Invalid input. Please enter a number between 1 and 5.")
            continue

# Insert a key and value into the tree

def insert(tree, key, value):
    tree.insert(key, value)

# Delete a key and value from the tree
def delete(tree, key):
    tree.delete(key)

# Search for a key in the tree
def search(tree, key):
    return tree.search(key)

# Print the tree
def print_tree(tree):
    tree.print_tree()          