

using namespace std;

template <typename T>
class Deque
{
    // Write a "Friend" function that overloads the "<<"" operator, and can be used to "cout" a deque.
    // Read about friend functions. Note that friend functions have access to private, public and 
    // protected members!
    friend ostream& operator<<(ostream& out, const Deque& dq)
    { 
        // TODO: Complete the overloading function. 
        // HINT: You just have to populate the ostream (output stream) with the members of the deque
        // array! Look at the testcases to see how the print should look like
        T* arr = dq.arr;
        if (dq.size == 0) {
            return out;
        }
        for(int i=dq.index_front; i<dq.index_front+dq.size; i++){
            out << arr[i%dq.capacity] << " ";
        }
        return out; // dummy
    }

protected:
    // TODO: Suitably initialize the queue parameters (Feel free to add any other variables as needed) 
    T* arr = NULL;
    int capacity = 5;
    int resize_factor = 2;
    int size = 0;
    int index_front = 0;
    int index_back = -1;
    bool auto_resize = true;

public:
    Deque(int cap, bool resize = true, int resize_factor = 2) 
    {       
        // TODO: Implement the constructor that initializes the Deque with a given capacity
        // and optionally the resize factor  
        auto_resize = resize;
        capacity = cap;
        this->resize_factor = resize_factor;
        arr = new T[capacity];                                  
    }

    Deque(bool resize = true, int resize_factor = 2)
    {
        // TODO: Implement the constructor that initializes the Deque with a default capacity
        // and optionally given the resize factor
        arr = new T[capacity];
        auto_resize = resize;
        this->resize_factor = resize_factor;
    }

    Deque(const Deque& dq)
    {
        // TODO: Implement the copy constructor for the Deque. 
        // What you need to do is copy the contents of the Deque object dq to the new Deque object
        // being instantiated.
        capacity = dq.capacity;
        resize_factor = dq.resize_factor;
        size = dq.size;
        index_front = dq.index_front;
        index_back = dq.index_back;
        auto_resize = dq.auto_resize;
        arr = new T[capacity];
        for(int i=index_front; i<index_front+size; i++)
        {
            arr[i%capacity] = dq.arr[i%capacity];
        }
    }

    ~Deque()
    {
       // TODO: Implement the destructor
       delete[] arr;
    }

    void print()
    {
        // TODO: Implement a print function similar to the << overload. You can cout the values. Look at the testcases to see how the print output should look
        for(int i=index_front; i<index_front+size; i++)
        {
            cout << arr[i%capacity] << " ";
        }
        cout << endl;
    }

    bool is_empty()
    {
        // TODO: Implement the is_empty method to check if the deque is empty
      if(size == 0) return true;
      else return false; // DUMMY RETURN
    } 

    int get_capacity()
    {
        // TODO: Implement a getter for the capacity of the Deque
      return capacity; // DUMMY RETURN
    }

    int get_size()
    {
        // TODO: Implement a getter for the size of the Deque
      return size; // DUMMY RETURN
    }
// ATTENTION !!
// We DO NOT want to use Deque as a data structure for the purpose of this lab,
// but want to be able to inherit it's functions selectively and create our 
// Stack and Queue. Therefore, we do not make the following functions public.
protected:

    bool push_back(T data)
    {
        // TODO: Implement the push_back method to push the data into the back of the deque
        // If the deque is full and auto_resize is true, scale the capacity of the deque
        // Returns true if push succeds else returns false
        if (size >= capacity)
        {
            if(auto_resize == false)
                return 0;
            else 
            {   
                capacity = resize_factor*capacity;
                T* arr2 = arr;
                arr = new(nothrow) T[capacity];
                if(!arr) 
                    return 0;
                for(int i=index_front; i<index_front+size; i++)
                {
                    arr[i-index_front] = arr2[i%capacity];
                }
                index_back=size;
                index_front=0;
                arr[size] = data;
                size++;
                delete[] arr2;
                arr2 = NULL;
            }
        }
        else
        {
            index_back = (index_back+1)%capacity;
            arr[index_back] = data;
            size++;
        }
        return 1;
    }

    T pop_front()
    {
        // TODO: Implement the pop_front method to pop the data from the front of the deque
        // Throw exception if the deque is empty
      if(is_empty())
          throw std::underflow_error("Deque is empty");

      T num_pop = arr[index_front];
      index_front = (index_front+1)%capacity;
      size--;
      return num_pop; // DUMMY RETURN
    }

//Returns true if push succeds else returns false
    bool push_front(T data)
    {
        // TODO: Implement the push_front method to push the data into the front of the deque
        // If the deque is full and auto_resize is true, scale the capacity of the deque
        // Returns true if push succeds else returns false
      if (size >= capacity)
        {
            if(auto_resize == false)
                return 0;
            else 
            {   
                capacity = resize_factor*capacity;
                T* arr2 = arr;
                arr = new(nothrow) T[capacity];
                if(!arr) 
                    return 0;
                for(int i=index_front; i<index_front+size; i++)
                {
                    arr[i-index_front+1] = arr2[i%capacity];
                }
                index_back=size;
                index_front=0;
                arr[0] = data;
                size++;
                delete[] arr2;
                arr2 = NULL;
            }
        }
        else
        {
            index_front = (index_front-1+capacity)%capacity;
            arr[index_front] = data;
            size++;
        }
        return 1; //DUMMY RETURN
    }

