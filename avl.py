from sys import exit
from random import randint

class AVL(object):
    def __init__(self, root=None):
        self.root = root

    def printout(self):
        layout = []
        curr_row = [self.root]
        layout.append(curr_row)
        last_row = False
        while True:
            new_row = []
            for node in curr_row:
                if node:
                    new_row.append(node.left)
                    new_row.append(node.right)
                else:
                    new_row.append(None)
                    new_row.append(None)
            if any(cell for cell in new_row):
                curr_row = new_row
                layout.append(curr_row)
            else:
                return(layout)

    def lowest(self):
        lowest = self.root
        while lowest.left:
            lowest = lowest.left
        return lowest

    def highest(self):
        highest = self.root
        while highest.right:
            highest = highest.right
        return highest

    def next_smaller(node):
        if not node.left:
            if node.parent and node.parent.val < node.val:
                return node.parent
            return
        smaller = node.left
        while smaller.right:
            smaller = smaller.right
        return smaller

    def next_bigger(node):
        if not node.right:
            if node.parent and node.parent.val > node.val:
                return node.parent
            return
        bigger = node.right
        while bigger.left:
            bigger = bigger.left
        return bigger

    def add(self, cell):
        parent = self.root
        while cell.parent is None:
            if cell.val == parent.val:
                parent.occurrences += 1
                return
            elif cell.val > parent.val:
                if parent.right == None:
                    parent.right = cell
                    cell.parent = parent
                else:
                    parent = parent.right
            elif parent.left == None:
                parent.left = cell
                cell.parent = parent
            else:
                # if parent.left.parent is not parent:
                #     printing = self.printout()
                #     for line in printing:
                #         print(line)
                #     print("Quitting")
                #     exit()
                # assert parent.right is None or parent.right.parent == parent
                parent = parent.left
        self.rebalance(cell)


    def remove(self, key):
        node = self.root
        while node and node.val != key:
            node = node.left if node.val > key else node.right
        if not node:
            print("Value was not in tree.\n---\n")
            return
        if node.occurrences > 1:
            node.occurrences -= 1
            return
        if not node.right and not node.left:
            "We're a leaf, so just delete ourselves and we're done"
            if node.val > node.parent.val:
                node.parent.right = None
            else:
                node.parent.left = None
            new_node = node.parent

        elif node.right and not node.left:
            '''node.right must be a leaf or else balance is violated. so node.right
            just replaces node. Same logic applies if node.left and not node.right'''
            node.right.parent = node.parent
            if node.val > node.parent.val:
                node.parent.right = node.right
            else:
                node.parent.left = node.right
            new_node = node.parent

        elif node.left and not node.right:
            node.left.parent = node.parent
            if node.val > node.parent.val:
                node.parent.right = node.left
            else:
                node.parent.left = node.left
            new_node = node.parent

        else:
            '''n.b.: We can refactor by just changing vals instead of reassigning chains.

            Because we're looking at next smaller, new_node cannot have a
            right child unless that child is node. But in that case, node must not
            have a left child, which is a case already covered above. Therefore,
            new child must be in node's left subtree, and must not have a right child'''
            new_node = AVL.next_smaller(node)

            if new_node.parent is not node:
                '''new_node is either a leaf, or only has a left child. If the former,
                new_node can just replace node. If the latter, new_node's left child
                takes new_node's place, and then new_node replaces node.'''
                if new_node.left:
                    new_node.left.parent = new_node.parent
                new_node.parent.right = new_node.left
                if node.parent:
                    node.parent.right = new_node
                node.left.parent = new_node
                node.right.parent = new_node
                new_node.left = node.left
                new_node.right = node.right
                new_node.parent = node.parent
                if node.parent:
                    if node.val > node.parent.val:
                        node.parent.right = new_node
                    else:
                        node.parent.left = new_node

            else:
                '''new_node is either a leaf or only has a left child. If the latter,
                left_child must be a leaf. So we don't have to mess with it, we can just
                have new_node replace node.'''
                new_node.parent = node.parent
                new_node.right = node.right
                if node.right:
                    node.right.parent = new_node
                if node.parent and node.val > node.parent.val:
                    node.parent.right = new_node
                elif node.parent and node.val <= node.parent.val:
                    node.parent.left = new_node
        del node
        self.rebalance(new_node)


    def rebalance(self, cell):
        while cell:
            update_height(cell)
            update_gamma(cell)
            if height(cell.right) - height(cell.left) >= 2:
                if height(cell.right.left) > height(cell.right.right):
                    cell.right.rotate_right()
                cell.rotate_left()

            elif height(cell.left) - height(cell.right) >= 2:
                if height(cell.left.right) > height(cell.left.left):
                    cell.left.rotate_left()
                cell.rotate_right()
            if cell.parent is None:
                self.root = cell
            cell = cell.parent

