//подключаем макросы catch2
#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include <iostream>
#include<catch2/catch_session.hpp>

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

List dl_list;

TEST_CASE("test DL List", "[DL List]") {

    SECTION("PushBack") {
        dl_list.PushBack(0);
        dl_list.PushBack(14348);
        dl_list.PushBack(-145);
        dl_list.PushBack(454);
        dl_list.PushBack(1);
        REQUIRE(dl_list.Size() == 5);
        dl_list.PopBack();
        REQUIRE(dl_list.Size() == 4);      
    }
    SECTION("PushFront") {
        dl_list.Clear();
        dl_list.PushFront(1);
        dl_list.PushFront(0);
        dl_list.PushFront(-5);
        dl_list.PushBack(1);
        dl_list.PushFront(104545);
        REQUIRE(dl_list.Size() == 5);
    }
    SECTION("PopBack") {
        dl_list.Clear();
        dl_list.PushFront(1);
        dl_list.PushFront(1);
        REQUIRE(dl_list.Size() == 2);
        
        dl_list.PopBack();
        REQUIRE(dl_list.Size() == 1);
        dl_list.PopBack();
        REQUIRE(dl_list.Size() == 0);
        REQUIRE_THROWS(dl_list.PopBack());
    }
    SECTION("PopFront") {
        dl_list.Clear();
        dl_list.PushFront(1);
        dl_list.PushFront(1);
        REQUIRE(dl_list.Size() == 2);

        dl_list.PopFront();
        REQUIRE(dl_list.Size() == 1);
        dl_list.PopFront();
        REQUIRE(dl_list.Size() == 0);
        REQUIRE_THROWS(dl_list.PopFront());
    }
}

int main(int argc, char* argv[]) {
    return Catch::Session().run(argc, argv);
}