#  RedBlackTree.py
#  CPSC3620 Project
#  Created by Henok Lamiso on 2021-11-26.
#  This file contains the implementation for Red-Black Tree Algorithms in Python

# define structure of a node in the tree
class Node:
    def __init__(self, key, value, color = 'red'):
        self.key = key
        self.value = value
        self.color = color
        self.left = None
        self.right = None
        self.parent = None

    def __str__(self):
        return str(self.key) + ' ' + str(self.value) + ' ' + self.color

# define structure of a tree

class RedBlackTree:
    def __init__(self):
        self.root = None
        self.size = 0

    def __str__(self):
        return str(self.root)

    def __len__(self):
        return self.size
    
    def __contains__(self, key):
        return self.search(key) != None
    
    def __getitem__(self, key):
        return self.search(key).value
    
    def __setitem__(self, key, value):
        self.insert(key, value)
    
    def __delitem__(self, key):
        self.delete(key)
    
    def search(self, key):
        return self.search_helper(self.root, key)
    
    def search_helper(self, node, key):
        if node == None:
            return None
        elif node.key == key:
            return node
        elif node.key > key:
            return self.search_helper(node.left, key)
        else:
            return self.search_helper(node.right, key)
    
    def insert(self, key, value):
        self.root = self.insert_helper(self.root, key, value)
        self.root.color = 'black'
    
    def insert_helper(self, node, key, value):
        if node == None:
            self.size += 1
            return Node(key, value)
        elif node.key > key:
            node.left = self.insert_helper(node.left, key, value)
            node.left.parent = node
        else:
            node.right = self.insert_helper(node.right, key, value)
            node.right.parent = node
        return self.balance(node)
    
    def balance(self, node):
        if self.is_red(node.right) and not self.is_red(node.left):
            node = self.rotate_left(node)
        if self.is_red(node.left) and self.is_red(node.left.left):
            node = self.rotate_right(node)
        return node

    def rotate_left(self, node):
        x = node.right
        node.right = x.left
        if x.left != None:
            x.left.parent = node
        x.parent = node.parent
        if node.parent == None:
            self.root = x
        elif node == node.parent.left:
            node.parent.left = x
        else:
            node.parent.right = x
        x.left = node
        node.parent = x
        return x

    def rotate_right(self, node):
        x = node.left
        node.left = x.right
        if x.right != None:
            x.right.parent = node
        x.parent = node.parent
        if node.parent == None:
            self.root = x
        elif node == node.parent.right:
            node.parent.right = x
        else:
            node.parent.left = x
        x.right = node
        node.parent = x
        return x

    def delete(self, key):
        self.root = self.delete_helper(self.root, key)
        self.root.color = 'black'

    def delete_helper(self, node, key):
        if node == None:
            return None
        elif node.key > key:
            node.left = self.delete_helper(node.left, key)
        elif node.key < key:
            node.right = self.delete_helper(node.right, key)
        else:
            if node.left == None:
                return node.right
            elif node.right == None:
                return node.left
            else:
                y = self.successor(node)
                node.key = y.key
                node.value = y.value
                node.right = self.delete_helper(node.right, y.key)
        if self.is_red(node.right) and not self.is_red(node.left):
            node = self.rotate_left(node)
        if self.is_red(node.left) and self.is_red(node.left.left):
            node = self.rotate_right(node)
        if self.is_red(node.left) and self.is_red(node.right):
            self.flip_colors(node)
        return node

    def successor(self, node):
        if node.right != None:
            return self.minimum(node.right)
        y = node.parent
        while y != None and node == y.right:
            node = y
            y = y.parent
        return y

    def minimum(self, node):
        while node.left != None:
            node = node.left
        return node

    def flip_colors(self, node):
        node.color = 'red'
        node.left.color = 'black'
        node.right.color = 'black'

    def is_red(self, node):
        if node == None:
            return False
        return node.color == 'red'

    def is_black(self, node):
        if node == None:
            return True
        return node.color == 'black'

    def is_balanced(self):
        return self.is_balanced_helper(self.root)

    def is_balanced_helper(self, node):
        if node == None:
            return True
        if abs(self.black_height(node.left) - self.black_height(node.right)) > 1:
            return False
        return self.is_balanced_helper(node.left) and self.is_balanced_helper(node.right)

    def black_height(self, node):
        if node == None:
            return 0
        if self.is_black(node):
            return 1 + self.black_height(node.left)
        return self.black_height(node.left)

    def inorder(self):
        return self.inorder_helper(self.root)

    def inorder_helper(self, node):
        if node == None:
            return []
        return self.inorder_helper(node.left) + [node.key] + self.inorder_helper(node.right)

    def preorder(self):
        return self.preorder_helper(self.root)

    def preorder_helper(self, node):
        if node == None:
            return []
        return [node.key] + self.preorder_helper(node.left) + self.preorder_helper(node.right)

    def postorder(self):
        return self.postorder_helper(self.root)

    def postorder_helper(self, node):
        if node == None:
            return []
        return self.postorder_helper(node.left) + self.postorder_helper(node.right) + [node.key]

    def levelorder(self):
        return self.levelorder_helper(self.root)

    def levelorder_helper(self, node):
        if node == None:
            return []
        queue = [node]
        result = []
        while len(queue) > 0:
            node = queue.pop(0)
            result.append(node.key)
            if node.left != None:
                queue.append(node.left)
            if node.right != None:
                queue.append(node.right)
        return result

    def height(self):
        return self.height_helper(self.root)

    def height_helper(self, node):
        if node == None:
            return 0
        return 1 + max(self.height_helper(node.left), self.height_helper(node.right))

    def size(self):
        return self.size_helper(self.root)

    def size_helper(self, node):
        if node == None:
            return 0
        return 1 + self.size_helper(node.left) + self.size_helper(node.right)

    def is_bst(self):
        return self.is_bst_helper(self.root, None, None)

    def is_bst_helper(self, node, min, max):
        if node == None:
            return True
        if min != None and node.key < min:
            return False
        if max != None and node.key > max:
            return False
        return self.is_bst_helper(node.left, min, node.key) and self.is_bst_helper(node.right, node.key, max)

    def is_binary_search_tree(self):
        return self.is_binary_search_tree_helper(self.root, None, None)

    def is_binary_search_tree_helper(self, node, min, max):
        if node == None:
            return True
        if min != None and node.key < min:
            return False
        if max != None and node.key > max:
            return False
        return self.is_binary_search_tree_helper(node.left, min, node.key) and self.is_binary_search_tree_helper(node.right, node.key, max)

    def is_valid_bst(self):
        return self.is_valid_bst_helper(self.root, None, None)

    def is_valid_bst_helper(self, node, min, max):
        if node == None:
            return True
        if min != None and node.key < min:
            return False
        if max != None and node.key > max:
            return False
        return self.is_valid_bst_helper(node.left, min, node.key) and self.is_valid_bst_helper(node.right, node.key, max)


