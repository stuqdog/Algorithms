'''Generate a random maze via a DFS to generate successful route, and then
BFS to fill in remaining nodes.'''

from random import randint
import numpy as np
from collections import deque

def generate_layout(n):
    '''Returns nxn 2D array'''
    layout = [[''] * n for x in range(n)]
    layout[0][0] = 'X'
    return layout

def DFS(layout, size):
    '''Makes a path from position (0, 0) to a point on one of the far walls.'''
    parent = {(0, 0): None} # Key = position. Val = previous position.

    def DFS_recur(x, y):
        neighbors = [(1, 0), (-1, 0), (0, 1), (0, -1)]
        np.random.shuffle(neighbors)
        for i in range(4):
            nx, ny = neighbors[i]
            if x + nx == size - 1 or y + ny == size - 1:
                parent[(x+nx, y+ny)] = (x, y)
                return (x+nx, y+ny)
            elif x + nx in range(size) and y + ny in range(size) and (
                              (x+nx, y+ny) not in parent):
                parent[(x+nx, y+ny)] = (x, y)
                end_check = DFS_recur(x+nx, y+ny)
                if end_check:
                    return end_check

    return (DFS_recur(0, 0), parent)


def BFS(layout, size):
    '''Takes the layout after DFS has made a path, and marks remaining nodes
    as either walls or paths. This doesn't need to be done via BFS, but is done
    so as a personal exercise.'''
    neighbors = [(1, 0), (-1, 0), (0, 1), (0, -1)]
    steps = 0
    prev = set()
    curr = deque([(0, 0)])
    while curr:
        x, y = curr.popleft()
        for dx, dy in neighbors:
            new_x, new_y = x + dx, y + dy
            if (new_x, new_y) not in prev and (
                        new_x in range(size) and new_y in range(size)):
                prev.add((new_x, new_y))
                curr.append((new_x, new_y))
                if not layout[new_y][new_x]:
                    wall = randint(0, 3) # change range to change wall frequency
                    layout[new_y][new_x] = '#' if wall else '.'


def main():
    size = 40
    layout = generate_layout(size)
    path_pos, parent = DFS(layout, size) # parent tracks parent-child relations
    while parent[path_pos]:              # between nodes on the DFS path.
        x, y = path_pos
        layout[y][x] = 'X'
        path_pos = parent[path_pos]
    BFS(layout, size)
    for row in layout:
        print(row)

if __name__ == "__main__":
    main()
