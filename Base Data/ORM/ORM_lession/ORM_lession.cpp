
#include <iostream>
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Postgres.h>
#include <string>

using namespace std;

class Book;		//обьявим класс Book
class Stock;	// class Stock
//---------------------------------------
class Publisher
{
public:
	string name{ "" };
	Wt::Dbo::collection<Wt::Dbo::ptr<Book>> books;
	template <class A>
	void persist(A& a) {
		Wt::Dbo::field(a, name, "name");
		Wt::Dbo::hasMany(a, books, Wt::Dbo::ManyToOne, "id_publisher");
	};
	static void addPublisher(const string& name, Wt::Dbo::Session& session) {
		Wt::Dbo::Transaction tr(session);
		unique_ptr<Publisher> publisher{ new Publisher() };
		publisher->name = name;
		Wt::Dbo::ptr<Publisher> p_publisher = session.add(move(publisher));
		tr.commit();
	}
};
//-------------------------------------------------
class Book
{
public:
	string title{ "" };
	Wt::Dbo::ptr<Publisher> id_publisher;
	Wt::Dbo::collection<Wt::Dbo::ptr<Stock>> stocks;
	template<class A>
	void persist(A& a) {
		Wt::Dbo::field(a, title, "title");
		Wt::Dbo::belongsTo(a, id_publisher, "id_publisher");
		Wt::Dbo::hasMany(a, stocks, Wt::Dbo::ManyToOne, "id_book");
	}
	static void addBook(const string& title, const string& id_publisher, Wt::Dbo::Session& session) {
		Wt::Dbo::Transaction tr(session);
		unique_ptr<Book> book{ new Book() };
		book->title = title;
		book->id_publisher = session.find<Publisher>().where("name=?").bind(id_publisher);
		Wt::Dbo::ptr<Book> p_book = session.add(move(book));
		tr.commit();
	}
};

//---------------------------------------
class Shop
{
public:
	string name{ "" };
	Wt::Dbo::collection<Wt::Dbo::ptr<Stock>> stocks;
	template <class A>
	void persist(A& a) {
		Wt::Dbo::field(a, name, "name");
		Wt::Dbo::hasMany(a, stocks, Wt::Dbo::ManyToOne, "id_shop");
	};
	static void addShop(const string& name, Wt::Dbo::Session& session) {
		Wt::Dbo::Transaction tr(session);
		unique_ptr<Shop> shop{ new Shop() };
		shop->name = name;
		Wt::Dbo::ptr<Shop> p_shop = session.add(move(shop));
		tr.commit();
	}
};
//---------------------------------------------------------------------
class Stock
{
public:
	int count;
	Wt::Dbo::ptr<Book> id_book;	
	Wt::Dbo::ptr<Shop> id_shop;
	template<class A>
	void persist(A& a) {
		Wt::Dbo::field(a, count, "count");
		Wt::Dbo::belongsTo(a, id_book, "id_book");
		Wt::Dbo::belongsTo(a, id_shop, "id_shop");
	}
	/*static void addBook(const string& title, const string& id_publisher, Wt::Dbo::Session& session) {
		Wt::Dbo::Transaction tr(session);
		unique_ptr<Book> book{ new Book() };
		book->title = title;
		book->id_publisher = session.find<Publisher>().where("name=?").bind(id_publisher);
		Wt::Dbo::ptr<Book> p_book = session.add(move(book));
		tr.commit();
	}*/
};
//-------------------------------------------------------------------------
class Sale
{
public:
	int count;
	int price;
	Wt::Dbo::ptr<Stock> stocks;
	template<class A>
	void persist(A& a) {
		Wt::Dbo::field(a, count, "count");
		Wt::Dbo::field(a, price, "price");
		Wt::Dbo::belongsTo(a, stocks, "id_stock");
	}
};


int main()
{
	locale::global(std::locale("ru_RU.UTF-8"));
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
			session.mapClass<Shop>("shop");				//table shop
			session.mapClass<Stock>("stock");			//table stock
			session.mapClass<Sale>("sale");				//table sale
			session.createTables();

			//-------------заполняем таблицу Publisher----------------
			Publisher::addPublisher("BBB", session); //Завернул все в статический метод класса
			Publisher::addPublisher("AAA", session);
			Publisher::addPublisher("CCC", session);

			//------------заполняем таблицу Book----------------------
			Book::addBook("Unknow1", "BBB", session);
			Book::addBook("Unknow2", "BBB", session);
			Book::addBook("Unknow3", "AAA", session);
			Book::addBook("Unknow1", "CCC", session);

			//-------------fill table Shop-----------------------------
			Shop::addShop("shop1", session);
			Shop::addShop("shop2", session);

			//---------------fill table 



	}
	catch (const Wt::Dbo::Exception& e)
	{
		cout << e.what();
	}
    std::cout << "Hello World!\n";
}
