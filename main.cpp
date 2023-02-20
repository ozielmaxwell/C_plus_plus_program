#include <iostream>

using namespace std;


class Queue
{
    private: 
        int* Contents;
        int Queue_size;
        int Front, Back;
    public:
        //constructor function with default int of 5
        Queue (int Queue_size = 5);
        ~Queue(); //destructor
        bool Empty() const;
        bool Full() const;
        bool Remove(int& front_element);
        bool Add(const int& new_element);
        void Display() const;

};


//constructor function
Queue::Queue(int queue_size) :
    Queue_size(queue_size),
    Contents(new int[queue_size + 1]),
    Front(0), Back(0)
{};

//destructor function
Queue::~Queue()
{
    delete[] Contents;
}

//function to check empty queue
bool Queue::Empty() const
{
    return (Front == Back) ? true : false;
}

//function to check full
bool Queue::Full() const
{
    return ((Back + 1) % (Queue_size + 1) == Front) ? true : false;
}

//function to remove element from the queue
bool Queue::Remove(int& front_element)
{
    if (Empty())
    {
        return false;
    }
    else
    {
        front_element = Contents[Front];
        Front = (Front + 1) % (Queue_size + 1);
        return true;
    }
}

//function to add elemt to a queue
bool Queue::Add(const int& new_element)
{
    if (Full())
    {
        return false;
    }
    else
    {
        Contents[Back] = new_element;
        Back = (Back + 1) % (Queue_size + 1);
        return true;
    }
}

//function to display the element in a queue
void Queue::Display() const
{
    if (Empty())
    {
        cout << "The queue is empty. Therefore nothing to display" << endl;
        return;
    }
    else
    {
        int i = Front;
        cout << "Below is the content of the Queue:" << endl;
        while (i != Back)
        {
            cout << Contents[i];  cout << " ";
            i = (i + 1) % (Queue_size + 1);
        }
        cout << endl;

    }
};

int main()
{
    int q_size;
    cout << "Welcome! what is the Queue size you want to use for this operation?" << endl;
    cin >> q_size;
    
    Queue my_queue(q_size);
    char choice;
    int i;

    cout << "What operation do you want to perform? \nEnter 'a' to Add, \nEnter 'r' to Remove, \nEnter 'd' to Display and \nEnter 'q' to to exit the program " << endl;
    cin >> choice;

    while (choice != 'q')
    {
        switch (choice)
        {
        case 'a':
            cout << "Enter new element: ";
            cin >> i;
            if (my_queue.Add(i))
                cout << "Element Added succefully" << endl;
            else
                cout << "Queue is full please, delete some data" << endl;
            break;

        case 'r':
            if (my_queue.Remove(i))
                cout << "Element " << i << " removed succefully" << endl;
            else
                cout << "Queue is empty please, add some data before removing" << endl;
            break;

        case 'd':
            my_queue.Display();
            break;

        default:
            cout << "Ivalid request please try again" << endl;
            break;
        }
        // this line will keep prompting the user for the right input
        cin >> choice;
    }
    return 0;

}