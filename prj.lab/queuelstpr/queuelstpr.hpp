#ifndef QUEUELSTPR
#define QUEUELSTPR

#include <stdexcept>

class QueueLstPr {
public:
    QueueLstPr() = default;
    QueueLstPr(QueueLstPr&& rhs) noexcept;

    QueueLstPr(const QueueLstPr& rhs);

    QueueLstPr& operator=(QueueLstPr&& rhs) noexcept;
    QueueLstPr& operator=(const QueueLstPr& rhs);

    const float& Top() const;

    float& Top();

    void Push(const float& rhs);

    void Pop() noexcept;

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