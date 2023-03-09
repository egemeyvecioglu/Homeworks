#pragma once

#include "Iterable.tpp"
#include <queue>
//*****************************************
//                REPEAT
//*****************************************

using std::queue;

template<typename T>
class RepeatIterator : public IIterator<T>
{
    private:
        T mNum;
    public:
        RepeatIterator(T v):mNum(v)
        {
        }

        virtual T next()
        {
            return mNum;
        }

        virtual ~RepeatIterator()
        {
        }
};


template<typename T>
class RepeatIterable : public IIterable<T>
{
    private:
        T V;
    public:

        RepeatIterable(T v):V(v)
        {

        }

        virtual IIterator<T> * iter() const
        {
            return new RepeatIterator<T>(V);
        }

        virtual ~RepeatIterable() {}
};


template<typename T>
IIterable<T> * repeat(T v)
{   
    return new RepeatIterable<T>(v);
}



//*****************************************
//                COUNT
//*****************************************

template<typename T>
class CountIterator : public IIterator<T>
{
    private:
        T mNum,mDelta;
    public:
        CountIterator(T v,T d):mNum(v),mDelta(d)
        {
        }

        virtual T next()
        {
            int k=mNum;
            mNum+=mDelta;
            return k;
        }

        virtual ~CountIterator()
        {

        }
};


template<typename T>
class CountIterable : public IIterable<T>
{
    private:
        T mv,md;
    public:

        CountIterable(T v,T d):mv(v),md(d)
        {
        }

        virtual IIterator<T> * iter() const
        {
            return new CountIterator<T>(mv,md);
        }

        virtual ~CountIterable() {}
};



template<typename T>
IIterable<T> * count(T start, T delta)
{
    return new CountIterable<T>(start,delta);
}


//*****************************************
//                SKIP
//*****************************************

template<typename T>
class SkipIterator : public IIterator<T>
{
    private:
        unsigned mSkipCounter;
        IIterator<T> *mIterator;
    public:
        SkipIterator(unsigned k,IIterator<T> *iterator) :mSkipCounter(k),
                                                        mIterator(iterator)
        {
        }

        virtual T next()
        {  
            while(mSkipCounter)
            {   
                mIterator->next();
                mSkipCounter--;
            }
            return mIterator->next();
        }

        virtual ~SkipIterator()
        {
            delete mIterator;
        }
};

template<typename T>
class SkipIterable : public IIterable<T>
{
    private:
        unsigned K;
        IIterable<T> *mIterable;
    public:
        SkipIterable(unsigned k,IIterable<T> *iterable) :K(k),mIterable(iterable)
        {
            
        }

        virtual IIterator<T> * iter() const
        {   
            return new SkipIterator<T>(K,mIterable->iter());
        }

        virtual ~SkipIterable()
        {
            delete mIterable;
        }
};

template<typename T>
IIterable<T> * skip(unsigned k,IIterable<T> *i)
{
    return new SkipIterable<T>(k,i); 
}



//*****************************************
//                TAKE
//*****************************************


template<typename T>
class TakeIterator: public IIterator<T>
{
    private:
        unsigned mCount;
        IIterator<T> *mIterator;
    public:
        TakeIterator(IIterator<T> *iterator,unsigned k):mCount(k), 
                                                        mIterator(iterator)
        {
        }

        virtual T next()
        {   
            if(mCount>0)
            {
                mCount--;
                return mIterator->next();
            }
            else throw StopIteration();
        }

        virtual ~TakeIterator()
        {
            delete mIterator;
        }
};


template<typename T>
class TakeIterable : public IIterable<T>
{
    private:
        unsigned K;
        IIterable<T> *mIterable;

    public:
        TakeIterable(unsigned k,IIterable<T> *iterable) :K(k),mIterable(iterable)
        {   
        }

        virtual IIterator<T> * iter() const
        {   
            return new TakeIterator<T>(mIterable->iter(),K);
        }

        virtual ~TakeIterable()
        {
            delete mIterable;
        }
};



template<typename T>
IIterable<T> * take(unsigned k, IIterable<T> *i)
{
    
    return new TakeIterable<T>(k, i);
}


//*****************************************
//                CYCLE
//*****************************************

template<typename T>
class CycleIterator : public IIterator<T>
{
    private:
        IIterator<T> *mIterator;
        queue<T> q;
    public:
        CycleIterator(IIterator<T> *iterator) : mIterator(iterator)
        {
        }

        virtual T next()
        {  
            try
            {   
                T a= mIterator->next();
                q.push(a);
                return a;
            }
            catch(StopIteration &)
            {   if(!q.empty())
                {
                q.push(q.front());
                q.pop();
                return(q.back());
                }
                else throw StopIteration();
            }
        }

        virtual ~CycleIterator()
        {   
            while(!q.empty())q.pop();
            delete mIterator;
        }
};

