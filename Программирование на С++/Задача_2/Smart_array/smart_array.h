#pragma once

class smart_array
{
public:
	smart_array(int size) :size{ size }, p_arr{ new int[size] {} } {};		//конструктор
	smart_array(smart_array&) = delete;									//конструктора копирования не будет
	smart_array(smart_array&& old_arr) {								//конструктор перемещения
		std::cout << "MOVE\n";
		index = old_arr.index;
		size = old_arr.size;
		delete[] p_arr;
		p_arr = new int[size];
		for (int i{}; i < size; i++)p_arr[i] = old_arr.p_arr[i];
		delete[] old_arr.p_arr;
		old_arr.p_arr = nullptr;
	};

//добавление элемента в конец
	void add_element(const int element) {
		if (index < size) {						//проверяем на конец массива
			p_arr[index] = element;
			index++;
		}
		else {									//если конец то добавляем пять элементов
			int size_tmp = size + 5;
			int* p_tmp{ new int[size_tmp] {} };
			for (int i{}; i < size; i++) {			//копируем наш массив во временный
				p_tmp[i] = p_arr[i];		//Почему пишет переполнение буфера????? не могу понять
			}
			delete[] p_arr;					//удаляем старый массив
			p_arr = nullptr;
			p_arr = p_tmp;					//копируем указатель временного массива. при выходе из блока переменная на стеке уничтожится
			size = size_tmp;								//а указатель на увеличенный массив сохранен в поле класса
			p_arr[index] = element;			//наконец то копируем новый элемент
			index++;			//увеличиваем индекс
		}
	};
//возврат элемента по индексу
	int get_element(int index) {
		if (size <= index) throw std::exception("Не существующий индекс");
		return p_arr[index];
	};
//деструктор
	~smart_array() {
		std::cout << "Destructor\n";
		delete[] p_arr;
	};

	smart_array& operator=(smart_array& copy) {
		std::cout << "copy\n";
		size = copy.size;			//присваеваем новые размер и положение индекса
		index = copy.index;
		delete[] p_arr;				//удаляем старый массив
		p_arr = new int[size];		//создаем новый и переписываем туда элементы
		for (int i{}; i < size; i++)p_arr[i] = copy.p_arr[i];
		return *this;
	}

private:
	int size;				//размер массива
	int index{};			//индекс элемента
	int* p_arr;				//указатель на массив int
};

