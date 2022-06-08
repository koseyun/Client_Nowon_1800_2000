#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Player {
public:
	string nickName;
	int score;

	Player(string nickName, int score) {
		this->nickName = nickName;
		this->score = score;
	}

	bool operator < (Player& player) const {
		return this->score < player.score;
	}

	bool operator <= (Player& player) const {
		return this->score <= player.score;
	}

	bool operator > (Player& player) {
		return this->score > player.score;
	}

	bool operator >= (Player& player) {
		return this->score >= player.score;
	}
};

bool IsABeatB(Player& player1, Player& player2)
{
	return player1 > player2;
}

int main() {
	
	int arr1[10] = { 7, 6, 2, 4, 5, 1, 3, 9, 8, 0 };
	sort(arr1, arr1 + 10);

	for (int i = 0; i < 10; i++)
		cout << arr1[i];

	cout << endl;
	vector<int> vec1;
	for (int i = 9; i >= 0; i--)
		vec1.push_back(i);
	sort(vec1.begin(), vec1.end());
	vector<int>::iterator iter = vec1.begin();
	while (iter != vec1.end())
	{
		cout << *iter;
		iter++;
	}
	
	// string 비교해서 정렬하는 잘못된 예
	vector<pair<string, int>> ranking;

	ranking.push_back(pair<string, int>("Luke", 10));
	ranking.push_back(pair<string, int>("Dina", 20));
	ranking.push_back(pair<string, int>("Julia", 5));

	sort(ranking.begin(), ranking.end());
	for (int i = 0; i < ranking.size(); i++)
		cout << ranking[i].first << " , ";
	cout << endl;

	vector<Player> players;
	players.push_back(Player("Ailey", 45));
	players.push_back(Player("Su", 40));
	players.push_back(Player("Julia", 5));
	players.push_back(Player("Ryu", 35));
	players.push_back(Player("Luke", 10));
	players.push_back(Player("Dina", 20));
	players.push_back(Player("Terry", 15));



	//sort(players.begin(), players.end());

	//partial_sort(players.begin(), players.begin() + 3, players.end());
	//partial_sort(players.begin(), players.begin() + 3, players.end(), greater<>());
	//partial_sort(players.begin(), players.begin() + 3, players.end(), less<>());
	//partial_sort(players.begin(), players.begin() + 3, players.end(), IsABeatB);

	//cout << players[2].nickName << endl;
	//nth_element(players.begin(), players.begin() + 2, players.end(), greater<>());
	//cout << players[2].nickName << endl;

	sort(players.begin(), players.end(), less<>());
	stable_sort(players.begin(), players.end(), less<>());
	vector<int> test;
	test.push_back(1);
	test.push_back(1);
	stable_sort(test.begin(), test.end());

	for (int i = 0; i < players.size(); i++)
		cout << players[i].nickName << ", ";
	cout << endl;

	// 원소들을 누적하는
	// accumulate(시작, 끝, 초기값)
	int acc = accumulate(arr1, arr1 + 10, 0);
	cout << "누적값: " << acc << endl;

	// 부분합, 원소들을 처음부터 끝까지 합하는
	int arr2[10];
	partial_sum(arr1, arr1 + 10, arr2); // 부분합
	partial_sum(arr1 + 1, arr1 + 10, arr2, multiplies<int>()); // 부분곱
	for (int i = 0; i < 10; i++)
	{
		cout << "부분합 : " << arr2[i] << endl;
	}

	int arr3[10];
	adjacent_difference(arr1, arr1 + 10, arr3);
	for (int i = 0; i < 10; i++)
	{
		cout << "차이 : " << arr3[i] << endl;
	}

	int coord1[3] = { 1,5,3 };
	int coord2[3] = { 2,5,4 };
	// 벡터의 내적

	int dotResult = inner_product(coord1, coord1 + 3, coord2, 0);
	cout << dotResult << endl;


	return 0;
}