template<typename T>
class CycleIterable : public IIterable<T>
{
    private:
        IIterable<T> *mIterable;
    public:
        CycleIterable(IIterable<T> *iterable) :mIterable(iterable)
        {
        }

        virtual IIterator<T> * iter() const
        {   
            return new CycleIterator<T>(mIterable->iter());
        }

        virtual ~CycleIterable()
        {
            delete mIterable;
        }
};

template<typename T>
IIterable<T> * cycle(IIterable<T> *i)
{
    return new CycleIterable<T>(i); 
}



//*****************************************
//                CONCAT
//*****************************************


template<typename T>
class ConcatIterator : public IIterator<T>
{
    private:
        IIterator<T> *mIterator1;
        IIterator<T> *mIterator2;
    public:
        ConcatIterator(IIterator<T> *iterator1,IIterator<T> *iterator2) :
                                                        mIterator1(iterator1),
                                                        mIterator2(iterator2)
        {
        }

        virtual T next()
        {  
            try
            {
                return mIterator1->next();
            }
            catch(StopIteration &)
            {
                return mIterator2->next();
            }
            
        }

        virtual ~ConcatIterator()
        {
            delete mIterator1;
            delete mIterator2;
        }
};

template<typename T>
class ConcatIterable : public IIterable<T>
{
    private:
        IIterable<T> *mIterable1;
        IIterable<T> *mIterable2;
    public:
        ConcatIterable(IIterable<T> *iterable1,IIterable<T> *iterable2):mIterable1(iterable1),
                                                                        mIterable2(iterable2)
        {
            
        }

        virtual IIterator<T> * iter() const
        {   
            return new ConcatIterator<T>(mIterable1->iter(),mIterable2->iter());
        }

        virtual ~ConcatIterable()
        {
            delete mIterable1;
            delete mIterable2;
        }
};

template<typename T>
IIterable<T> * concat(IIterable<T> *i, IIterable<T> *j)
{
    return new ConcatIterable<T>(i,j); 
}


//*****************************************
//                ALTERNATE
//*****************************************
template<typename T>
class AlternateIterator : public IIterator<T>
{
    private:
        unsigned k=0;
        IIterator<T> *mIterator1;
        IIterator<T> *mIterator2;
    public:
        AlternateIterator(IIterator<T> *iterator1,IIterator<T> *iterator2) :
                                                        mIterator1(iterator1),
                                                        mIterator2(iterator2)
        {
        }

        virtual T next()
        {  
            try
            {   
                return k++%2==0?mIterator1->next():mIterator2->next();
            }
            catch(StopIteration &)
            {
                try
                {
                    return mIterator1->next();
                }
                catch(StopIteration &)
                {
                    return mIterator2->next();
                }
                
            }
            
        }

        virtual ~AlternateIterator()
        {
            delete mIterator1;
            delete mIterator2;
        }
};

template<typename T>
class AlternateIterable : public IIterable<T>
{
    private:
        IIterable<T> *mIterable1;
        IIterable<T> *mIterable2;
    public:
        AlternateIterable(IIterable<T> *iterable1,IIterable<T> *iterable2):mIterable1(iterable1),
                                                                        mIterable2(iterable2)
        {
            
        }

        virtual IIterator<T> * iter() const
        {   
            return new AlternateIterator<T>(mIterable1->iter(),mIterable2->iter());
        }

        virtual ~AlternateIterable()
        {
            delete mIterable1;
            delete mIterable2;
        }
};

template<typename T>
IIterable<T> * alternate(IIterable<T> *i, IIterable<T> *j)
{
    return new AlternateIterable<T>(i,j); 
}

//*****************************************
//                FILTER
//*****************************************

template<typename T>
class FilterIterator : public IIterator<T>
{
    private:
        unsigned k=0;
        IIterator<T> *mIterator1;
        IIterator<bool> *mIterator2;
    public:
        FilterIterator(IIterator<T> *iterator1,IIterator<bool> *iterator2) :
                                                        mIterator1(iterator1),
                                                        mIterator2(iterator2)
        {
        }

        virtual T next()
        {  
            while(!(mIterator2->next())) mIterator1->next();
            return mIterator1->next();
        }

        virtual ~FilterIterator()
        {
            delete mIterator1;
            delete mIterator2;
        }
};

template<typename T>
class FilterIterable : public IIterable<T>
{
    private:
        IIterable<T> *mIterable1;
        IIterable<bool> *mIterable2;
    public:
        FilterIterable(IIterable<T> *iterable1,IIterable<bool> *iterable2): mIterable1(iterable1),
                                                                            mIterable2(iterable2)
        {
            
        }

        virtual IIterator<T> * iter() const
        {   
            return new FilterIterator<T>(mIterable1->iter(),mIterable2->iter());
        }

        virtual ~FilterIterable()
        {
            delete mIterable1;
            delete mIterable2;
        }
};

template<typename T>
IIterable<T> * filter(IIterable<T> *i, IIterable<bool> *f)
{
    return new FilterIterable<T>(i,f); 
}