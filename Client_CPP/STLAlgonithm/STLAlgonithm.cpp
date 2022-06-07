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



	return 0;
}