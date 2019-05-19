#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <functional>
#include <string>
#include <conio.h>

using namespace std;

template<typename TElement>
class Sequence
{
protected:
    int length;
public:
    int GetLength()
    {
        return length;
    }

    bool GetIsEmpty()
    {
        bool empt;
        if (length == 0) empt = true;
            else
                empt == false;
        return empt;
    }

    virtual string TypeofSequence() = 0;

    virtual void Print() = 0;

    virtual void Swap(int first, int second) = 0;

    virtual TElement Get(int index) = 0;

    virtual TElement GetFirst() = 0;

    virtual TElement GetLast() = 0;

    virtual void GetSubsequence(int StartIndex, int EndIndex) = 0;

    virtual void Append(TElement item) = 0;

    virtual void Prepend(TElement item) = 0;

    virtual void InsertAt(int index, TElement item) = 0;

    virtual void Remove(TElement item) = 0;
};

template<typename TElement>
class ArraySequence : public Sequence<TElement>
{
    TElement *array_head;
public:
    ArraySequence(){}

    ArraySequence(int inp_length, bool random)
    {
        this->length = inp_length;
        array_head = new TElement[this->length];
        if (random == false)
        {
            if (this->length != 0)
                cout << "������� �������� Array Sequence:" << endl;
            for (int i = 0; i < this->length; i++)
                cin >> array_head[i];
        }

        if (random == true)
        {
            cout << "�������� ��� ���������:" << endl;
            cout << "1. ��������� ���������" << endl;
            cout << "2. ������������� ���������" << endl;
            cout << "3. �������������������� ���������" << endl;
            char choice;
            cin >> choice;
            cout << "��������������� �������� Array Sequence:" << endl;
            if (choice == '1')
            {
                for (int i = 0; i < this->length; i++)
                {
                    array_head[i] = rand();
                    cout << array_head[i] << " ";
                }
                cout << endl;
            }

            if (choice == '2')
            {
                for (int i = 0; i < this->length; i++)
                {
                    array_head[i] = rand();
                    if (i != 0)
                    {
                        while (array_head[i-1] > array_head[i])
                            array_head[i] = array_head[i] + (rand() % 10);
                    }
                    cout << array_head[i] << " ";
                }
                cout << endl;
            }

            if (choice == '3')
            {
                for (int i = 0; i < this->length; i++)
                {
                    array_head[i] = rand();
                    if (i != 0)
                    {
                        while (array_head[i-1] < array_head[i])
                            array_head[i] = array_head[i] - (rand() % 10);
                    }
                    cout << array_head[i] << " ";
                }
                cout << endl;
            }
        }
    }

    ArraySequence(const ArraySequence &arrseq)
    {
        this->array_head = new TElement[arrseq.length];
        this->length = arrseq.length;
        for (int i = 0; i < arrseq.length; i++)
            this->array_head[i] = arrseq.array_head[i];
    }

    string TypeofSequence()
    {
        return "ArraySequence";
    }

    void Print()
    {
        for (int i = 0; i < this->length; i++)
            cout << array_head[i] << " ";
        cout << endl;
    }

    void Swap(int first, int second)
    {
        int temp = array_head[first];
        array_head[first] = array_head[second];
        array_head[second] = temp;
    }

    TElement Get(int index)
    {
        while (index < 0 || index >= this->length)
        {
            cout << "������� ���������� ��������!" << endl;
            cin >> index;
        }
        return array_head[index];
    }

    TElement GetFirst()
    {
        return array_head[0];
    }

    TElement GetLast()
    {
        return array_head[this->length - 1];
    }

    void GetSubsequence(int StartIndex, int EndIndex)
    {
        while (StartIndex < 0 || StartIndex > EndIndex || EndIndex >= this->length)
        {
            cout << "������� ���������� ��������!" << endl;
            cin >> StartIndex >> EndIndex;
        }
        ArraySequence *Subsequence = new ArraySequence;
        Subsequence->length = EndIndex - StartIndex + 1;
        Subsequence->array_head = new TElement[Subsequence->length];
        int j = 0;
        for (int i = StartIndex; i <= EndIndex; i++){
            Subsequence->array_head[j] = array_head[i];
            j++;
        }
        array_head = Subsequence->array_head;
        this->length = Subsequence->length;
    }