class Cell():

    def __repr__(self):
        return str(self.val)

    def __init__(self, val):
        self.val = val
        self.parent = None
        self.left = None
        self.right = None
        self.gamma = 1
        self.height = 0
        self.occurrences = 1

    def rotate_left(self):
        self.right.parent = self.parent
        if self.parent:
            if self.val < self.parent.val:
                self.parent.left = self.right
            else:
                self.parent.right = self.right
        self.parent = self.right
        self.right = self.right.left
        if self.right:
            self.right.parent = self
        self.parent.left = self
        update_gamma(self)
        update_height(self)

    def rotate_right(self):
        self.left.parent = self.parent
        if self.parent:
            if self.val < self.parent.val:
                self.parent.left = self.left
            else:
                self.parent.right = self.left
        self.parent = self.left
        self.left = self.left.right
        if self.left:
            self.left.parent = self
        self.parent.right = self
        update_gamma(self)
        update_height(self)

def update_gamma(cell):
    if not cell:
        return
    cell.gamma = gamma(cell.left) + gamma(cell.right) + 1

def gamma(cell):
    return 0 if not cell else cell.gamma

def update_height(cell):
    if not cell:
        return
    cell.height = max(height(cell.left), height(cell.right)) + 1

def height(cell):
    return - 1 if not cell else cell.height


def main():

    root = Cell(randint(0,1000))
    print(f"Root: {root}\n---\n")
    avl = AVL(root)
    for _ in range(100000):
        cell = Cell(randint(0,1000000))
        avl.add(cell)

    while True:
        instr = input('''What would you like to do? (I)nsert number, (D)elete number,
(P)rint tree, Find (L)owest, Find (H)ighest, Show (R)oot, Show (N)umber of unique
nodes, or (Q)uit?\n> ''')
        if instr == 'I' or instr == 'i':
            try:
                num = input("What number would you like to insert?\n> ")
                num = Cell(int(num))
                avl.add(num)
            except:
                print("Numbers must be integers.\n---\n")
        elif instr == 'D' or instr == 'd':
            try:
                delete = int(input("What number would you like to delete?\n> "))
                avl.remove(delete)
            except:
                print("Numbers must be integers.")
        elif instr == 'L' or instr == 'l':
            print(avl.lowest(), '\n---\n')
        elif instr == 'H' or instr == 'h':
            print(avl.highest(), '\n---\n')
        elif instr == 'P' or instr == 'p':
            # tab = 2 ** avl.root.height
            # mod = 1
            for row in avl.printout():
                # print(' ' * (tab - mod), row)
                print(row)
                # mod *= 2
            print("\n---\n")
        elif instr == 'Q' or instr == 'q':
            return
        elif instr == 'R' or instr == 'r':
            print(avl.root)
        elif instr == "N" or instr == 'n':
            total = 0
            for row in avl.printout():
                total += sum(1 for node in row if node)
            print(total)
        else:
            try:
                instr = Cell(int(instr))
                avl.add(instr)
            except:
                print("Please make a valid selection.\n")

main()
