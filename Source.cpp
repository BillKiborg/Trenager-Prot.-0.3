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
	void list_of_phrases();	//считывает фразы из файла
	void training();	//содержит алгоритм тренировки		
};


void Trenager::list_of_phrases() {
  

    fs::path current_path = fs::current_path();//получение директории

    int cntr_dir;//счетчик файлов в директории
	string filename[50];//массив содержащий имена файлов в формате txt
	char buffer[80];
	ifstream in;

	while (true) {

		cntr_dir = 1;

		for (auto& p : fs::directory_iterator(current_path)) {

			if (p.path().extension().string() == ".txt") {

				filename[cntr_dir - 1] = p.path().filename().string();
				cout << cntr_dir << " - " << p.path().stem().string() << endl;//выводит имена всех файлов в директории с расширение .txt
				cntr_dir++;

			}
		}

		cout << "\nВыберете номер файла, который хотите открыть:";
		int choice_file;	cin >> choice_file;

		if (cin.fail()) {

			cin.clear();
			cin.ignore(10, '\n');
			system("cls");
			continue;

		}				
		
		in.open(filename[choice_file - 1]);//открытие файла

		if (!in) {   //обработка ошибок открытия файла
			system("cls");

		}
		else break;
	}


	size = 0;

	while (!in.eof()) { //вычесление размера массива

		in.getline(buffer, 80);
		size++;

	}
	in.seekg(0);
	size /= 2;


	phrase = new char** [size + 1]; //динамическое выделение памяти под массив фраз
	for (int i = 0; i < size + 1; i++) {
		phrase[i] = new char* [2];
		for (int j = 0; j < 2; j++)
		{
			phrase[i][j] = new char[80];

		}
	}


	while (!in.eof()) //запись в массив
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

		cout << "Введите фразу на другом языке:\n";
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
				cout << "Вот правильный ответ:\n";
				cout << phrase[i][1] << " - " << phrase[i][0] << endl;
				cout << "Повторите ввод: ";
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

		cout << "Поздравляю! Вы закончили выполнение!\n\n";

		cout << "Хотите открыть другой файл?\n"
			<< "1 - да\n"
			<< "2 - нет\n";

		int choice_proceed; cin >> choice_proceed;

		if (choice_proceed == 2) break;

		cin.ignore(10, '\n');
		system("cls");
	}	
	

	return 0;
}