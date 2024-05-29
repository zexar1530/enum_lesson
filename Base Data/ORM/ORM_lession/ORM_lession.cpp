
#include <iostream>
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Postgres.h>
#include <string>

using namespace std;

class Book;		//обьявим класс Book
//---------------------------------------
class Publisher
{
public:
	string name{ "" };
	int id;
	Wt::Dbo::collection<Wt::Dbo::ptr<Book>> books;
	template <class A>
	void persist(A& a) {
		Wt::Dbo::field(a, id, "id");
		Wt::Dbo::field(a, name, "name");
		Wt::Dbo::hasMany(a, books, Wt::Dbo::ManyToOne, "id_publisher");
	};
};
//-------------------------------------------------
class Book
{
public:
	int id;
	string title{ "" };
	Wt::Dbo::ptr<Publisher> id_publisher;
	template<class A>
	void persist(A& a) {
		Wt::Dbo::field(a, id, "id");
		Wt::Dbo::field(a, title, "title");
		Wt::Dbo::belongsTo(a, id_publisher, "id_publisher");
	}
};


int main()
{
	try
	{
			string ConnectionString =
			"host=localhost "
			"port=5432 "
			"dbname=book "
			"user=postgres "
			"password=80017";

			/*Wt::Dbo::backend::Postgres*/ auto postgres{ make_unique<Wt::Dbo::backend::Postgres>(ConnectionString) };
			Wt::Dbo::Session session;
			session.setConnection(move(postgres));

			session.mapClass<Publisher>("publisher");	//создаем таблицу publisher
			session.mapClass<Book>("book");				//table book

	}
	catch (const Wt::Dbo::Exception& e)
	{
		cout << e.what();
	}
    std::cout << "Hello World!\n";
}
