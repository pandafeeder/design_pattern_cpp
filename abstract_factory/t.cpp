#include <iostream>
#include <memory>

// interface
class Button {
public:
    virtual void draw() = 0;
};

class WinButton: public Button {
public:
    virtual void draw() override
    {
        std::cout << "Win button drawn\n";
    }
};

class MacButton: public Button {
public:
    virtual void draw() override
    {
        std::cout << "Mac button drawn\n";
    }
};

// interface
class ScrollBar
{
public:
    virtual void draw() = 0;
};

class WinScrollBar: public ScrollBar {
public:
    virtual void draw() override
    {
        std::cout << "Win scrollBar drawn\n";
    }
};

class MacScrollBar: public ScrollBar {
public:
    virtual void draw() override
    {
        std::cout << "Mac scrollBar drawn\n";
    }
};


class GUIFactory {
public:
    virtual std::unique_ptr<Button> createButton() = 0;
    virtual std::unique_ptr<ScrollBar> createScrollBar() = 0;
};

class WinFactory: public GUIFactory {
public:
    virtual std::unique_ptr<Button> createButton() override
    {
        return std::make_unique<WinButton>();
    }
    virtual std::unique_ptr<ScrollBar> createScrollBar() override
    {
        return std::make_unique<WinScrollBar>();
    }
};

class MacFactory: public GUIFactory {
public:
    virtual std::unique_ptr<Button> createButton() override
    {
        return std::make_unique<MacButton>();
    }
    virtual std::unique_ptr<ScrollBar> createScrollBar() override
    {
        return std::make_unique<MacScrollBar>();
    }
};

int main()
{
    std::unique_ptr<GUIFactory> guiFactory = std::make_unique<MacFactory>();
    std::unique_ptr<Button> btn = guiFactory->createButton();
    std::unique_ptr<ScrollBar> bar = guiFactory->createScrollBar();
    btn->draw();
    bar->draw();
}
