#include<iostream>
using namespace std;

class player
{
public:
	string name;
	int job;
	int HP;
	int damage;
	int level;
	int exp;
	int money;
	int MP;
	int deffense;
};

int main()
{
	cout<<"===============================================\n";
	cout<<"===================怪奇世界====================\n";
	cout<<"===============================================\n";
	cout<<"===============================================\n";
	cout << "1.开始游戏=====================================\n2.开发者名单====================================\n3.游戏规则=====================================\n3.成就=======================================\n";
	int choice;
	player you,player1, player2, player3;
	cin>>choice;
	while (1)
	{
		switch (choice)
		{
		case 1:
			cout << "欢迎来到怪奇世界";
			cout << "请输入你的名字：";
			cin >> you.name;
			cout << "请选择你的职业：1.商人 2.战士 3.法师" << endl;
            cin >> you.job;
			break;
		case 2:
			cout << "开发者名单：\n杨昊冕\n颜煜\n闫旭\n杨堃旺";
			break;
		case 3:
			cout << "灰雾之上，百层成神\n游戏规则：1.不要让生命值下降为0以下\n2.杀死非凡生物，提升等级，向上晋升，每十级可提升一次序列，序列从9到0，序列0即为神明\n3.在本游戏中，你会获得各种各样的塔罗牌，它们能给予你不同的力量。职业介绍：\n1.商人：有初始资金，买卖高手，生命值低，攻击力低，魔法值高，防御力高\n战士：生命值高，攻击力高\n法师：生命值低，攻击力低，善用魔法";
			break;
		default:
			cout << "输入错误，请重新输入";
		    continue;
		}
		break;

	}
	
}    