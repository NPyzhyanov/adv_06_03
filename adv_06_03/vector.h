#ifndef VECTOR_H
#define VECTOR_H

#define ELONGATION_RATE 1.5
#define RESETTING_RATIO 0.9

template <class Type>
class Vector
{
private:
    Type* p_begin;
    int capacity;
    int size;
    
public:
    
    Vector<Type>()
    {
        capacity = 1;
        size = 0;
        p_begin = new Type[capacity];
    }
    
    Vector<Type>(int capacity_)
    {
        if (capacity_ < 1)
        {
            throw std::invalid_argument("Vector capacity cannot be less than 1");
        }
        size = 0;
        capacity = capacity_;
        p_begin = new Type[capacity];
    }
    
    Vector<Type>(int size_, Type value)
    {
        if (size_ < 0)
        {
            throw std::invalid_argument("Vector size cannot be less than 0");
        }
        size = size_;
        capacity = (size_ == 0 ? 1 : size_);
        p_begin = new Type[capacity];
        for (int i = 0; i < size; i++)
        {
            p_begin[i] = value;
        }
    }
    
    Vector<Type>(const Vector<Type>& vector_to_copy)
    {
        capacity = vector_to_copy.capacity;
        size = vector_to_copy.size;
        p_begin = new Type[capacity];
        for (int i = 0; i < size; i++)
        {
            p_begin[i] = vector_to_copy.p_begin[i];
        }
    }
    
    Vector<Type>& operator=(const Vector<Type>& right)
    {
        if (&right == this)
        {
            return *this;
        }
        Vector<Type> tmp_vector = right;
        swap_fields(tmp_vector);
        return *this;
    }
    
    ~Vector()
    {
        delete[] p_begin;
        p_begin = nullptr;
    }
    
    Type& at(int index)
    {
        if (index < 0 || index >= size)
        {
            throw std::out_of_range("Vector::at(int index): invalid argument");
        }
        return p_begin[index];
    }

    void push_back(Type value)
    {
        if (capacity <= size)
        {
            int new_capacity = static_cast<int>(round(static_cast<double>(capacity) * ELONGATION_RATE));
            Vector<Type> new_vector(this, new_capacity);
            swap_fields(new_vector);
        }
        p_begin[size] = value;
        size++;
    }

    int get_size()
    {
        return size;
    }

    int get_capacity()
    {
        return capacity;
    }
    
    void pop_back()
    {
        if (size < 1)
        {
            return;
        }
        size--;
        if ((static_cast<double>(size) / static_cast<double>(capacity)) < (RESETTING_RATIO / ELONGATION_RATE))
        {
            this->shrink_to_fit();
        }
    }

    void shrink_to_fit()
    {
        if (capacity <= size || size < 1)
        {
            return;
        }
        Vector<Type> new_vector(this, size);
        swap_fields(new_vector);
    }
    
    void print()
    {
        std::string default_separator = " ";
        this->print(default_separator);
    }
    
    void print(std::string separator)
    {
        for (int i = 0; i < size; i++)
        {
            std::cout << p_begin[i] << separator;
        }
        for (int i = size; i < capacity; i++)
        {
            std::cout << "_" << separator;
        }
        std::cout << std::endl;
    }
    
private:
    Vector<Type>(Vector<Type>* p_vector_to_copy, int updated_capacity)
    {
        if (updated_capacity < p_vector_to_copy->size || updated_capacity < 1)
        {
            throw std::logic_error("Not enough capacity for copying this vector");
        }
        size = p_vector_to_copy->size;
        capacity = updated_capacity;
        p_begin = new Type[capacity];
        for (int i = 0; i < size; i++)
        {
            p_begin[i] = p_vector_to_copy->at(i);
        }
    }
    
    void swap_fields(Vector<Type>& source_object)
    {
        Type* tmp_ptr = p_begin;
        int tmp_capacity = capacity;
        int tmp_size = size;
        
        p_begin = source_object.p_begin;
        capacity = source_object.capacity;
        size = source_object.size;
        
        source_object.p_begin = tmp_ptr;
        source_object.capacity = tmp_capacity;
        source_object.size = tmp_size;
    }
};

#endif // VECTOR_H
