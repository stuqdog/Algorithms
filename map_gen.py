'''Generate a random maze via a DFS to generate successful route, and then
BFS to fill in remaining nodes.'''

from random import randint

def DFS(x, y, layout, size):
    '''Makes a path from position (0, 0) to a point on one of the far walls.'''
    neighbors = [(1, 0), (-1, 0), (0, 1), (0, -1)]
    for _ in range(4):
        i = randint(0, len(neighbors) - 1)
        nx, ny = neighbors[i]
        if x + nx == size - 1 or y + ny == size - 1:
            parent[(x+nx, y+ny)] = (x, y)
            return (x+nx, y+ny)
        elif x + nx in range(size) and y + ny in range(size) and (
                          (x+nx, y+ny) not in parent):
            parent[(x+nx, y+ny)] = (x, y)
            end_check = DFS(x+nx, y+ny, layout, size)
            if end_check:
                return end_check
        del neighbors[i]
    return

def generate_layout(n):
    '''Returns nxn 2D array'''
    layout = [[''] * size for x in range(n)]
    layout[0][0] = 'X'
    return layout

def BFS(layout, size):
    '''Takes the layout after DFS has made a path, and marks remaining nodes
    as either walls or paths.'''
    neighbors = [(1, 0), (-1, 0), (0, 1), (0, -1)]
    steps = 0
    prev = {}
    curr = [(0, 0)]

    while curr:
        steps += 1
        search = []
        for pos in curr:
            x, y = pos
            for neighbor in neighbors:
                dx, dy = neighbor
                new_x, new_y = x + dx, y + dy
                if (new_x, new_y) not in prev and (
                            new_x in range(size) and new_y in range(size)):
                    wall = randint(0, 3) # change range to make walls more/less likely
                    prev[(new_x, new_y)] = steps
                    search.append((new_x, new_y))
                    if not layout[new_y][new_x]:
                        layout[new_y][new_x] = '#' if wall else '.'
        curr = search

def main():
    layout = generate_layout(size)
    path = DFS(0, 0, layout, size)
    while parent[path]:
        x, y = path
        layout[y][x] = 'X'
        path = parent[path]
    BFS(layout, size)
    for row in layout:
        print(row)


if __name__ == "__main__":
    size = 15
    parent = {(0, 0): None}
    main()