    void Append(TElement item)
    {
        ArraySequence *Appendsequence = new ArraySequence;
        Appendsequence->length = this->length + 1;
        Appendsequence->array_head = new TElement[Appendsequence->length];
        for (int i = 0; i < this->length; i++)
            Appendsequence->array_head[i] = array_head[i];
        Appendsequence->array_head[Appendsequence->length - 1] = item;
        array_head = Appendsequence->array_head;
        this->length = Appendsequence->length;
    }

    void Prepend(TElement item)
    {
        ArraySequence *Prependsequence = new ArraySequence;
        Prependsequence->length = this->length + 1;
        Prependsequence->array_head = new TElement[Prependsequence->length];
        for (int i = 0; i < this->length; i++)
            Prependsequence->array_head[i + 1] = array_head[i];
        Prependsequence->array_head[0] = item;
        array_head = Prependsequence->array_head;
        this->length = Prependsequence->length;
    }

    void InsertAt(int index, TElement item)
    {
        while (index < 0 || index >= this->length)
        {
            cout << "������� ���������� ��������!" << endl;
            cin >> index;
        }
        ArraySequence *Insertsequence = new ArraySequence;
        Insertsequence->length = this->length + 1;
        Insertsequence->array_head = new TElement[Insertsequence->length];
        for (int i = 0; i < index; i++)
            Insertsequence->array_head[i] = array_head[i];
        Insertsequence->array_head[index] = item;
        for (int i = index + 1; i < Insertsequence->length; i++)
            Insertsequence->array_head[i] = array_head[i - 1];
        array_head = Insertsequence->array_head;
        this->length = Insertsequence->length;
    }

    void Remove(TElement item)
    {
        int size = this->length;
        for (int i = 0 ; i < size; i++){
            if (array_head[i] == item)
              this->length = this->length - 1;
        }
        ArraySequence *newSequence = new ArraySequence;
        newSequence->array_head = new TElement[this->length];
        newSequence->length = this->length;
        for (int i = 0, j = 0; i < size; i++){
            if (array_head[i] != item){
                newSequence->array_head[j] = array_head[i];
                j++;
            }
        }
        array_head = newSequence->array_head;
        this->length = newSequence->length;
    }

};

template<typename TElement>
class ListSequence : public Sequence<TElement>
{
    TElement value;
    ListSequence<TElement> *head, *next;
public:
    ListSequence(){}

    ListSequence(int inp_length, bool random)
    {
        this->length = inp_length;
        head = this;
        ListSequence *temp = head;
        if (random == false)
        {
            if (this->length != 0)
            {
                cout << "������� �������� List Sequence" << endl;
                cin >> temp->value;
            }
            for (int i = 0; i < this->length - 1; i++)
            {
                temp->next = new ListSequence<TElement>;
                temp = temp->next;
                cin >> temp->value;
            }
        }

        if (random == true)
        {
            cout << "�������� ��� ���������:" << endl;
            cout << "1. ��������� ���������" << endl;
            cout << "2. ������������� ���������" << endl;
            cout << "3. �������������������� ���������" << endl;
            char choice;
            cin >> choice;
            cout << "��������������� �������� List Sequence:" << endl;
            if (choice == '1')
            {
                if (this->length != 0)
                {
                    temp->value = rand();
                    cout << temp->value << " ";
                }
                for (int i = 0; i < this->length - 1; i++)
                {
                    temp->next = new ListSequence<TElement>;
                    temp = temp->next;
                    temp->value = rand();
                    cout << temp->value << " ";
                }
                cout << endl;
            }

            if (choice == '2')
            {
                ListSequence<TElement> *ctemp;
                if (this->length != 0)
                {
                    temp->value = rand();
                    cout << temp->value << " ";
                }
                for (int i = 0; i < this->length - 1; i++)
                {
                    temp->next = new ListSequence<TElement>;
                    ctemp = temp;
                    temp = temp->next;
                    temp->value = rand();
                    while (temp->value < ctemp->value)
                    {
                        temp->value = temp->value + (rand() % 10);
                    }
                    cout << temp->value << " ";
                }
                cout << endl;
            }

            if (choice == '3')
            {
                ListSequence<TElement> *ctemp;
                if (this->length != 0)
                {
                    temp->value = rand();
                    cout << temp->value << " ";
                }
                for (int i = 0; i < this->length - 1; i++)
                {
                    temp->next = new ListSequence<TElement>;
                    ctemp = temp;
                    temp = temp->next;
                    temp->value = rand();
                    while (temp->value > ctemp->value)
                    {
                        temp->value = temp->value - (rand() % 10);
                    }
                    cout << temp->value << " ";
                }
                cout << endl;
            }
        }
    }

