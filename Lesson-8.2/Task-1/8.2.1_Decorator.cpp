#include <string>
#include <iostream>
#include <algorithm> // for std::reverse

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

class ItalicText : public DecoratedText {
public:
    explicit ItalicText(Text* text) : DecoratedText(text) {}
    void render(const std::string& data)  const {
        std::cout << "<i>";
        text_->render(data);
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

// Paragraph
class Paragraph : public DecoratedText {
public:
    explicit Paragraph(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const override {
        std::cout << "<p>";
        text_->render(data);
        std::cout << "</p>";
    }
};

// Reversed
class Reversed : public DecoratedText {
public:
    explicit Reversed(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const override {
        std::string reversed_data = data;
        std::reverse(reversed_data.begin(), reversed_data.end());
        text_->render(reversed_data);
    }
};

// Link
class Link : public DecoratedText {
public:
    explicit Link(Text* text) : DecoratedText(text) {}
    void render(const std::string& url, const std::string& text) const {
        std::cout << "<a href=" << url << ">";
        text_->render(text);
        std::cout << "</a>";
    }
    // override base "render" method to make it work as an original method
    void render(const std::string& data) const override {
        text_->render(data);
    }
};

int main() {
    auto paragraph = new Paragraph(new Text());
    paragraph->render("Hello world");
    std::cout << std::endl;

    std::cout << "\n" << std::endl;

    auto reversed = new Reversed(new Text());
    reversed->render("Hello world");
    std::cout << std::endl;

    std::cout << "\n" << std::endl;

    auto link = new Link(new Text());
    link->render("netology.ru", "Hello world");
    std::cout << std::endl;

    delete paragraph;
    delete reversed;
    delete link;

    return 0;
}