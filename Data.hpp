struct data
{   
    public:
    int array[100];
    size_t size;
    data():size(0){}
    data(int* _array,size_t _size):size(_size)
    {   
        for (size_t i=0; i<size; i++)
        {
            array[i]=_array[i];
        }
    }
};