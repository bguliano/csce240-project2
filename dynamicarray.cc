// Copyright 2026 bguliano and erin-owens

#include<iostream>
#include"dynamicarray.h"
using std::ostream;

/* The << operator (not a member of the class, can be a friend). Should output all of
the values in the array. The operator should output the static delimiter character
between each pair of values in the array. */

ostream& operator << (ostream& whereto, const DynamicArray& arr){
    for(int i = 0; i <= arr.GetSize() - 1; ++i) {
        whereto << arr.values_[i];

        if(i != arr.GetSize() - 1) {
            whereto << arr.GetDelimeter();
        }
    }
    return whereto;
}

/* The == operator that returns true if the operands are the same size and contain
exactly the same values in the same positions. */

bool DynamicArray::operator == (const DynamicArray& right) const {
    if(size_ != right.size_) {
        return false;
    }
    // now loop through each array to check value for value
    for(int i = 0; i < size_; ++i){
        if(values_[i] != right.values_[i]) {
            return false;
        }
    }
    return true;
}

// A GetSize function that returns the current size of the array.
int DynamicArray::GetSize() const {
    return size_;
}

/* A SetSize function that takes an integer parameter for the updated size, and a bool
parameter for whether or not to copy the existing values into the updated array. The
bool parameter should default to true. If decreasing the size and copying the
values, copy over the values that will fit from the beginning of the array (the
ending values are not copied over). If increasing the size and copying the values,
the additional values should all be 0. */

// if you are NOT copying values, just make new block of memory, then plug leak
// if you ARE copying values...
// then update size
void DynamicArray::SetSize(int newSize, bool isCopy) {
    if(newSize < 1) {
        newSize = 1;
        isCopy = false;
    }

    // Since valid input, allocate mem
    int * temp = new int[newSize];      
    if(!isCopy) { 
        for(int i = 0; i < newSize; ++i) {
            temp[i] = 0;
        }
    } else {
        int smaller = (size_ < newSize) ? size_ : newSize;
        CopyHelper(0, smaller, temp);
        
        // Now fill rest with 0s
        for(int i = smaller; i < newSize; ++i) {
            temp[i] = 0;
        }
    }
    delete[] values_;
    values_ = temp;
    size_ = newSize;
}

/* An AllUnique function that returns true if all of the values in the array are
unique, and false if any value in the array is duplicated. */
bool DynamicArray::AllUnique() const {
    for(int i = 0; i < size_; ++i){
        for(int j = i+1; j < size_; ++j) {
            if(values_[i] == values_[j]) {
                return false;
            }
        }
    }
    return true;
}


/* A RemoveAll function that takes an int parameter. The function should remove all
occurrences of that value in the array, resizing the array to an exact fit for the
remaining elements. The function should return the number of copies of the value it
found and removed. If every value in the array matches the value that’s to be
removed, the resulting array should have size 1, and hold a single 0 in that one
position. */

// note: ^ this function should utilize SetSize funct
int DynamicArray::RemoveAll(int toRemove) {
    int copyCount = 0;
    int newSize = size_;
    for (int i = 0 ; i < size_; ++i) {
        if (values_[i] == toRemove) {
            ++copyCount;
            --newSize;
            continue;
        }
    }
    if(copyCount == size_) {
        SetSize(1, false);
    }
    int * temp = new int[newSize];
    for(int i = 0; i < newSize; ++i){
        if(values_[i] != toRemove) {
            temp[i] = values_[i];
        }
    }
    delete[] values_;
    values_ = temp;
    size_ = newSize;
}

void DynamicArray::Insert(int toAdd, int index) {
    // validate index: must be greater than 0
    // leave it the same if invalid index
    if(index < 0){
        return;
    }
    if (index > size_) {
        SetSize(index + 1, true);
        // this copies values, then sets all extra values to 0
        // now change target index to toAdd
        values_[index] = toAdd;
    }
    // make new array of size + 1
    // copy values to index -1
    // insert toAdd at index
    // finish copying over for index +1 to end
    int * temp = new int[size_ + 1];
    CopyHelper(0, index - 1, temp);

    temp[index] = toAdd;
    CopyHelper(index + 1, size_, temp);

    delete[] values_;
    values_ = temp;
    size_ ++;
}


// probs want a copy helper 
void DynamicArray::CopyHelper(int start, int end, int * ptr) {
    for(int i = start; i < end; ++i) {
        ptr[i] = values_[i];
    }
}
