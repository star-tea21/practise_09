//18 вариант
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
using namespace std;

//1
enum platform {
	PC,
	mobile,
	gamepad
};
struct game_type {
	char game[40]; //наименование игры
	platform platf; //игровая платформа
	double cost; //стоимость подписки
	double audi; //аудитория
	char type[20]; //тип игры
	int rating; //рейтинг игры для практики 10, изначально рейтинг равен нулю

};
struct game { //структура игры 
	game_type descript;
	char dev[20]; //разработчик
};

// шаблоны для дальнейших функций практика 9
int find_strategy(game* array_output, game* array_input, int size);
//int print_strategy(game* pc_strategy, int count);
int find_avia(game* array_output, game* array_input, int size);
//int print_avia(game* avia_sims, int count);
int game_info(game* gamers, int index);
void bubble_sort(game* avia_sims, int avia_size);
void max_cost(game* games, int games_size);
void update(game* games, int games_size, const char* old_name, const char* new_name);
void filter_and_print(game* source, game* dest, int size, int (*filter)(game*, game*, int), const char* message);

// шаблоны функций для работы с файлами (практика 10)
void write_bin(const char* filename, game* games, int size);
void read_bin(const char* filename, game* games, int size);
void  ratings(const char* filename, game* games, int size);

//2
int main() {
	int game_size = 20;
	struct game gamers[20];
	struct game avia_sims[20];
	struct game pc_strategy[20];
	gamers[0] = { {"Baldurs Gate 3", PC, 2500, 15000000, "RPG", 0}, "Lorian" };
	gamers[1] = { {"Age of Empires 4", PC, 2500, 8000000, "strategy",0}, "Lorian" };
	gamers[2] = { {"Witcher 3", PC, 1500, 30000000, "RPG", 0}, "CDPR" };
	gamers[3] = { {"Cyberpunk 2077", PC, 2000, 25000000, "RPG", 0}, "CDPR" };
	gamers[4] = { {"Starcraft 2", PC, 1200, 10000000, "strategy", 0}, "Blizzard" };
	gamers[5] = { {"Warcraft 3", PC, 900, 12000000, "strategy", 0}, "Blizzard" };
	gamers[6] = { {"Forza Horizon 5", gamepad, 3000, 15000000, "racing", 0}, "Playground" };
	gamers[7] = { {"Need for Speed Unbound", gamepad, 2800, 8000000, "racing", 0}, "Playground" };
	gamers[8] = { {"Microsoft Flight Simulator", mobile, 4000, 5000000, "aviator", 0}, "Asobo" };
	gamers[9] = { {"IL-2 Sturmovik", PC, 1800, 2000000, "aviator", 0}, "Asobo" };
	gamers[10] = { {"Outlast 2", PC, 800, 6000000, "horror", 0}, "RedBarrels" };
	gamers[11] = { {"Resident Evil Village", gamepad, 2500, 10000000, "horror", 0}, "RedBarrels" };
	gamers[12] = { {"The Room", mobile, 400, 20000000, "quest", 0}, "Fireproof" };
	gamers[13] = { {"Machinika Museum", mobile, 350, 5000000, "quest", 0}, "Fireproof" };
	gamers[14] = { {"Genshin Impact", mobile, 0, 60000000, "RPG", 0}, "Hoyoverse" };
	gamers[15] = { {"Honkai Star Rail", mobile, 0, 40000000, "RPG", 0}, "Hoyoverse" };
	gamers[16] = { {"Mario Kart 8", gamepad, 3500, 25000000, "racing", 0}, "Nintendo" };
	gamers[17] = { {"Zelda Tears of Kingdom", gamepad, 4000, 20000000, "RPG", 0}, "Nintendo" };
	gamers[18] = { {"Amnesia Rebirth", PC, 700, 4000000, "horror", 0}, "Frictional" };
	gamers[19] = { {"Soma", PC, 600, 3500000, "horror", 0}, "Frictional" };

	//загрузка рейтингов из текстового файла (практика 10, задание 1)
	ratings("C:/Users/palee/Desktop/change.txt", gamers, game_size);

	int index = 4;
	game_info(gamers, index);

	int found_1 = find_avia(gamers, avia_sims, 20);
	//print_avia(avia_sims, found_1);

	max_cost(gamers, 20);

	//int found_2 = find_strategy(gamers, pc_strategy, 20);
	//print_strategy(pc_strategy, found_2);

	filter_and_print(gamers, avia_sims, 20, find_avia, "Авиасимуляторы с аудиторией от 1 млн");

	if (found_1 > 0) {
		bubble_sort(avia_sims, found_1);
	}

	filter_and_print(gamers, pc_strategy, 20, find_strategy, "Стратегии для PC");

	// запись в бинарный файл (практика 10, задание 2)
	write_bin("C:/Users/palee/Desktop/games.bin.txt", gamers, game_size);

	// чтение из бинарного файла в новый массив
	game gamers_file[20];
	read_bin("C:/Users/palee/Desktop/games.bin.txt", gamers_file, game_size);
	cout << "\n" << "чтение первая игра): " << gamers_file[0].descript.game;
	cout << ", рейтинг: " << gamers_file[0].descript.rating << "\n";

	//fstream out("change1.txt", ios::binary | ios::out);
	//for (int i = 0; i < game_size; i++) {
	//	out.write((char*)&gamers[i], sizeof(gamers[i]));
	//}
	//out.close();

	update(gamers, 20, "Zelda Tears of Kingdom", "The Legend of Zelda");
	return 0;
}

