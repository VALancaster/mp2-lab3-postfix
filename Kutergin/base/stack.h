#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;

using namespace std;

template <class T>
class TStack
{
private:
    T* pMem;
    int size;
    int top;
public:
    TStack(int sz = 10) // конструктор инициализатор
    {
        size = sz;
        top = -1;
        if ((size < 1) || (size > MaxStackSize)) // стек будет всегда правильно инициализирован, не нужны лишние проверки
            throw out_of_range("Stack size should be greater or equal than 1 and less than MaxStackSize");;
        pMem = new T[size];
    }

    ~TStack() // деструктор
    {
        delete[] pMem;
    }

    int getSize() const
    {
        return size;
    }

    bool IsEmpty() const
    {
        return top == -1;
    }

    bool IsFull() const
    {
        return top == size - 1;
    }

    void push(const T& val)
    {
        if (IsFull()) // во избежание переполнения стека: перевыделим память для стека в два раза большую
        {
            T* tmpMem = new T[size * 2];
            copy(pMem, pMem + size, tmpMem);
            delete[] pMem;
            pMem = tmpMem;
            size *= 2;
        }
        pMem[++top] = val;
    }

    T pop()
    {
        if (IsEmpty())
            throw out_of_range("Nothing to pop. The stack is empty");
        return pMem[top--];
    }

    T getTop()
    {
        if (IsEmpty())
            throw out_of_range("Stack is empty");
        return pMem[top];
    }
};

#endif
