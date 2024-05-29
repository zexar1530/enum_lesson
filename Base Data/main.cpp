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
		creat_table.exec("create table if not exists Client( "
			"Id_client integer primary key, "
			"Name text not null, "
			"Sur_name text not null, "
			"E_mail text not null);");
		//creat_table.commit();
		creat_table.exec("create table if not exists Phone( "
			"id_phone text primary key, "
			"id_client integer references Client(Id_client), "
			"Number text);");
		creat_table.commit();
	};

	//добавление нового клиента
	void AddClient(string id_c, const string& name, const string& surname, const string& email) {
		pqxx::work creat_client{ *p_conn };
		creat_client.exec("insert into Client (Id_client, Name, Sur_name, E_mail) values ('"+id_c+"','" + creat_client.esc(name) + "','" + creat_client.esc(surname) +
				"','" + creat_client.esc(email) + "');");
		creat_client.commit();
	};

	//добавляем номер телефона к существующему клиенту
	void AddTellNumber(const string& id_p, const string& id_c, const string& phonenumber) {
		pqxx::work add_tell{ *p_conn };
		add_tell.exec("insert into Phone (id_phone, id_client, Number) values ('" + id_p + "','" + add_tell.esc(id_c) + "','" + add_tell.esc(phonenumber) + "');");
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
		//----------add client-----------------------------
		tb.AddClient("2", "aaaa", "aaaaa", "email@4");
		tb.AddClient("3", "Vasy", "Pupkin", "email@1");
		tb.AddClient("4", "Pety", "Ivanov", "email@3");
		tb.AddClient("5", "Pety", "Ivanov", "email@3");
		//---------add phone------------------------------
		tb.AddTellNumber("1", "2", "1234567");
		tb.AddTellNumber("2", "2", "123456789"); //у ааааа два телефона
		tb.AddTellNumber("3", "3", "234234234"); //а это Вася 1 телефон

		/*tb.AddClient("Pety", "Ivanov", "email@3", "18768");
		tb.AddClient("Pety", "Ivanov", "email@5");
		tb.AddClient("Pety", "Ivanov", "email@3", "18769");*/
		/*tb.AddTellNumber();
		tb.DelTell("email@5");
		tb.DelClt("email@3");
		tb.Select("Vasy");*/
	}
	catch (const pqxx::sql_error& e)
	{
		cout << e.what();
	}

	return 0;
}