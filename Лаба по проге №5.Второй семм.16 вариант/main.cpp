#include "headerinc.h"
#include "tree_node.h"
#include "Tree.h"
#include "checkfile.h"
#include "stringrandom.h"
#include <Windows.h>

Tree <int>* Tree_;
bool tree_initFlag = false;

void print_menu() {
	cout << "\n---------------Menu---------------\n";
	cout << "1.Сгенерировать рандомное дерево\n";
	cout << "2.Добавить узел по ключу\n";
	cout << "3.Добавить узел по индексу\n";
	cout << "4.Получить ключ по индексу\n";
	cout << "5.Получить индекс по ключу\n";
	cout << "6.Найти ключ\n";
	cout << "7.Вывести дерево\n";
	cout << "8.Очистить дерево\n";
	cout << "9.Удалить узел\n";
	cout << "10.Корень дерева\n";
	cout << "11.Изменить ключ \n";
	cout << "12.Изменить ключ по индексу \n";
	cout << "13.Вывести дерево в файл\n";
	cout << "14.Считать дерево из файла\n";
	cout << "15.Расчитать среднее геометрическое \n";
}

void SW_OP() {
	int operation, index, RWriteFlag, AddingKey, Key;
	bool flag = false;
	double AG;
	string Filename;
	ofstream Output;
	print_menu();
	do
	{
		cout << "Введите номер действия\n";
		cin >> operation;
		switch (operation)
		{
		case 1: {
			uint16_t size;
			if (tree_initFlag == false) {
				while (true)
				{
					cout << "Введите количество узлов\n";
					cin >> size;
					if (cin) break;
				}
				Tree_ = new Tree <int>(size);
				Tree_->OutputTree(Tree_->_Root(), 0);
				tree_initFlag = true;
			}
			else {
				cout << "Дерево уже проинициализировано\n";
			}
			flag = false;;
			break;
		}
		case 2:
			if (tree_initFlag == true) {
				cout << "Введите ключ к которому будет добавляться\n";
				cin >> Key;
				cout << "Введите добавляемый ключ\n";
				cin >> AddingKey;
				Tree_->addElement(Key, AddingKey);
				Tree_->OutputTree(Tree_->_Root(), 0);
			}
			else {
				cout << "Дерево пустое\n";
				cout << "Введите добавляемый ключ\n";
				cin >> AddingKey;
				Tree_ = new Tree<int>(AddingKey);
				Tree_->OutputTree(Tree_->_Root(), 0);
				tree_initFlag = true;
			}
			flag = false;;
			break;
		case 3:
			if (tree_initFlag == true) {
				cout << "Введите индекс к которому будет добавляться\n";
				cin >> index;
				cout << "Введите добавляемый ключ\n";
				cin >> AddingKey;
				Tree_->addIndex(AddingKey, index);
				Tree_->OutputTree(Tree_->_Root(), 0);
			}
			else {
				cout << "Дерево пустое\n";
				cout << "Введите добавляемый ключ\n";
				cin >> AddingKey;
				Tree_ = new Tree<int>(AddingKey);
				Tree_->OutputTree(Tree_->_Root(), 0);
				tree_initFlag = true;
			}
			flag = false;
			break;
		case 4:
			cout << "Введите индекс\n";
			cin >> index;
			cout << "Результат: " << Tree_->GetKey(index) << '(' << index << ')';
			flag = false;
			break;
		case 5:
			cout << "Введите ключ\n";
			cin >> Key;
			cout << "Результат: " << Tree_->GetIndex(Key) << ' ' << Key << endl;
			flag = false;
			break;
		case 6:
			cout << "Введите ключ\n";
			cin >> Key;
			if (Tree_->FindKey(Key)) cout << "Ключ есть в дереве\n";
			else cout << "Ключа нету в дереве\n";
			flag = false;
			break;
		case 7:
			Tree_->OutputTree(Tree_->_Root(), 0);
			cout << endl;
			flag = false;
			break;
		case 8:
			Tree_->ClearTree();
			Tree_->OutputTree(Tree_->_Root(), 0);
			cout << endl;
 			flag = false;
			break;
		case 9:
			cout << "Введите ключ\n";
			cin >> Key;
			Tree_->DeleteElement(Key);
			Tree_->OutputTree(Tree_->_Root(), 0);
			cout << endl;
			flag = false;
			break;
		case 10:
			if (Tree_->_Root() != NULL)
				cout << "Корень: " << Tree_->_Root()->KeyField << '(' << Tree_->_Root()->index << ')' << endl;
			else
				cout << "Дерево пустое\n";
			flag = false;
			break;
		case 11: 
			cout << "Введите ключ к который будет изменяться\n";
			cin >> Key;
			cout << "Введите изменяемый ключ\n";
			cin >> AddingKey;
			Tree_->SetKey(Key, AddingKey);
			Tree_->OutputTree(Tree_->_Root(), 0);
			flag = false; 
			break;
		case 12:
			cout << "Введите индекс\n";
			cin >> index;
			cout << "Введите изменяемый ключ\n";
			cin >> AddingKey;
			Tree_->SetKeyIndex(index, AddingKey);
			Tree_->OutputTree(Tree_->_Root(), 0);
			flag = false;
			break;
		case 13:
			cout << "Введите название файла \n";
			do {
				getline(cin, Filename);
			} while (Filename.empty());
			Filename = check_mask(Filename);
			if (check_empty(Filename)) {
				Output.open(Filename, ios::out);
				Tree_->OutputTreeInFile(Tree_->_Root(), Output);
				cout << "Записано в файл:" << Filename;
			}
			else {
				cout << "Файл не пуст.Хотите перезаписать? 1.YES 2.NO\n";
				do {
					cin >> RWriteFlag;
					if (RWriteFlag == 2 || RWriteFlag == 1) break;
					cout << "Повторите ввод\n";
				} while (true);
				if (RWriteFlag == 1) {
					Output.open(Filename, ios::out);
					Tree_->OutputTreeInFile(Tree_->_Root(), Output);
					cout << "Записано в файл:" << Filename;
				}
			}
			break;
		case 14:
			uint16_t size;
			if (tree_initFlag == false) {
				cout << "Введите название файла \n";
				do {
					getline(cin, Filename);
				} while (Filename.empty());
				Filename = check_mask(Filename);
				if (!check_empty(Filename)) {
					Tree_ = new Tree <int>(Filename, 0);
					Tree_->OutputTree(Tree_->_Root(), 0);
					tree_initFlag = true;
				}
				else {
					cout << "Файл пуст или не найден\n";
				}
			}
			else {
				cout << "Дерево уже проинициализировано\n";
			}
			flag = false;
			break;
		case 15:
			AG = Tree_->GetGeometricAverage();
			if (AG != 0.0) cout << "Среднее геометрическое этого дерева: " << fixed <<setprecision(2) << AG << '\n';
			else cout << "Дерево пусто\n";
			flag = false;
			break;
		default:
			cout << "Ошибка ввода. Попробуйте ещё.\n";
			flag = true;
			break;
		}
	} while (flag);
}

//TODO:Проверить выполнение IsEmpty()

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int exit = 0;
	do {
		SW_OP();
		while (true)
		{
			cout << "Хотите продолжать: 1.YES 2.NO \n";
			cin >> exit;
			if (exit == 1 || exit == 2) break;
			cout << "Ошибка. Повторите ввод\n";
		}
	} while (exit!=2);
	return 0;
}