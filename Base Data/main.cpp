#include <iostream>
#include <pqxx/pqxx>
#include <string>
#include <sstream>
#include <Windows.h>
#include <tuple>

using namespace std;

class TransactionBase {
public:
	//удаляем конструкторы копирования и присваивания
	TransactionBase(const TransactionBase&) = delete;
	TransactionBase(TransactionBase&&) = delete;
	TransactionBase() = delete;

	//конструктор
explicit TransactionBase(const string host, const string port, const string dbname, const string user, const string pass) :
		host(host), port(port), dbname(dbname), user(user), pass(pass) {
		try				//Правильно ли что блок try в конструкторе определил?
		{
			s << "host=" << host << " port=" << port << " dbname=" << dbname << " user=" << user << " password=" << pass;
			p_conn = new pqxx::connection(s.str());
		}
		catch (const runtime_error& e)
		{
			throw runtime_error("ошибка работы с БД");
			cout << e.what();
		}
	};

	//деструктор
	~TransactionBase() {
		delete p_conn;
	}

	//созданеие базы
	void TransactionCreate() {
		pqxx::work creat_table{ *p_conn };
		creat_table.exec("create table if not exists Phones( "
			"Name text not null, "
			"Sur_name text not null, "
			"Number text, "
			"E_mail text primary key not null);");
		creat_table.commit();
	};

	//добавление нового клиента
	void AddClient(const string& name, const string& surname, const string& email, const string& phonenumber = "") {
		pqxx::work creat_client{ *p_conn };
		if (phonenumber != "") creat_client.exec("insert into Phones (Name, Sur_name, E_mail, Number) values ('" + creat_client.esc(name) + "','" + creat_client.esc(surname) +
			"','" + creat_client.esc(email) + "','" + creat_client.esc(phonenumber) + "');");
		else
			creat_client.exec("insert into Phones (Name, Sur_name, E_mail) values ('" + creat_client.esc(name) + "','" + creat_client.esc(surname) +
				"','" + creat_client.esc(email) + "');");
		creat_client.commit();
	};

	//добавляем номер телефона к существующему клиенту
	void AddTellNumber() {
		pqxx::work add_tell{ *p_conn };
		add_tell.exec("update Phones set Number='555555' where E_mail='email@5';");
		add_tell.commit();
	};

	//удаляем телефон у существующего клиента
	void DelTell(const string email) {
		pqxx::work del_tell{ *p_conn };
		del_tell.exec("update Phones set Number=null where E_mail='" + del_tell.esc(email) + "';");
		del_tell.commit();
	}

	//удаляем клиента
	void DelClt(const string email) {
		pqxx::work del_clt{ *p_conn };
		del_clt.exec("delete from Phones where E_mail='" + del_clt.esc(email) + "';");
		del_clt.commit();
	};

	//поиск клиента по имени
	void Select(const string& name) {
		pqxx::work select{ *p_conn };
		/*for (auto [name,surname, mail] : select.query<string, string,string>("select name, sur_name, E_mail from Phones where name='"+select.esc(name) + "';")) {
			cout << name << " " << surname << " " << mail << endl;
		}*/
		auto cort{ select.query<string, string,string>("select name, sur_name, E_mail from Phones where name='" + select.esc(name) + "';") };
		for(tuple<string,string,string>t:cort)
			cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << endl;
	};
private:
	string host, port, dbname, user, pass;
	pqxx::connection* p_conn;			// Указатель на подключение
	ostringstream s;					//сборка строки транзакции

};

int main() {
	locale::global(std::locale("ru_RU.UTF-8"));
	
//	auto tb = make_unique<TransactionBase>("localhost", "5432", "phone", "postgres", "80017");
	TransactionBase tb("localhost", "5432", "phone", "postgres", "80017");	//создаем наш обьект
	try
	{
		tb.TransactionCreate(); //create
		tb.AddClient("Vasy", "Pupkin", "email@1", "1234567");
		tb.AddClient("Pety", "Ivanov", "email@3", "18768");
		tb.AddClient("Pety", "Ivanov", "email@5");
		tb.AddTellNumber();
		tb.DelTell("email@5");
		tb.DelClt("email@3");
		tb.Select("Vasy");
	}
	catch (const pqxx::sql_error& e)
	{
		cout << e.what();
	}

	return 0;
}