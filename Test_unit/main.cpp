//подключаем макросы catch2
#include <catch2/catch_test_macros.hpp>
#include <iostream>

struct ListNode
{
public:
    ListNode(int value, ListNode* prev = nullptr, ListNode* next = nullptr)
        : value(value), prev(prev), next(next)
    {
        if (prev != nullptr) prev->next = this;
        if (next != nullptr) next->prev = this;
    }

public:
    int value;
    ListNode* prev;
    ListNode* next;
};


class List
{
public:
    List()
        : m_head(new ListNode(static_cast<int>(0))), m_size(0),
        m_tail(new ListNode(0, m_head))
    {
    }

    virtual ~List()
    {
        Clear();
        delete m_head;
        delete m_tail;
    }

    bool Empty() { return m_size == 0; }

    unsigned long Size() { return m_size; }

    void PushFront(int value)
    {
        new ListNode(value, m_head, m_head->next);
        ++m_size;
    }

    void PushBack(int value)
    {
        new ListNode(value, m_tail->prev, m_tail);
        ++m_size;
    }

    int PopFront()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_head->next->next);
        int ret = node->value;
        delete node;
        return ret;
    }

    int PopBack()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_tail);
        int ret = node->value;
        delete node;
        return ret;
    }

    void Clear()
    {
        auto current = m_head->next;
        while (current != m_tail)
        {
            current = current->next;
            delete extractPrev(current);
        }
    }

private:
    ListNode* extractPrev(ListNode* node)
    {
        auto target = node->prev;
        target->prev->next = target->next;
        target->next->prev = target->prev;
        --m_size;
        return target;
    }

private:
    ListNode* m_head;
    ListNode* m_tail;
    unsigned long m_size;
};
//юнит-тест
TEST_CASE( "EMPTY SIZE CLEAR", "EMPTY" ) {
        List l;
        REQUIRE(l.Empty() == true);
    SECTION("[Size]") {
        l.PushBack(1);
        l.PushBack(2);
        REQUIRE(l.Size() == 2);
    };
    SECTION("[Clear]") {
        l.Clear();
        REQUIRE(l.Size() == 0);
    }
}

TEST_CASE("PUSHBACK PUSHFRONT POPBACK POPFRONT", "[PUSHBACK]") {
    List l;
    l.PushBack(5);
    REQUIRE(l.Size() == 1);
    REQUIRE(l.PopBack() == 5);
    SECTION("[PUSHFRONT]") {
        l.PushFront(10);
        REQUIRE(l.PopFront() == 10);
    }
    SECTION("[POPBACK]") {
        REQUIRE_THROWS(l.PopBack());
    }
    SECTION("[POPFRONT]") {
        REQUIRE_THROWS(l.PopFront());
    }
}