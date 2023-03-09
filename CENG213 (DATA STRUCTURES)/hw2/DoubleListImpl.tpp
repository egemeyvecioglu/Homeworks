#pragma once

#include "DoubleList.tpp"

template <typename T>
DoubleList<T>::DoubleList(T *a, unsigned n) : DoubleList()
{

  for(unsigned i=0;i<n;i++)
  {
    this->insert(a[i],i,i);	
  }

}

template <typename T>
DoubleList<T>::DoubleList(const DoubleList<T> &dl): DoubleList()
{

  if(dl.head(Red))
  {
    Node *temp;
    Node *newRedHead=new Node;
    Node *newBlueHead=nullptr;
    temp = dl.head(Red);
    newRedHead->mValue=temp->value();
    mHead[Red] = newRedHead;
    temp = temp->next(Red);
    Node *prev = mHead[Red];

    while(temp)
    {
      Node *newNode = new Node;
      newNode->mValue = temp->value();
      prev->mNext[Red] = newNode;
      if(prev->mValue == (dl.head(Blue)->value()))newBlueHead=prev;
      temp=temp->next(Red);
      prev=prev->next(Red);
    }
    prev->mNext[Red]=nullptr;
    if(prev->mValue == (dl.head(Blue)->value()))newBlueHead=prev;
    mHead[Blue] = newBlueHead;
    prev = mHead[Blue];
    temp = (dl.head(Blue))->next(Blue);

    while(temp)
    {
      Node* temp_red=mHead[Red];
      while(temp_red)
      {
        if(temp->value()==temp_red->value())
        {
          prev->mNext[Blue]=temp_red;
          break;
        }
        temp_red=temp_red->next(Red);
      }
      temp=temp->next(Blue);
      prev=prev->next(Blue);
    }
    prev->mNext[Blue]=nullptr;
  }
}

template <typename T>
typename DoubleList<T>::Node *DoubleList<T>::get(unsigned index,
                                                 Color color) const 
{
  Node *temp=mHead[color];
  if(index<0 || !temp) throw InvalidIndexException();
  while(index--)
  {
    if(temp->next(color)==nullptr)
    {
      throw InvalidIndexException();
    }
    temp=temp->mNext[color];
  }
  return temp;
}

template <typename T>
typename DoubleList<T>::Node *DoubleList<T>::insert(T value, unsigned redIndex,
                                                    unsigned blueIndex) 
{
  Node *newNode=new Node;
  newNode->mValue= value;
  newNode->mNext[Red]=nullptr;
  newNode->mNext[Blue]=nullptr;
  Node *temp1,*temp2;
  try
  {
    if(redIndex!=0) temp1=get(redIndex-1,Red);
    if(blueIndex!=0)temp2=get(blueIndex-1,Blue);


    if(redIndex!=0)
    {
      newNode->mNext[Red]=temp1->mNext[Red];
      temp1->mNext[Red]=newNode;
    }
    else
    {
      if(mHead[Red])
      {
        Node *tmp;
        tmp=mHead[Red];
        newNode->mNext[Red]=tmp;
        mHead[Red]=newNode;
      }
      else mHead[Red]=newNode;
    }

    if(blueIndex!=0)
    {
      newNode->mNext[Blue]=temp2->mNext[Blue];
      temp2->mNext[Blue]=newNode;
    }
    
    else
    {
      if(mHead[Blue])
      {
        Node *tmp;
        tmp=mHead[Blue];
        newNode->mNext[Blue]=tmp;
        mHead[Blue]=newNode;
      }
      else mHead[Blue]=newNode;
    }


  }
  catch(InvalidIndexException &)
  {
    delete newNode;
    throw InvalidIndexException();
  }
  
  return newNode;
}

template <typename T>
void DoubleList<T>::remove(unsigned index, Color color)
{
    Node *temp;
    try
    {
      get(index,color);
    }
    catch(InvalidIndexException&)
    {
      throw InvalidIndexException();
    }

    if(mHead[color])
    {
      if(index == 0 )
      {
        temp=mHead[color];
        mHead[color]=mHead[color]->mNext[color];
      }

      else
      {
        Node *prev;
        prev = get(index-1,color);
        temp=prev->mNext[color];
        prev->mNext[color]=temp->mNext[color];

      }

      unsigned new_color=(color+1)%2;
      Node *temp2=mHead[new_color];
      if(temp2==temp)
      {
        mHead[new_color]=temp->mNext[new_color];
        delete temp;
      }
      else
      {
        while(temp2)
        {
          if(temp2->mNext[new_color]==temp)
          {
              temp2->mNext[new_color]=temp2->mNext[new_color]->mNext[new_color];
              delete temp;
              break;
          }
          temp2=temp2->mNext[new_color];
        }
      }

    }
}


template <typename T>
void DoubleList<T>::append(DoubleList<T> &dl)
{
  Node *tmp1,*tmp2;
  int i=0;
  while(i<2 && dl.mHead[i])
  {
    tmp1=mHead[i];tmp2=dl.mHead[i];
    if(!mHead[i]) 
    {
      mHead[i] =tmp2;
      tmp2=tmp2->mNext[i];
      tmp1=mHead[i];
    }
    else
    {
      while(tmp1->mNext[i])
      {
        tmp1=tmp1->mNext[i];
      }
    }

    while(tmp2)
    {
      tmp1->mNext[i]=tmp2;
      tmp1 = tmp1->mNext[i];
      tmp2=tmp2->mNext[i];
    }
    i++;
  }
  dl.mHead[Red]=nullptr;
  dl.mHead[Blue]=nullptr;
}

template <typename T>
DoubleList<T>::~DoubleList()
{

    Node *temp=nullptr;	
    while(mHead[Red])
    {
      temp = mHead[Red];
      mHead[Red]=mHead[Red]->next(Red);
      delete temp;
    }
    
}