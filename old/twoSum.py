class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        htable = {}

        for i in range(len(nums)):
            htable[nums[i]] = i
        
        for i in range(len(nums)):
            complement = target - nums[i]
            if complement in htable and htable[complement] != i:
                return [i, htable[complement]]
        
        return []

    def twoSumBrute(self, nums: List[int], target: int) -> List[int]:
        for i in range(len(nums)):
            for j in range(i+1, len(nums)):
                if nums[i] + nums[j] == target:        
                    return [i, j]