//3 переписываем из одного массива в массив с авиасимуляторами
int find_avia(game* array_input, game* array_output, int size) { //массив, из которого берём, затем тот, в который помещаем, и размер исходного
	int count = 0;
	for (int i = 0; i < size; i++) {
		if (strcmp(array_input[i].descript.type, "aviator") == 0 && array_input[i].descript.audi >= 1000000) {
			array_output[count] = array_input[i]; // копируем в новый массив
			count++;
		}
	}
	return count;
}
//int print_avia(game* avia_sims, int count) {
//	cout << "\n";
//	cout << "Авиасимуляторы с аудиторией от 1 млн:\n";
//	for (int i = 0; i < count; i++) {
//		cout << avia_sims[i].descript.game << ", аудитория: " << (int)avia_sims[i].descript.audi << "\n";
//	}
//	return 0;
//}

//4 сортировка массива по платформам (пузырьком)
void bubble_sort(game* avia_sims, int avia_size) {
	for (int x = 0; x < avia_size - 1; x++) {
		for (int y = avia_size - 1; y > x; y--) {
			if (avia_sims[y - 1].descript.platf > avia_sims[y].descript.platf) {
				game z = avia_sims[y - 1];
				avia_sims[y - 1] = avia_sims[y];
				avia_sims[y] = z;
			}
		}
	}
	cout << "\n" << "отсортированный массив: " << "\n";
	for (int z = 0; z < avia_size; z++) {
		cout << z + 1 << ". " << avia_sims[z].descript.game << " (платформа: ";
		switch (avia_sims[z].descript.platf) {
		case PC: cout << "PC"; break;
		case mobile: cout << "Mobile"; break;
		case gamepad: cout << "Gamepad"; break;
		}
		cout << ")\n";
	}
}

//5 функция для вывода информации по конкретной игре
int game_info(game* gamers, int index) {
	cout << "информация об игре:" << "\n";
	cout << "название: " << gamers[index].descript.game << "\n";
	cout << "платформа: ";
	switch (gamers[index].descript.platf) {
	case PC: cout << "PC"; break;
	case mobile: cout << "Mobile"; break;
	case gamepad: cout << "Gamepad"; break;
	}
	cout << "\n";
	cout << "цена: " << gamers[index].descript.cost << "\n";
	cout << "аудитория: " << (int)gamers[index].descript.audi << "\n";
	cout << "жанр: " << gamers[index].descript.type << "\n";
	cout << "разработчик: " << gamers[index].dev << "\n";
	cout << "рейтинг: " << gamers[index].descript.rating << "\n";
	return 0;
}

