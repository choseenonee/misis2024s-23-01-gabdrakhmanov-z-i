#ifndef QUEUELSTPR
#define QUEUELSTPR

#include <stdexcept>

class QueueLstPr {
public:
    QueueLstPr() = default;

    QueueLstPr(const QueueLstPr& rhs);

    QueueLstPr& operator=(const QueueLstPr& rhs);

    const float& Top() const;

    float& Top();

    void Push(const float& rhs);

    void Pop();

    bool IsEmpty() const noexcept;

    void Clear() noexcept;

    ~QueueLstPr();

private:
    struct Node {
        float data = 0.0f;
        Node* next_node = nullptr;
    };

    Node* head_ = nullptr;
    Node* tail_ = nullptr;
};

#endif