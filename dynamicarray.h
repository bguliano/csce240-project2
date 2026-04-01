// Copyright 2026 bguliano and erin-owens

#ifndef DYNAMICARRAY_H_
#define DYNAMICARRAY_H_

#include<ostream>

using std::ostream;

class DynamicArray {
friend ostream& operator << (ostream&, const DynamicArray&);

 public:
    explicit DynamicArray(int size = 1) :
            size_(size > 0 ? size : 1), values_(new int[size_]()) {
        for (int i = 0; i < size_; i++) values_[i] = 0;
    }

    explicit DynamicArray(const DynamicArray &copy_from) :
            size_(copy_from.size_), values_(new int[size_]) {
        for (int i = 0; i < size_; i++) values_[i] = copy_from.values_[i];
    }

    bool operator == (const DynamicArray& right) const;

    int GetSize() const;

    void SetSize(int newSize, bool isCopy = true);

    bool AllUnique() const;

    int RemoveAll(int toRemove);

    void Insert(int toAdd, int index);

    void CopyHelper(int start, int end, int * ptr);

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

    static void SetDelimiter(char delimiter) {
        delimiter_ = delimiter;
    }

    static char GetDelimiter() {
        return delimiter_;
    }

    int FindAndReplace(const int search, const int replace) {
        int numReplaced = 0;
        for (int i = 0; i < size_; i++) {
            if (values_[i] == search) {
                values_[i] = replace;
                numReplaced++;
            }
        }
        return numReplaced;
    }

    int NumUnique() {
        int uniqueCount = 0;

        for (int i = 0; i < size_; i++) {
            bool foundEarlier = false;

            for (int j = 0; j < i; j++) {
                if (values_[j] == values_[i]) {
                    foundEarlier = true;
                    break;
                }
            }

            if (!foundEarlier) uniqueCount++;
        }
        return uniqueCount;
    }

    void RemoveDuplicates() {
        int uniqueCount = NumUnique();
        int *newValues = new int[uniqueCount];
        int newIndex = 0;

        for (int i = 0; i < size_; i++) {
            bool foundEarlier = false;

            for (int j = 0; j < i; j++) {
                if (values_[j] == values_[i]) {
                    foundEarlier = true;
                    break;
                }
            }

            if (!foundEarlier) {
                newValues[newIndex] = values_[i];
                newIndex++;
            }
        }

        delete[] values_;
        values_ = newValues;
        size_ = uniqueCount;
    }

    void Sort(bool descending = false) {
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
    static char delimiter_;  // (for separator used by <<)
};

#endif  // DYNAMICARRAY_H_
