# call the implementation from Implementation using Python/RedBlackTree.py
# Show menu for user and get user input
def menu():
    print('1. Insert')
    print('2. Delete')
    print('3. Search')
    print('4. Print')
    print('5. Exit')
    return input('Enter your choice: ')

# Insert a new node in the tree
def insert(tree, key, value):
    tree.insert(key, value)
    print('Inserted ' + str(key) + ' ' + str(value))

# Delete a node in the tree
def delete(tree, key):
    tree.delete(key)
    print('Deleted ' + str(key))

# Search for a node in the tree
def search(tree, key):
    node = tree.search(key)
    if node == None:
        print('Not found')
    else:
        print('Found ' + str(node.key) + ' ' + str(node.value))

# Print the tree
def print_tree(tree):
    print(tree)

# Main function