    string TypeofSequence()
    {
        return "ListSequence";
    }

    void Print()
    {
        ListSequence *temp = head;
        for (int i = 0; i < this->length; i++)
        {
            cout << temp->value << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    void Swap(int first, int second)
    {
        ListSequence *temp = head;
        ListSequence *ctemp = head;
        for (int i = 0; i < first; i++)
            temp = temp->next;
        for (int i = 0; i < second; i++)
            ctemp = ctemp->next;
        TElement tp = temp->value;
        temp->value = ctemp->value;
        ctemp->value = tp;
    }

    TElement Get(int index)
    {
        while (index < 0 || index >= this->length)
        {
            cout << "������� ���������� ��������!" << endl;
            cin >> index;
        }
        ListSequence *temp = head;
        for (int i = 0; i < index; i++)
        {
            temp = temp->next;
        }
        return temp->value;
    }

    TElement GetFirst()
    {
        return head->value;
    }

    TElement GetLast()
    {
        ListSequence *temp = head;
        for (int i = 0; i < head->length - 1; i++)
        {
            temp = temp->next;
        }
        return temp->value;
    }

    void GetSubsequence(int StartIndex, int EndIndex)
    {
        while (StartIndex < 0 || StartIndex > EndIndex || EndIndex >= this->length)
        {
            cout << "������� ���������� ��������!" << endl;
            cin >> StartIndex >> EndIndex;
        }
        for (int i = 0; i < StartIndex; i++)
            head = head->next;
        this->length = EndIndex - StartIndex + 1;
    }

    void Append(TElement item)
    {
        ListSequence *temp = head;
        if (this->length == 0)
        {
            head->value = item;
            head->length = 1;
        }
            else
            {
                for (int i = 0; i < head->length - 1; i++)
                    temp = temp->next;
                temp->next = new ListSequence<TElement>;
                temp = temp->next;
                temp->value = item;
                head->length = head->length + 1;
            }
    }

    void Prepend(TElement item)
    {
        ListSequence *temp = new ListSequence<TElement>;
        temp->next = head->next;
        temp->value = head->value;
        head->next = temp;
        head->value = item;
        head->length = head->length + 1;
    }

    void InsertAt(int index, TElement item)
    {
        while (index < 0 || index >= this->length)
        {
            cout << "������� ���������� ��������!" << endl;
            cin >> index;
        }
        ListSequence *tempitem = new ListSequence<TElement>;
        ListSequence *ctemp = new ListSequence<TElement>;
        if (index == 0)
        {
            tempitem->value = head->value;
            head->value = item;
            ctemp = head->next;
            head->next = tempitem;
            tempitem->next = ctemp;

        }
        if (index != 0)
        {
            ListSequence *temp = head;
            for (int i = 0; i < index - 1; i++)
                temp = temp->next;
            ctemp = temp->next;
            temp->next = tempitem;
            tempitem->next = ctemp;
            tempitem->value = item;
        }
        head->length = head->length + 1;
    }

    void Remove(TElement item)
    {
        ListSequence *temp = head;
        ListSequence *NLsequence = new ListSequence<TElement>;
        ListSequence *cNLsequence = NLsequence;
        int size = this->length;
        for (int i = 0; i < size; i++)
        {
            if (temp->value != item)
            {
                NLsequence->value = temp->value;
                NLsequence->next = new ListSequence<TElement>;
                NLsequence = NLsequence->next;
            }
            if (temp->value == item)
            {
                this->length = this->length - 1;
            }
            temp = temp->next;
        }
        head->value = cNLsequence->value;
        head->next = cNLsequence->next;
    }
};

template<typename TElement>
class Sort
{
public:
    void QuickSort(Sequence<TElement> *s_arr, int first, int last)
    {
        if (first < last)
        {
            int left = first, right = last, index = (left + right) / 2, middle = s_arr->Get(index);
            do
            {
                while (s_arr->Get(left) < middle) left++;
                while (s_arr->Get(right) > middle) right--;
                if (left <= right)
                {
                    s_arr->Swap(left, right);
                    left++;
                    right--;
                }
            } while (left <= right);
            QuickSort(s_arr, first, right);
            QuickSort(s_arr, left, last);
        }
    }

    void InsertionSort(Sequence<TElement> *s_arr, int length)
    {
        int temp, item;
        for (int i = 1; i < length; i++)
        {
            temp = s_arr->Get(i);
            item = i - 1;
            while(item >= 0 && s_arr->Get(item) > temp)
            {
                s_arr->Swap(item, item + 1);
                item--;
            }
        }
    }
};

double GetTime(function<void()> foo)
{
    double start_time = clock();
    foo();
    double end_time = clock();
    return (end_time - start_time) / CLOCKS_PER_SEC;
}

template<typename TElement>
void ChecktheCorrect(Sequence<TElement> *sequence)
{
    TElement input;
    int check = 0;
    cout << "���������� ���������: " << endl;
    for (int i = 0; i < sequence->GetLength(); i++)
    {
        cin >> input;
        cout << input << " ";
        if (input != sequence->Get(i))
            check = check + 1;
    }

    if (check != 0)
        cout << endl << "����� �������� �� �����" << endl;
        else
            cout << endl << "����� �������� �����" << endl;
}

template<typename TElement>
class Interface
{
public:
    Interface(bool mode)
    {
        srand(clock());
        cout << "������� ����� ������������������: " << endl;
        int length;
        cin >> length;
        if (mode == true)
            cout << length << endl;
        cout << "�������� ��� ������������������:" << endl;
        cout << "1. Array Sequence" << endl;
        cout << "2. List Sequence" << endl;
        char choice_type;
        cin >> choice_type;
        if (mode == true)
            cout << choice_type << endl;
        cout << "������������� ������������������? (Y/N)" << endl;
        char choice_rand;
        cin >> choice_rand;
        if (mode == true)
            cout << choice_rand << endl;
        if (choice_type == '1')
        {
            if (choice_rand == 'Y')
            {
                ArraySequence<TElement> seq(length, true);
                Interface<TElement> interface(&seq, mode);
            }

            if (choice_rand == 'N')
            {
                ArraySequence<TElement> seq(length, false);
                Interface<TElement> interface(&seq, mode);
            }
        }

        if (choice_type == '2')
        {
            if (choice_rand == 'Y')
            {
                ListSequence<TElement> seq(length, true);
                Interface<TElement> interface(&seq, mode);
            }

            if (choice_rand == 'N')
            {
                ListSequence<TElement> seq(length, false);
                Interface<TElement> interface(&seq, mode);
            }
        }
    }

    Interface(Sequence<TElement> *sequence, bool mode)
    {
        cout << "�������� ����������� �����:" << endl;
        cout << "1. Length" << endl;
        cout << "2. IsEmpty" << endl;
        cout << "3. Get" << endl;
        cout << "4. GetFirst" << endl;
        cout << "5. GetLast" << endl;
        cout << "6. GetSubsequence" << endl;
        cout << "7. Append" << endl;
        cout << "8. Prepend" << endl;
        cout << "9. InsertAt" << endl;
        cout << "10. Remove" << endl;
        cout << "11. Quick Sort" << endl;
        cout << "12. Insertion Sort" << endl;
        cout << "13. �������� ����� ����������" << endl;
        int choice;
        while (1 < 2)
        {
            cin >> choice;
            if (mode == true)
                cout << choice << endl;
            if (choice == 1)
            {
                cout << "����� ������������������: ";
                cout << sequence->GetLength() << endl;
            }

            if (choice == 2)
            {
                cout << "������������������ ������: ";
                if (sequence->GetIsEmpty() == 1)
                    cout << "��" << endl;
                if (sequence->GetIsEmpty() == 0)
                    cout << "���" << endl;
            }

            if (choice == 3)
            {
                cout << "������� ������ ��������" << endl;
                int index;
                cin >> index;
                if (mode == true)
                    cout << index << endl;
                cout << "������� ������������������: ";
                cout << sequence->Get(index) << endl;
            }

            if (choice == 4)
            {
                cout << "������ ������� ������������������:" << endl;
                cout << sequence->GetFirst() << endl;
            }

            if (choice == 5)
            {
                cout << "��������� ������� ������������������:" << endl;
                cout << sequence->GetLast() <<endl;
            }

            if (choice == 6)
            {
                cout << "������� ��������� � �������� ������ ���������������������:" << endl;
                int StartIndex, EndIndex;
                cin >> StartIndex >> EndIndex;
                if (mode == true)
                    cout << StartIndex << " " << EndIndex << endl;
                cout << "���������� ���������������������: ";
                sequence->GetSubsequence(StartIndex, EndIndex);
                sequence->Print();
            }

            if (choice == 7)
            {
                cout << "������� �������������� ������� ������������������:" << endl;
                TElement item;
                cin >> item;
                if (mode == true)
                    cout << item << endl;
                cout << "����� ������������������: ";
                sequence->Append(item);
                sequence->Print();
            }

            if (choice == 8)
            {
                cout << "������� �������������� ������� ������������������:" << endl;
                TElement item;
                cin >> item;
                if (mode == true)
                    cout << item << endl;
                cout << "����� ������������������: ";
                sequence->Prepend(item);
                sequence->Print();
            }

            if (choice == 9)
            {
                cout << "������� ������ ��������:" << endl;
                int index;
                cin >> index;
                if (mode == true)
                    cout << index << endl;
                cout << "������� �������������� ������� ������������������:" << endl;
                TElement item;
                cin >> item;
                if (mode == true)
                    cout << item << endl;
                cout << "����� ������������������: ";
                sequence->InsertAt(index, item);
                sequence->Print();
            }

            if (choice == 10)
            {
                cout << "������� ������� ������������������:" << endl;
                TElement item;
                cin >> item;
                if (mode == true)
                    cout << item << endl;
                cout << "���������� ������������������: ";
                sequence->Remove(item);
                if (sequence->GetLength() != 0 )
                    sequence->Print();
                if (sequence->GetLength() == 0 )
                    cout << "������ ������������������" << endl;
            }

            Sort<TElement> ssort;
            if (choice == 11)
            {
                cout << "�������� ����� ����������? (Y/N): " << endl;
                char get_time_choice;
                cin >> get_time_choice;
                if (mode == true)
                    cout << get_time_choice << endl;
                if (get_time_choice == 'N')
                {
                    ssort.QuickSort(sequence, 0, sequence->GetLength() - 1);

                }
                if (get_time_choice == 'Y')
                {
                    function<void()> f  = [&ssort, sequence](){
                                                                ssort.QuickSort(sequence, 0, sequence->GetLength() - 1);
                                                              };
                    double time = GetTime(f);
                    cout << "����� ���������� ����������: " << time << endl;
                }
                cout << "��������������� ������������������:" << endl;
                sequence->Print();
                if (mode == true)
                    ChecktheCorrect<TElement>(sequence);
            }

            if (choice == 12)
            {
                cout << "�������� ����� ����������? (Y/N): " << endl;
                char get_time_choice;
                cin >> get_time_choice;
                if (mode == true)
                    cout << get_time_choice << endl;
                if (get_time_choice == 'N')
                    ssort.InsertionSort(sequence, sequence->GetLength());

                if (get_time_choice == 'Y')
                {
                    function<void()> f = [&ssort, sequence](){
                                                                ssort.InsertionSort(sequence, sequence->GetLength());
                                                              };
                    double time = GetTime(f);
                    cout << "����� ���������� ����������: " << time << endl;
                }
                cout << "��������������� ������������������:" << endl;
                sequence->Print();
                if (mode == true)
                    ChecktheCorrect<TElement>(sequence);
            }

            if (choice == 13)
            {
                if (sequence->TypeofSequence() == "ArraySequence")
                {
                    ArraySequence<TElement> copy_arr(0, false);
                    for (int i = 0; i < sequence->GetLength(); i++)
                        copy_arr.Append(sequence->Get(i));
                    double time_quicksort = GetTime([&ssort, sequence](){
                                                                ssort.QuickSort(sequence, 0, sequence->GetLength() - 1);
                                                                    });
                    double time_insertionsort = GetTime([&ssort, &copy_arr](){
                                                                        ssort.InsertionSort(&copy_arr, copy_arr.GetLength());
                                                                    });
                    cout << "���������� ���������: "<< copy_arr.GetLength() << endl;
                    cout << "����� ���������� Quick Sort: " << time_quicksort << endl;
                    cout << "����� ���������� Insertion Sort: " << time_insertionsort << endl;
                    cout << "������� ������� ����������: " << time_quicksort - time_insertionsort << endl;
                }

                if (sequence->TypeofSequence() == "ListSequence")
                {
                    ListSequence<TElement> copy_arr(0, false);
                    for (int i = 0; i < sequence->GetLength(); i++)
                        copy_arr.Append(sequence->Get(i));
                    double time_quicksort = GetTime([&ssort, sequence](){
                                                                ssort.QuickSort(sequence, 0, sequence->GetLength() - 1);
                                                                    });
                    double time_insertionsort = GetTime([&ssort, &copy_arr](){
                                                                        ssort.InsertionSort(&copy_arr, copy_arr.GetLength());
                                                                    });
                    cout << "���������� ���������: "<< copy_arr.GetLength() << endl;
                    cout << "����� ���������� Quick Sort: " << time_quicksort << endl;
                    cout << "����� ���������� Insertion Sort: " << time_insertionsort << endl;
                    cout << "������� ������� ����������: " << time_quicksort - time_insertionsort << endl;
                    if (mode == true)
                        ChecktheCorrect<TElement>(sequence);
                }
            }

            if (mode == true)
            {
                char button;
                cout << "��� ����������� ������� ����� �������..." << endl;
                button = getch();
            }

            cout << "�������� ����������� �����:" << endl;
        }
    }
};


class User
{
public:
    User()
    {
        cout << "�������� ��� ������:" << endl;
        cout << "1. int" << endl;
        cout << "2. double" << endl;
        cout << "3. char" << endl;
        char choice;
        cin >> choice;
        if (choice == '1')
            Interface<int> interface(false);

        if (choice == '2')
            Interface<double> interface(false);

        if (choice == '3')
            Interface<char> interface(false);
    }
};

class Tester
{
public:
    Tester()
    {
        cout << "�������� ����:" << endl;
        cout << "1. ������������ ����������" << endl;
        cout << "2. ������������ ������� Sequence" << endl;
        char choice;
        cin >> choice;
        if (choice == '1')
            freopen("tests/test_sort.txt", "r", stdin);
        if (choice == '2')
            freopen("tests/test_sequence.txt", "r", stdin);
        Interface<int> interface(true);
        freopen("CONIN$", "r", stdin);

    }
};

int main()
{
    setlocale(0, "Russian");
    cout << "�������� ����� ������:" << endl;
    cout << "1. ������������" << endl;
    cout << "2. �����������" << endl;
    char choice;
    cin >> choice;
    if (choice == '1')
        User user;
    if (choice == '2')
        Tester tester;

    return 0;
}
