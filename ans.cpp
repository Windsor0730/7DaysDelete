#include<vector>
#include<iostream>
#include<queue>

class Solution {
public:
	std::vector<int> GetTopScores(int m, std::vector<int>&scores) {
		std::vector<int> topScores;
		if (m <= 0 || scores.size() == 0) {
			return topScores;
		}

		std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
		for (int i = 0; i < scores.size(); i++) {
			if (minHeap.size() < m) {
				minHeap.push(scores[i]);
			}
			else {
				if (scores[i] > minHeap.top()) {
					minHeap.pop();
					minHeap.push(scores[i]);
				}
			}
		}
		while (!minHeap.empty()) {
			topScores.push_back(minHeap.top());
			minHeap.pop();
		}

		std::sort(topScores.begin(), topScores.end(), std::greater<int>());//结果数组从大到小重排序
		return topScores;
	}

	float MaxEnergyField(std::vector<int>& heights) {
		float l = 0.0, r = heights.size() - 1;
		float ans = 0.0;
		while (l < r) {
			float area = (heights[l]+heights[r]) * (r - l) / 2.0;
			ans = std::max(ans, area);
			if (heights[l] <= heights[r]) {
				++l;
			}
			else {
				--r;
			}
		}
		return ans;
	}

	int MaxTreasureValue(std::vector<int>& treasures) {
		if (treasures.empty()) {
			return 0;
		}
		int size = treasures.size();
		if (size == 1) {
			return treasures[0];
		}
		int first = treasures[0], second = std::max(treasures[0], treasures[1]);
		for (int i = 2; i < size; i++) {
			int temp = second;
			second = std::max(first + treasures[i], second);
			first = temp;
		}
		return second;
	}

	float FindMedianTalentIndex(std::vector<int>& fireAbility, std::vector<int>& iceAbility) {
		int totalLength = fireAbility.size() + iceAbility.size();
		if (totalLength % 2 == 1) {
			return getKthElement(fireAbility, iceAbility, (totalLength + 1) / 2);
		}
		else {
			return (getKthElement(fireAbility, iceAbility, totalLength / 2) + getKthElement(fireAbility, iceAbility, totalLength / 2 + 1)) / 2.0;
		}
	}
	int getKthElement(const std::vector<int>& fireAbility, const std::vector<int>& iceAbility, int k) {
		int m = fireAbility.size();
		int n = iceAbility.size();
		int index1 = 0, index2 = 0;

		while (true) {
			if (index1 == m) {
				return iceAbility[index2 + k - 1];
			}
			if (index2 == n) {
				return fireAbility[index1 + k - 1];
			}
			if (k == 1) {
				return std::min(fireAbility[index1], iceAbility[index2]);
			}

			int newIndex1 = std::min(index1 + k / 2 - 1, m - 1);
			int newIndex2 = std::min(index2 + k / 2 - 1, n - 1);
			int pivot1 = fireAbility[newIndex1];
			int pivot2 = iceAbility[newIndex2];
			if (pivot1 <= pivot2) {
				k -= newIndex1 - index1 + 1;
				index1 = newIndex1 + 1;
			}
			else {
				k -= newIndex2 - index2 + 1;
				index2 = newIndex2 + 1;
			}
		}
	}

};

int main() {
	Solution s = Solution();

	std::vector<int> scores1 = { 5, 8, 4, 3, 1, 6, 7, 2, 9 };
	int m1 = 3;
	std::vector<int> ans1 = { 9, 8, 7 };
	std::cout << (s.GetTopScores(m1, scores1) == ans1 ? "1-1true" : "1-1false") << std::endl;
	std::vector<int> scores2 = { 100, 50, 75, 80, 65 };
	int m2 = 3;
	std::vector<int> ans2 = { 100, 80, 75 };
	std::cout << (s.GetTopScores(m2, scores2) == ans2 ? "1-2true" : "1-2false") << std::endl;

	std::vector<int> heights = { 1, 8, 6, 2, 5, 4, 8, 3, 7 };
	std::cout << (s.MaxEnergyField(heights) == 52.5 ? "2-1true" : "2-1false") << std::endl;

	std::vector<int> treasures1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	std::cout << (s.MaxTreasureValue(treasures1) == 25 ? "3-1true" : "3-2false") << std::endl;
	std::vector<int> treasures2 = { 3, 1, 5, 2, 4 };
	std::cout << (s.MaxTreasureValue(treasures2) == 12 ? "3-2true" : "3-2false") << std::endl;

	std::vector<int> fireAbility1 = { 1, 3, 5, 7, 9 };
	std::vector<int> iceAbility1 = { 2, 4, 6, 8, 10 };
	std::cout << (s.FindMedianTalentIndex(fireAbility1, iceAbility1) == 5.5 ? "4-1true" : "4-1false") << std::endl;
	std::vector<int> fireAbility2 = { 1,3,7,9,11 };
	std::vector<int> iceAbility2 = { 2,4,8,10,12,14 };
	std::cout << (s.FindMedianTalentIndex(fireAbility2, iceAbility2) == 8 ? "4-2true" : "4-2false") << std::endl;

	return 0;

}