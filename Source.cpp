#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

class Trenager {
	char*** phrase;
	int size;
public:	
	void list_of_phrases();	//��������� ����� �� �����
	void training();	//�������� �������� ����������		
};


void Trenager::list_of_phrases() {
  

    fs::path current_path = fs::current_path();//��������� ����������

    int cntr_dir;//������� ������ � ����������
	string filename[50];//������ ���������� ����� ������ � ������� txt
	char buffer[80];
	ifstream in;

	while (true) {

		cntr_dir = 1;

		for (auto& p : fs::directory_iterator(current_path)) {

			if (p.path().extension().string() == ".txt") {

				filename[cntr_dir - 1] = p.path().filename().string();
				cout << cntr_dir << " - " << p.path().stem().string() << endl;//������� ����� ���� ������ � ���������� � ���������� .txt
				cntr_dir++;

			}
		}

		cout << "\n�������� ����� �����, ������� ������ �������:";
		int choice_file;	cin >> choice_file;

		if (cin.fail()) {

			cin.clear();
			cin.ignore(10, '\n');
			system("cls");
			continue;

		}				
		
		in.open(filename[choice_file - 1]);//�������� �����

		if (!in) {   //��������� ������ �������� �����
			system("cls");

		}
		else break;
	}


	size = 0;

	while (!in.eof()) { //���������� ������� �������

		in.getline(buffer, 80);
		size++;

	}
	in.seekg(0);
	size /= 2;


	phrase = new char** [size + 1]; //������������ ��������� ������ ��� ������ ����
	for (int i = 0; i < size + 1; i++) {
		phrase[i] = new char* [2];
		for (int j = 0; j < 2; j++)
		{
			phrase[i][j] = new char[80];

		}
	}


	while (!in.eof()) //������ � ������
	{
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < 2; j++)
			{
				in.getline(buffer, 80);
				strcpy_s(phrase[i][j], 80, buffer);

			}
		}

	}
	in.close();
	phrase[size][0] = NULL;
	phrase[size][1] = NULL;

	cin.ignore(10, '\n');

	system("cls");
}


void Trenager::training() {

	string answer;
	int fail = 0;

	system("cls");
	for (int i = 0; phrase[i][1]; i++) {

		cout << "������� ����� �� ������ �����:\n";
		cout << phrase[i][1] << " - ";
		getline(cin, answer);


		char TMP[80];
		strcpy_s(TMP, 80, phrase[i][0]);

		
		auto equalization([](auto& str) {

			for (int i = 0; str[i]; i++) {

				str[i] = tolower(str[i]);

			}
			});

		equalization(TMP);
		equalization(answer);
		

		if (TMP == answer) {
			phrase[i][0] = NULL;
			phrase[i][1] = NULL;
			system("cls");

		}
		else {

			if (i > fail) {
				phrase[fail][0] = phrase[i][0];
				phrase[fail][1] = phrase[i][1];

			}
			fail++;

			while (true)
			{
				system("cls");
				cout << "��� ���������� �����:\n";
				cout << phrase[i][1] << " - " << phrase[i][0] << endl;
				cout << "��������� ����: ";
				getline(cin, answer);
				equalization(answer);

				if (TMP == answer) {
					if (i + 1 > fail) {
						phrase[i][0] = NULL;
						phrase[i][1] = NULL;
					}
					system("cls");
					break;

				}

			}
		}

	}
	if (fail) training();

}



int main() {
	setlocale(LC_ALL, "rus");

	Trenager lesson, * Ptr;
	Ptr = &lesson;

	while (true) {

		Ptr->list_of_phrases();
		Ptr->training();

		cout << "����������! �� ��������� ����������!\n\n";

		cout << "������ ������� ������ ����?\n"
			<< "1 - ��\n"
			<< "2 - ���\n";

		int choice_proceed; cin >> choice_proceed;

		if (choice_proceed == 2) break;

		cin.ignore(10, '\n');
		system("cls");
	}	
	

	return 0;
}