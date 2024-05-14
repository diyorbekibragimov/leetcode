class Solution(object):
    def helper(self, grid, row, col):
        if (row >= len(grid) or row < 0) \
            or (col >= len(grid[row]) or col < 0) \
            or (grid[row][col] == 0):
            return 0
        else:
            val = grid[row][col]
            grid[row][col] = 0

            max_left = val
            max_right = val
            max_up = val
            max_down = val

            max_left += self.helper(grid, row, col-1) # left
            max_right += self.helper(grid, row, col+1) # right
            max_up += self.helper(grid, row-1, col) # up
            max_down += self.helper(grid, row+1, col) # down
            grid[row][col] = val

            return max(max_left, max_right, max_up, max_down)

    def getMaximumGold(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        global_max = 0
        for row in range(len(grid)):
            for col in range(len(grid[row])):
                local_max = self.helper(grid, row, col)
                if local_max > global_max:
                    global_max = local_max
        return global_max