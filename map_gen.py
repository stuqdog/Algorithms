'''Generate a random maze via a DFS to generate successful route, and then
BFS to fill in remaining nodes.'''

from random import randint

def DFS(x, y):
    neighbors = [(1, 0), (-1, 0), (0, 1), (0, -1)]
    i = randint(0, 3)
    nx, ny = neighbors[i]
    i_change = -1 if randint(0, 1) else 1

    for _ in range(4):
        i = randint(0, len(neighbors) - 1)
        nx, ny = neighbors[i]
        if x+nx == 9 or y+ny == 9:
            parent[(x+nx, y+ny)] = (x, y)
            return (x+nx, y+ny)
        elif x+nx in range(10) and y+ny in range(10) and (
                          (x+nx, y+ny) not in parent):
            parent[(x+nx, y+ny)] = (x, y)
            end_check = DFS(x+nx, y+ny)
            if end_check:
                return end_check
        del neighbors[i]
        # neighbor_size -= 1
    return

def generate_layout(size):
    layout = [[''] * size for x in range(size)]
    layout[0][0] = '.'
    return layout




def BFS():
    neighbors = [(1, 0), (-1, 0), (0, 1), (0, -1)]
    steps = 0
    x = y = 0
    prev = {}

    curr = [(x, y)]
    while curr:
        steps += 1
        expand = []
        for pos in curr:
            cx, cy = pos
            for neighbor in neighbors:
                dx, dy = neighbor
                nx, ny = cx + dx, cy + dy
                if (nx, ny) not in prev and nx in range(10) and ny in range(10):
                    wall = randint(0, 4)
                    prev[(nx, ny)] = steps
                    expand.append((nx, ny))
                    if not layout[ny][nx]:
                        layout[ny][nx] = '#' if wall else '.'
        curr = expand


puzzle_size = 15

layout = [[''] * 10 for x in range(10)]
layout[0][0] = 'X'

parent = {(0, 0): None}
path = DFS(0, 0)
while parent[path]:
    x, y = path
    layout[y][x] = 'X'
    path = parent[path]
BFS()
for row in layout:
    print(row)