    T pop_back()
    {
        // TODO: Implement the pop_back method to pop the data from the back of the deque
        // Throw exception if the deque is empty
      if(is_empty())
          throw std::underflow_error("Deque is empty");

      T num_pop = arr[index_back];
      index_back = (index_back-1+capacity)%capacity;
      size--;
      return num_pop; // DUMMY RETURN
    }

    T peek_front()
    {
        // TODO: Implement the peek_front method to return the front element of the deque
        // Throw exception if the deque is empty
      if(is_empty())
      {
          throw std::underflow_error("Deque is empty");
      }
      return arr[index_front]; // DUMMY RETURN
    }

    T peek_back()
    {
        // TODO: Implement the peek_back method to return the last element of the deque
        // Throw exception if the deque is empty
        if(is_empty())
        {
            throw std::underflow_error("Deque is empty");
        }
        return arr[index_back];
    }
};

// Before you go on to this part, read about class inheritance and understand the 3 types below:

// Public inheritance: public->public, protected->protected
// Protected inheritance: public->protected, protected->protected
// Private inheritance (default): public->private, protected->private

// To access private members of the base class, you need to declare derived class as a friend class

// Now, create the Queue class, and you must derive it from Deque. Why implement everything again!

template<typename T>
class Queue : public Deque<T>
{
    // TO THINK: Do we need a similar friend function to overload << as Deque? 
    // Or will Queue inherit it from Deque?
public:
    // TODO: Inherit the constructor that initializes the queue with a given capacity
    // and optionally the resize factor from Deque
    Queue(int cap, bool resize = true, int resize_factor = 2) 
        : Deque<T>(cap, resize, resize_factor) 
    {}

    // TODO: Inherit the constructor that initializes the queue with a default capacity
    // and optionally given the resize factor from Deque
    Queue(bool resize = true, int resize_factor = 2)
        : Deque<T>(resize, resize_factor) 
    {}

    // TODO: Write a custom copy constructor for the Queue. It must take a const reference to a
    // Queue object and copy its contents to the new Queue object being created.
    // HINT: You can use the copy constructor of the Deque class to copy the contents of the Deque
    Queue(const Queue& q)
        : Deque<T>(q)
    {}
    // NOTE: Since Queue inherits from Deque, and Deque already has a destructor that correctly
    // deallocates the dynamic array arr, you don't need to write an additional destructor for Queue 

    // TODO: Make the (protected) member functions from Deque that are needed publicly by a 
    // Queue as Public members
    // HINT: do it by "using"


  // ------------------------------------------
  // The following functions are added to ensure initial compilation
  // Remove the following dummy functions once you implement the above functions
  //-------------------------------------------
  bool push(T data) {
      return this->push_back(data);
  }

  using Deque<T>::push_back;
  using Deque<T>::pop_front;
  using Deque<T>::peek_front;

};

// Now, create the Stack class, and you must derive it from Deque. Why implement everything again!


template<typename T>
class Stack : public Deque<T>
{
public:
    // TODO: Inherit the constructor that initializes the queue with a given capacity
    // and optionally the resize factor from Deque
    Stack(int cap, bool resize = true, int resize_factor = 2) 
        : Deque<T>(cap, resize, resize_factor) 
    {}

    // TODO: Inherit the constructor that initializes the queue with a default capacity
    // and optionally given the resize factor from Deque
    Stack(bool resize = true, int resize_factor = 2)
        : Deque<T>(resize, resize_factor) 
    {}

    // TODO: Write a custom copy constructor for the Stack. It must take a const reference to a
    // Stack object and copy its contents to the new Stack object being created.
    // HINT: You can use the copy constructor of the Deque class to copy the contents of the Deque
    Stack(const Stack& q)
        : Deque<T>(q)
    {}
    // NOTE: Since Stack inherits from Deque, and Deque already has a destructor that correctly
    // deallocates the dynamic array arr, you don't need to write an additional destructor for Stack 

    // TODO: Make the (protected) member functions from Deque that are needed publicly by a 
    // Stack as Public members
    // HINT: do it by "using" the necessary functions

  // ------------------------------------------
  // The following functions are added to ensure initial compilation
  // Remove the following dummy functions once you implement the above functions
  //-------------------------------------------
  using Deque<T>::push_back;
    using Deque<T>::pop_back;
    using Deque<T>::peek_back;

};
