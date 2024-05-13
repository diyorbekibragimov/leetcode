class Solution(object):
    def matrixScore(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        for i in range(len(grid)):
            if grid[i][0] == 0:
                for j in range(len(grid[i])):
                    if grid[i][j] == 0:
                        grid[i][j] = 1
                    else:
                        grid[i][j] = 0

        for i in range(1, len(grid[0])):
            count_0 = 0
            count_1 = 0
            for j in range(len(grid)):
                if grid[j][i] == 0:
                    count_0 += 1
                else:
                    count_1 += 1

            if count_0 > count_1:
                for j in range(len(grid)):
                    if grid[j][i] == 0:
                        grid[j][i] = 1
                    else:
                        grid[j][i] = 0
        result = 0
        for i in range(len(grid)):
            row_num = 0
            for j in range(len(grid[i])):
                number = 0
                if grid[i][j] == 1:
                    number = 1 << (len(grid[i]) - j - 1)
                row_num |= number
            result += row_num
        return result