//6 нахождение трёх игр с максимальной ценой
void max_cost(game* games, int games_size) { //исходный массив, размер исходного массива
	int i_max_c1 = -1, i_max_c2 = -1, i_max_c3 = -1; //индексы трёх самых больших цен
	double max_c1 = -1, max_c2 = -1, max_c3 = -1; //три самые большие цены
	for (int i = 0; i < games_size; i++) {
		if (games[i].descript.cost > max_c1) {
			max_c1 = games[i].descript.cost;
			i_max_c1 = i;
		}
	}
	for (int i = 0; i < games_size; i++) {
		if (i != i_max_c1 && games[i].descript.cost > max_c2) {
			max_c2 = games[i].descript.cost;
			i_max_c2 = i;
		}
	}
	for (int i = 0; i < games_size; i++) {
		if (i != i_max_c1 && i != i_max_c2 && games[i].descript.cost > max_c3) {
			max_c3 = games[i].descript.cost;
			i_max_c3 = i;
		}
	}
	cout << "\n" << "3 самых дорогих игры:\n";
	if (i_max_c1 != -1) {
		cout << "1. " << games[i_max_c1].descript.game << " " << games[i_max_c1].descript.cost << "\n";
	}
	if (i_max_c2 != -1) {
		cout << "2. " << games[i_max_c2].descript.game << " " << games[i_max_c2].descript.cost << "\n";
	}
	if (i_max_c3 != -1) {
		cout << "3. " << games[i_max_c3].descript.game << " " << games[i_max_c3].descript.cost << "\n";
	}
}

//7 функция изменения названия игры
void update(game* games, int games_size, const char* old_name, const char* new_name) {
	for (int i = 0; i < games_size; i++) {
		if (strcmp(old_name, games[i].descript.game) == 0) {
			strcpy_s(games[i].descript.game, sizeof(games[i].descript.game), new_name);
			cout << "\n" << "игра " << old_name << " переименована в " << new_name << "\n";
			return;
		}
	}
	cout << "игра " << old_name << " не найдена";
}

//8
int find_strategy(game* array_input, game* array_output, int size) { //массив, из которого берём, затем тот, в который помещаем, и размер исходного
	int count = 0;
	for (int i = 0; i < size; i++) {
		if (strcmp(array_input[i].descript.type, "strategy") == 0 && array_input[i].descript.platf == 0) {
			array_output[count] = array_input[i]; // копируем в новый массив
			count++;
		}
	}
	return count;
}
//int print_strategy(game* pc_strategy, int count) {
//	cout << "\n";
//	cout << "Стратегии для PC:\n";
//	for (int i = 0; i < count; i++) {
//		cout << pc_strategy[i].descript.game << "\n";
//	}
//	return 0;
//}

// 9
void filter_and_print(game* array_input, game* array_output, int size, int (*filter)(game*, game*, int), const char* message) {
	int count = filter(array_input, array_output, size);
	if (count > 0) {
		cout << "\n" << message << ":\n";
		for (int i = 0; i < count; i++) {
			cout << i + 1 << ". " << array_output[i].descript.game << "\n";
		}
	}
	else {
		cout << "\n" << message << " не найдены\n";
	}
}

//практика 10. запись
void write_bin(const char* filename, game* games, int size) {
	ofstream out(filename, ios::binary | ios::out);
	if (!out) {
		cout << "ошибка открытия файла для записи!\n";
		return;
	}
	for (int i = 0; i < size; i++) {
		out.write((char*)&games[i], sizeof(games[i]));
	}
	out.close();
	cout << "массив записан в бинарный файл " << filename << "\n";
}

// чтение
void read_bin(const char* filename, game* games, int size) {
	ifstream in(filename, ios::binary | ios::in);
	if (!in) {
		cout << "ошибка открытия файла\n";
		return;
	}
	for (int i = 0; i < size; i++) {
		in.read((char*)&games[i], sizeof(games[i]));
	}
	in.close();
	cout << "массив прочитан из бинарного файла " << filename << "\n";
}

// загрузка рейтингов  (задание 1)
void ratings(const char* filename, game* games, int size) {
	ifstream fin(filename);
	if (!fin) {
		cout << "текстовый файл " << filename << " не найден.\n";
		return;
	}
	string line;
	int loaded = 0;
	while (getline(fin, line)) {
		if (line.empty()) continue;
		size_t last_space = line.rfind(' ');
		if (last_space == string::npos) continue;
		string name = line.substr(0, last_space);
		string rating_str = line.substr(last_space + 1);
		int rating = stoi(rating_str);
		for (int i = 0; i < size; i++) {
			if (strcmp(games[i].descript.game, name.c_str()) == 0) {
				games[i].descript.rating = rating;
				loaded++;
				break;
			}
		}
	}
	fin.close();
	cout << "загружено рейтингов: " << loaded << "\n";
	cout << "\n";
}
