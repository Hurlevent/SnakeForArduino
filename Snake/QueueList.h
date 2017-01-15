#ifndef QUEUELIST_H
#define QUEUELIST_H

/*
* This is my custom data structure that is a combinations of a Queue and a List.
*/
template<class T>
class QueueList {
  public:

    /*
    * Constructor
    */
    QueueList() {
      m_buffer_size = 32; // starting buffer size
      m_items = new T[m_buffer_size];
      m_length = 0;
      m_beginning = 0;
      m_end = 0;
    }

    /*
    * Destructor
    */
    ~QueueList() {
      delete[] m_items;
    }
    /*
    * returns the number of elements in the QueueList.
    */
    int size() {
      return m_length;
    }
    
    /*
     * IMPORTANT! DO NOT DEQUEUE WHEN THE QUEUELIST IS EMPTY!
     *  
     *  This function removes and returns the first element in the QueueList.
     */
    T dequeue() {
      T ret_object = m_items[m_beginning++];
      --m_length;

      // Check for wrap-around
      if (m_beginning > m_buffer_size) {
        m_beginning -= (m_buffer_size + 1);
      }
      return ret_object;
    }

    /*
    * Adds a new element in the QueueList, it also dynamically reallocates more memory when needed
    */
    void enqueue(T item) {
      if (m_length == m_buffer_size) {
        int old_buff_size = m_buffer_size;
        m_buffer_size *= 2;
        T * temp = new T[m_buffer_size];
        for (int i = 0; i < m_length; ++i) {
          int index = (m_beginning + i) > (old_buff_size - 1) ? (m_beginning + i) - (old_buff_size + 1) : m_beginning + i;
          temp[i] = m_items[index];
        }
        delete[] m_items;
        m_items = temp;
        m_beginning = 0;
        m_end = m_length;
      }

      m_items[m_end++] = item;
      ++m_length;

      // Check for wrap-around
      if (m_end > m_buffer_size) {
        m_end -= (m_buffer_size + 1);
      }
    }

    /*
    * Returns a spesific element in the QueueList
    */
    T get(int i) {
      // Check for wrap around
      if (m_beginning + i > m_buffer_size) {
        i -= m_buffer_size + 1;
      }

      return m_items[m_beginning + i];
    }

    /*
    * Returns the first element in the QueueList
    */
    T first() {
      return m_items[m_beginning];
    }

    /*
    * Returns the last element in the QueueList
    */
    T last() {
      return m_items[m_end];
    }

    /*
    * Used to change a spesific element in the QueueList
    */
    void set(T item, int i) {
      // Check for wrap around
      if (m_beginning + i > m_buffer_size) {
        i -= m_buffer_size + 1;
      }

      m_items[m_beginning + i] = item;
    }

    /*
    * This function makes deletes all elements and completely resets the QueueList
    */
    void reset() {
      delete[] m_items;
      m_buffer_size = 32;
      m_items = new T[m_buffer_size];
      m_length = 0;
      m_beginning = 0;
      m_end = 0;
    }

  private:
    T * m_items;
    int m_length;
    int m_buffer_size;
    int m_beginning; // points to the front of the queue
    int m_end; // points to the back of the queue
};

#endif // QUEUELIST_H
