// Copyright 2026 bguliano and erin-owens

#ifndef DYNAMICARRAY_H_
#define DYNAMICARRAY_H_

using std::ostream;

class DynamicArray {
friend ostream& operator << (ostream& whereto, const DynamicArray& arr) {
    for (int i = 0; i <= arr.GetSize() - 1; ++i) {
        whereto << arr.values_[i];

        if (i != arr.GetSize() - 1) {
            whereto << arr.GetDelimiter();
        }
    }
    return whereto;
}

public:
    explicit DynamicArray(int size = 1) : size_(size > 0 ? size : 1), values_(new int[size_]()) {
        for (int i = 0; i < size_; i++) values_[i] = 0;
    }

    explicit DynamicArray(const DynamicArray &copy_from) : size_(copy_from.size_), values_(new int[size_]) {
        for (int i = 0; i < size_; i++) values_[i] = copy_from.values_[i];
    }

    bool operator == (const DynamicArray& right) const {
    if (size_ != right.size_) {
        return false;
    }
    // now loop through each array to check value for value
    for (int i = 0; i < size_; ++i) {
        if (values_[i] != right.values_[i]) {
            return false;
        }
    }
    return true;
}

    int GetSize() const {
    return size_;
}

    void SetSize(int newSize, bool isCopy = true) {
    if (newSize < 1) {
        newSize = 1;
        isCopy = false;
    }

    // Since valid input, allocate mem
    int * temp = new int[newSize];
    if (!isCopy) {
        for (int i = 0; i < newSize; ++i) {
            temp[i] = 0;
        }
    } else {
        int smaller = (size_ < newSize) ? size_ : newSize;
        CopyHelper(0, smaller, temp);

        // Now fill rest with 0s
        for (int i = smaller; i < newSize; ++i) {
            temp[i] = 0;
        }
    }
    delete[] values_;
    values_ = temp;
    size_ = newSize;
}

    bool AllUnique() const {
    for (int i = 0; i < size_; ++i) {
        for (int j = i+1; j < size_; ++j) {
            if (values_[i] == values_[j]) {
                return false;
            }
        }
    }
    return true;
}

    int RemoveAll(int toRemove) {
    int copyCount = 0;
    int newSize = size_;
    for (int i = 0 ; i < size_; ++i) {
        if (values_[i] == toRemove) {
            ++copyCount;
            --newSize;
            continue;
        }
    }
    if (copyCount == size_) {
        SetSize(1, false);
    }
    int * temp = new int[newSize];
    for (int i = 0; i < newSize; ++i) {
        if (values_[i] != toRemove) {
            temp[i] = values_[i];
        }
        if (values_[i] == toRemove) {
            for (int j = i; j < newSize; ++j) {
                temp[j] = values_[j+1];
            }
            break;
        }
    }
    delete[] values_;
    values_ = temp;
    size_ = newSize;
    return copyCount;
}

    void Insert(int toAdd, int index) {
    // validate index: must be greater than 0
    // leave it the same if invalid index
    if (index < 0) {
        return;
    }
    if (index > size_) {
        SetSize(index + 1, true);
        // this copies values, then sets all extra values to 0
        // now change target index to toAdd
        values_[index] = toAdd;
    } else {
        // make new array of size + 1
    // copy values to index -1
    // insert toAdd at index
    // finish copying over for index +1 to end
    int * temp = new int[size_ + 1];
    CopyHelper(0, index, temp);

    temp[index] = toAdd;
    CopyHelper(index + 1, size_, temp);
    for (int i = index +1; i <= size_; ++i) {
        temp[i] = values_[i-1];
    }
    delete[] values_;
    values_ = temp;
    }
    size_++;
}

    void CopyHelper(int start, int end, int * ptr) {
    for (int i = start; i < end; ++i) {
        ptr[i] = values_[i];
    }
}

    // same from HourlyTemperature.h
    DynamicArray &operator=(const DynamicArray &copy_from) {
        size_ = copy_from.size_;
        delete[] values_;

        values_ = new int[size_];
        for (int i = 0; i < size_; i++) values_[i] = copy_from.values_[i];
        return *this;
    }

    ~DynamicArray() {
        delete[] values_;
    }

    // char delimiter_ = ' ';

    static void SetDelimiter(char delimiter = ' ') {
        delimiter_ = delimiter;
    }

    static char GetDelimiter() {
        return delimiter_;
    }

    int FindAndReplace(const int search, const int replace) {
        int numReplaced = 0;

        // iterate over each value to find "search"
        for (int i = 0; i < size_; i++) {

            // if found, replace, and increment counter per instructions
            if (values_[i] == search) {
                values_[i] = replace;
                numReplaced++;
            }
        }
        return numReplaced;
    }

    int NumUnique() {
        int uniqueCount = 0;

        // iterate over each element in array again
        for (int i = 0; i < size_; i++) {
            // reset found flag
            bool foundEarlier = false;

            // iterate over the remaining numbers and look for equality to the current one (i)
            for (int j = 0; j < i; j++) {
                if (values_[j] == values_[i]) {
                    foundEarlier = true;
                    break;
                }
            }

            // if found flag is set, update uniqueCount
            if (!foundEarlier) uniqueCount++;
        }
        return uniqueCount;
    }

    void RemoveDuplicates() {
        // let's just set up a new values array with the size, which we can grab from the number of unique values
        int uniqueCount = NumUnique();
        int *newValues = new int[uniqueCount];
        int newIndex = 0;

        // iterate over the entire int array, per usual
        for (int i = 0; i < size_; i++) {
            bool foundEarlier = false;

            // if this int has been seen beforehand, set flag to skip
            for (int j = 0; j < i; j++) {
                if (values_[j] == values_[i]) {
                    foundEarlier = true;
                    break;
                }
            }

            // otherwise, add value to newValues array
            if (!foundEarlier) {
                newValues[newIndex] = values_[i];
                newIndex++;
            }
        }

        // delete and replace int pointer array
        delete[] values_;
        values_ = newValues;
        size_ = uniqueCount;
    }

    void Sort(bool descending = false) {
        // iterate over the array again, but one less so we can compare the next element
        // at the end of the array
        for (int i = 0; i < size_ - 1; i++) {
            // compare each pair of adjacent values
            for (int j = 0; j < size_ - i - 1; j++) {
                // swap if values are out of order for ascending sort,
                // or swap in the opposite case if descending
                if (values_[j] > values_[j + 1] || (descending && values_[j] < values_[j + 1])) {
                    int temp = values_[j];
                    values_[j] = values_[j + 1];
                    values_[j + 1] = temp;
                }
            }
        }
    }

    // version that allows one to use the operator in a non-constant setting
    // to update the values in the array
    int &operator[](int i) {
        if (i >= 0 && i < size_) return values_[i];
        if (i < 0) return values_[0];
        return values_[size_ - 1];
    }

    // version that allows one to use the operator on a constant array
    // returning copies of a value in the array
    int operator[](int i) const {
        if (i >= 0 && i < size_) return values_[i];
        if (i < 0) return values_[0];
        return values_[size_ - 1];
    }

private:
    int size_;
    int *values_;
    inline static char delimiter_ = ' ';  // (for separator used by <<)
};

#endif  // DYNAMICARRAY_H_
