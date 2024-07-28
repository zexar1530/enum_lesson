#include <string>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <ostream>

class Text {
public:
    virtual void render(const std::string& data) const {
        std::cout << data;
    }
};


class DecoratedText : public Text {
public:
    explicit DecoratedText(std::shared_ptr<Text> text) : text_(text) {}
    std::shared_ptr<Text> text_;
};

class Paragraph :public DecoratedText {
public:
    Paragraph(std::shared_ptr<Text> text) :DecoratedText(text) {}
    void render(const std::string& data) const override {
        std::cout << "<p>";
        text_->render(data);
        std::cout << "</p>";
    }
};

class Reversed :DecoratedText {
public:
    Reversed(std::shared_ptr<Text> text) :DecoratedText(text) {}
    void render(const std::string& data) const override {
        std::string d_cout{ data }; //с const пришлось повозится)))). Не сразу понял в чем подвох
        std::reverse(d_cout.begin(),d_cout.end());
        std::cout << d_cout;
    }
};

class Link :DecoratedText {
public:
    Link(std::shared_ptr<Text> text) :DecoratedText(text) {}
    void render(const std::string& addr, const std::string& data) const { //перегрузили
        std::cout << "<a href=" << addr << ">" << data << "</a>";
    }
};

class ItalicText : public DecoratedText {
public:
    explicit ItalicText(std::shared_ptr<Text> text) : DecoratedText(text) {}
    void render(const std::string& data)  const {
        std::cout << "<i>";
        text_->render(data);
        /*Text::render(data);*/
        std::cout << "</i>";
    }
};

class BoldText : public DecoratedText {
public:
    explicit BoldText(std::shared_ptr<Text> text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::cout << "<b>";
        text_->render(data);
        std::cout << "</b>";
    }
};

int main() {
    auto text_block = std::make_shared<BoldText>(std::make_shared<ItalicText>(std::make_shared<Text>()));
    text_block->render("Hello world");

    std::cout << std::endl;

    auto text_block1 = std::make_shared<Paragraph>(std::make_shared<Text>());
    text_block1->render("Hello world");

    std::cout << std::endl;

    auto text_block2 = std::make_shared<Reversed>(std::make_shared<Text>());
    text_block2->render("Hello world");

    std::cout << std::endl;

    auto text_block3 = std::make_shared<Link>(std::make_shared<Text>());
    text_block3->render("netology.ru", "Hello world");
};