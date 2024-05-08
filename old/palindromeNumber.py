import math
class Solution:
    def getNumberLength(self, number):
        if number == 0: return 1
        number = abs(number)
        return 1 + math.floor(math.log10(number))

    def getKthDigit(self, number, k):
        number = abs(number)
        return number // 10 ** (k) % 10

    def setKthDigit(self, number, value, k):
        rawNum = number - self.getKthDigit(number, k) * 10 ** (k)
        return rawNum + value * 10 ** (k)
    
    def isPalindrome(self, x: int) -> bool:
        numLen = self.getNumberLength(x)
        newNum = 0
        for i in range(numLen):
            val = self.getKthDigit(x, i)
            if i == 0 and val == 0:
                break
            newNum = self.setKthDigit(newNum, val, numLen-(i+1))
        return newNum == x