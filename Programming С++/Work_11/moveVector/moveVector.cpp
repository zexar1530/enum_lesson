//#include <memory>
//#include <iostream>
//#include <vector>
//
//template<class T>
//void move_vectors(std::vector<T>& one, std::vector<T>& two) {
//	two = std::move(one);
////	two = one;
//}
//
//int main()
//{
//	std::vector <std::string> one = { "test_string1", "test_string2" };
//	std::vector <std::string> two;
//	move_vectors(one, two);
//	for (auto v : two) std::cout << " " << v;
//	for (auto v : one) std::cout << " " << v;		//С Move все работает!, а без просто копирование
//	return 0;
//}
//#include <algorithm>
//#include <vector>
//#include <iostream>
//#include <numeric>
//#include <execution>
//#include <asio.hpp>
//int main() {
	/*boost::asio::io_context io_context;
	std::vector<long> numbers( 1'000'000, 1), squares( 1'000'000, 0 );
		std::iota(numbers.begin(), numbers.end(), 0);
		size_t n_transformed{};
		std::transform(std::execution::par, numbers.begin(), numbers.end(),
			squares.begin(), [&n_transformed](const auto x) {
				++n_transformed;
					return x * x;
			});
	std::cout << "n_transformed: " << n_transformed << std::endl;*/

#include <asio.hpp>
#include <iostream>
#include <istream>
#include <ostream>
#include <string>

std::string request1(std::string host, boost::asio::io_context & io_context) {
		std::stringstream request_stream;
	request_stream << "GET / HTTP/1.1\r\n"
		"Host: " << host << "\r\n"
		"Accept: text/html\r\n"
		"Accept-Language: ru-ru\r\n"
		"Accept-Encoding: identity\r\n"
		"Connection: close\r\n\r\n";
	const auto request = request_stream.str();
		boost::asio::ip::tcp::resolver resolver{ io_context };
	const auto endpoints = resolver.resolve(host, "https");
		boost::asio::ip::tcp::socket socket{ io_context };
	const auto connected_endpoint = boost::asio::connect(socket, endpoints);
		boost::asio::write(socket, boost::asio::buffer(request));
		std::string response;
	boost::system::error_code ec;
	boost::asio::read(socket, boost::asio::dynamic_buffer(response), ec);
		if (ec && ec.value() != 2) throw boost::system::system_error{ ec };
			return response;
}
int main() {
	boost::asio::io_context io_context;
	try {
		const auto response = request1("www.yandex.ru", io_context);
			std::cout << response << "\n";
	}
	catch (boost::system::system_error& se) {
		std::cerr << "Error: " << se.what() << std::endl;
	}
}
	
