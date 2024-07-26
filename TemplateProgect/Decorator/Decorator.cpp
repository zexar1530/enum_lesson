#include <string>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

class Text {
public:
    virtual void render(const std::string& data) const {
        std::cout << data;
    }
};


class DecoratedText : public Text {
public:
    explicit DecoratedText(Text* text) : text_(text) {}
    Text* text_;
};

class Paragraph :public DecoratedText {
public:
    Paragraph(Text* text) :DecoratedText(text) {}
    void render(const std::string& data) const override {
        std::cout << "<p>";
        text_->render(data);
        std::cout << "</p>";
    }
};

class Reversed :DecoratedText {
public:
    Reversed(Text* text) :DecoratedText(text) {}
    void render(const std::string& data) const override {
        std::string d_cout{ data }; //с const пришлось повозится)))). Не сразу понял в чем подвох
        std::reverse(d_cout.begin(),d_cout.end());
        std::cout << d_cout;
    }
};

class Link :DecoratedText {
public:
    Link(Text* text) :DecoratedText(text) {}
    void render(const std::string& addr, const std::string& data) const { //перегрузили
        std::cout << "<a href=" << addr << ">" << data << "</a>";
    }
};

class ItalicText : public DecoratedText {
public:
    explicit ItalicText(Text* text) : DecoratedText(text) {}
    void render(const std::string& data)  const {
        std::cout << "<i>";
        text_->render(data);
        /*Text::render(data);*/
        std::cout << "</i>";
    }
};

class BoldText : public DecoratedText {
public:
    explicit BoldText(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::cout << "<b>";
        text_->render(data);
        std::cout << "</b>";
    }
};

int main() {
    auto text_block = std::make_shared<BoldText>(new ItalicText(new Text()));
    text_block->render("Hello world");

    std::cout << std::endl;

    auto text_block1 = new Paragraph(new Text());
    text_block1->render("Hello world");

    std::cout << std::endl;

    auto text_block2 = new Reversed(new Text());
    text_block2->render("Hello world");

    std::cout << std::endl;

    auto text_block3 = new Link(new Text());
    text_block3->render("netology.ru", "Hello world");
};