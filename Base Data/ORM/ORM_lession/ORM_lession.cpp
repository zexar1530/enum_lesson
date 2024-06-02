
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
	static void addStock(const string& id_book, const string& id_shop, int count, Wt::Dbo::Session& session) {
		Wt::Dbo::Transaction tr(session);
		unique_ptr<Stock> stock{ new Stock() };
		stock->id_book = session.find<Book>().where("title=?").bind(id_book);
		stock->id_shop = session.find<Shop>().where("name=?").bind(id_shop);
		stock->count = count;
		Wt::Dbo::ptr<Stock> p_stock = session.add(move(stock));
		tr.commit();
	}
};
//-------------------------------------------------------------------------
class Sale
{
public:
	int count;
	int price;
	string date_sale;
	Wt::Dbo::ptr<Stock> stocks;
	template<class A>
	void persist(A& a) {
		Wt::Dbo::field(a, count, "count");
		Wt::Dbo::field(a, price, "price");
		Wt::Dbo::field(a, date_sale, "date_sale");
		Wt::Dbo::belongsTo(a, stocks, "id_stock");
	}
	static void addSale(const string& date_sale, int price, int count, int id, Wt::Dbo::Session& session) {
		Wt::Dbo::Transaction tr(session);
		unique_ptr<Sale> sale{ new Sale() };
		sale->count = count;
		sale->date_sale = date_sale;
		sale->stocks = session.find<Stock>().where("id=?").bind(id);
		sale->price = price;
		Wt::Dbo::ptr<Sale> p_sale = session.add(move(sale));
		tr.commit();
	}
};
//-----------поиск магазинов по имени издателя--------------------------
//SELECT s.name  FROM shop s					Ломаю голову как его описать через ORM
//JOIN stock st ON s.id = st.id_shop_id
//JOIN book b  ON st.id_book_id = b.id
//JOIN publisher p ON b.id_publisher_id = p.id
//where  p.name = 'AAA';
void TransactPublisher(const string& name_publisher, Wt::Dbo::Session& session) {
	Wt::Dbo::Transaction tr(session);
	//Wt::Dbo::collection<Wt::Dbo::ptr<Shop>> shop_collection;
	//shop_collection = session.find<Shop>().join("stock ON shop.id = stock.id_shop_id").join("book ON stock.id_book_id = book.id")
	//	.join("publisher ON book.id_publisher_id = publisher.id").where("publisher.name=?").bind(name_publisher);
	string str = session.query<string>("SELECT s.name  FROM shop s JOIN stock st ON s.id = st.id_shop_id JOIN book b  ON st.id_book_id = b.id "
		" JOIN publisher p ON b.id_publisher_id = p.id").where("p.name = ?").bind(name_publisher);
	tr.commit();
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
			Book::addBook("Unknow4", "CCC", session);

			//-------------fill table Shop-----------------------------
			Shop::addShop("shop1", session);
			Shop::addShop("shop2", session);

			//---------------fill table stock-------------------------
			Stock::addStock("Unknow1", "shop1", 10, session); //book Unknow1 in the shop1 10 штук
			Stock::addStock("Unknow1", "shop2", 30, session); //book Unknow1 in the shop2 30 штук
			Stock::addStock("Unknow2", "shop1", 50, session); //book Unknow2 in the shop1 50 штук
			Stock::addStock("Unknow3", "shop2", 10, session); //book Unknow3 in the shop2 10 штук
			Stock::addStock("Unknow4", "shop1", 15, session); //book Unknow4 in the shop1 15 штук
			Stock::addStock("Unknow4", "shop2", 35, session); //book Unknow4 in the shop2 35 штук

			//--------------fill the table sale------------------------
			Sale::addSale("2024-06-01", 2000, 1, 2, session);
			Sale::addSale("2024-06-02", 2500, 3, 5, session);

			cout << "Введите писателя: ";
			string name;
			cin >> name;
			TransactPublisher(name, session);

	}
	catch (const Wt::Dbo::Exception& e)
	{
		cout << e.what();
	}
    std::cout << "Hello World!\n";
}
