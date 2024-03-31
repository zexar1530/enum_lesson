#pragma once

class smart_array
{
public:
explicit	smart_array(int size) :size{ size }, p_arr{ new int[size] {} } {};		//�����������
	smart_array(smart_array&) = delete;											//������������ ����������� �� �����
	smart_array(smart_array&& old_arr) noexcept {								//����������� �����������
		std::cout << "MOVE\n";
		index = old_arr.index;
		size = old_arr.size;
//		delete[] p_arr;
//		p_arr = new int[size];
		p_arr = old_arr.p_arr;							//�������� ������ ��������� ���������
		old_arr.p_arr = nullptr;						//����� ������ ����)))))))))
//		for (int i{}; i < size; i++)p_arr[i] = old_arr.p_arr[i];
//		delete[] old_arr.p_arr;
//		old_arr.p_arr = nullptr;
	};

//���������� �������� � �����
	void add_element(const int element) {
		if (index < size) {						//��������� �� ����� �������
			p_arr[index] = element;
			index++;
		}
		else {									//���� ����� �� ��������� ���� ���������
			int size_tmp = size + 5;
			int* p_tmp{ new int[size_tmp] {} };
			for (int i{}; i < size; i++) {			//�������� ��� ������ �� ���������
				p_tmp[i] = p_arr[i];		
			}
			delete[] p_arr;					//������� ������ ������
			p_arr = nullptr;
			p_arr = p_tmp;					//�������� ��������� ���������� �������. ��� ������ �� ����� ���������� �� ����� �����������
			size = size_tmp;								//� ��������� �� ����������� ������ �������� � ���� ������
			p_arr[index] = element;			//������� �� �������� ����� �������
			index++;			//����������� ������
		}
	};
//������� �������� �� �������
	int get_element(int index) {
		if (size <= index||index<0) throw std::runtime_error("�� ������������ ��� ������������� ������");
		return p_arr[index];
	};
//����������
	~smart_array() {
		std::cout << "Destructor\n";
		delete[] p_arr;
	};

	smart_array& operator=(const smart_array& copy) {
		if (this != &copy) {
			std::cout << "copy\n";
			size = copy.size;			//����������� ����� ������ � ��������� �������
			index = copy.index;
			delete[] p_arr;				//������� ������ ������
			p_arr = new int[size];		//������� ����� � ������������ ���� ��������
			for (int i{}; i < size; i++)p_arr[i] = copy.p_arr[i];
			return *this;
		}
		return *this;
	}

private:
	int size;				//������ �������
	int index{};			//������ ��������
	int* p_arr;				//��������� �� ������ int
};

