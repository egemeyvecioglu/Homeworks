#pragma once
template<typename T>
class EHeap
{
    
    private:
        class HandleData
        {
            friend EHeap;
            private:
                T mValue;
                unsigned index;
        };

        const unsigned mCapacity;
        unsigned mSize;
        T *mHeap;
        HandleData** handles;
        
        void swap(unsigned a, unsigned b)
        {
            T temp1;
            HandleData* temp2;

            temp1=mHeap[a];
            mHeap[a]=mHeap[b];
            mHeap[b]=temp1;

            handles[a]->index=b;
            handles[b]->index=a;

            temp2=handles[a];
            handles[a]=handles[b];
            handles[b]=temp2;

            temp2=nullptr;delete temp2;

        }

        unsigned percolateUp(unsigned i)
        {

            while (i > 1  && mHeap[i / 2] >= mHeap[i])
            {
                unsigned  k= i / 2;
                swap(k, i);
                i = k;
            }
            return i;
        }

        void percolateDown(unsigned i)
        {
            while (2 * i <= mSize)
            {
                unsigned minChild;

                if (2 * i + 1 <= mSize and mHeap[2 * i + 1] < mHeap[2 * i])
                {
                    minChild = 2 * i + 1;
                }
                else
                {
                    minChild = 2 * i;
                }

                if (mHeap[minChild] < mHeap[i])
                {
                    swap(minChild, i);
                    i = minChild;
                }
                else
                {
                    break;
                }
            }
        }


    public:
        typedef HandleData * Handle;
        EHeap(unsigned capacity): mCapacity(capacity),
                                  mSize(0), 
                                  mHeap(new T[capacity + 1]),
                                  handles(new HandleData*[capacity+1])
                                  {
                                        for(unsigned i=0;i<=capacity;i++) handles[i]= new HandleData;
                                  }

        unsigned size() const {return mSize;}

        Handle push(T t)
        {
            unsigned k;
            mSize++;
            handles[mSize]->mValue=t;
            handles[mSize]->index=mSize;
            mHeap[mSize] = t;
            k=percolateUp(mSize);
            return handles[k];
        }

        T pop()
        {
            T popped = mHeap[1];
            swap(1, mSize);
            mSize--;
            percolateDown(1);
            return popped;
        }

    
        T erase(Handle handle)
        {
            T erased = handle->mValue;
            unsigned a=handle->index;
            swap(handle->index,mSize);
            mSize--;
            percolateDown(a);

            return erased;
        }

        ~EHeap()
        {
            delete [] mHeap; 
            for(unsigned i=0;i<=mCapacity;i++)
            {
                delete handles[i];
            }
            delete [] handles;
        }
};
