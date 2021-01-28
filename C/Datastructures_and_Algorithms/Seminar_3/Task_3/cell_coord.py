# nlantau, 2020-12-22


class Coordinate:
    def __init__(self, row, col):
        self.row = row
        self.col = col


class Neighbor:
    def __init__(self, row, col, x=8, y=8):
        self.coords = Coordinate(row, col)
        self.row_valid = False
        self.col_valid = False
        self.max_x = x
        self.max_y = y
        self.is_valid = False
        self.check_is_valid()

    def check_is_valid(self):
        self.check_validity()
        if self.row_valid and self.col_valid:
            self.is_valid = True
        else:
            self.is_valid = False

    def check_validity(self):
        if self.coords.row < 0 or self.coords.row > self.max_x:
            self.row_valid = False
        elif self.coords.row >= 0:
            self.row_valid = True
        if self.coords.col < 0 or self.coords.col > self.max_y:
            self.col_valid = False
        elif self.coords.col >= 0:
            self.col_valid = True


class Cell:

    """The Cell has its position and a list of all is
    valid neighbors in all eight directions

    The Cell stores its coordinates as a Coordinate(row, col)

    """

    def __init__(self, row, col, max_x=4, max_y=4):
        """Alteration of max_x and max_y will affect
        the neighbors max_x and max_y as well.
        This is good.
        """

        self.coords = Coordinate(row, col)
        self.valid_neighbors = []
        self.max_x = max_x
        self.max_y = max_y
        self.check_neighbors()

    def check_neighbors(self):
        row = self.coords.row
        col = self.coords.col
        directions = [
            (row, col - 1, "L"),
            (row, col + 1, "R"),
            (row + 1, col, "D"),
            (row - 1, col, "U"),
            (row - 1, col - 1, "UL"),
            (row - 1, col + 1, "UR"),
            (row + 1, col - 1, "DL"),
            (row + 1, col + 1, "DR"),
        ]
        for row, col, dir in directions:
            self.check_all_neighbors(row, col, dir)

    def check_all_neighbors(self, c_row, c_col, pos):
        valid_neighbors = list()
        valid_neighbors.append((self.coords.row, self.coords.col))
        row = c_row
        col = c_col

        n_mx = self.max_x - 1
        n_my = self.max_y - 1
        curr_neighbor = Neighbor(row, col, x=n_mx, y=n_my)
        perm_neighbors = list()

        if curr_neighbor.is_valid:
            valid_neighbors.append((row, col))
            while True:
                if self.check_row_col(row, col):
                    break
                row, col = self.alter_row_col(row, col, pos)
                next_neighbor = Neighbor(row, col, x=n_mx, y=n_my)
                if next_neighbor.is_valid:
                    valid_neighbors.append((row, col))
                else:
                    break
            for i, el in enumerate(valid_neighbors):
                perm_neighbors.append(valid_neighbors[0 : i + 1])
                perm_neighbors.append(list(reversed(valid_neighbors[0 : i + 1])))
            self.valid_neighbors.append(perm_neighbors)

    def alter_row_col(self, row, col, pos) -> int and int:
        if pos == "L":
            col -= 1
        elif pos == "R":
            col += 1
        elif pos == "UL":
            row -= 1
            col -= 1
        elif pos == "U":
            row -= 1
        elif pos == "UR":
            row -= 1
            col += 1
        elif pos == "DL":
            row += 1
            col -= 1
        elif pos == "D":
            row += 1
        elif pos == "DR":
            row += 1
            col += 1
        return row, col

    def check_row_col(self, row, col):
        if row > self.max_x or row < 0:
            return True
        elif col > self.max_y or col < 0:
            return True
        else:
            return False


if __name__ == "__main__":
    tc = Cell(2, 1, max_x=4, max_y=4)
    print(f"Cell position: ({tc.coords.row},{tc.coords.col})")
    print(*tc.valid_neighbors, sep="\n")
    """
    tc = Cell(1, 0, max_x=3, max_y=3)
    print(f"Cell position: ({tc.coords.row},{tc.coords.col})")
    print(*tc.valid_neighbors, sep="\n")
    """
