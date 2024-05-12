class Solution(object):
    def largestLocal(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: List[List[int]]
        """
        answer = list()
        max_val = 0

        for x in range(len(grid) - 2):
            arr = list()
            for y in range(len(grid) - 2):
                for i in range(3):
                    for j in range(3):
                        if (grid[x+i][y+j] > max_val):
                            max_val = grid[x+i][y+j]
                arr.append(max_val)
                max_val = 0
            answer.append(arr)

        return answer