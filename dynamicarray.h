// Copyright ECO1, bguliano, bhipp

#include<ostream>

using std::ostream;



class DynamicArray {
friend ostream& operator << (ostream&, const DynamicArray&);
public:
    bool operator == (const DynamicArray& right) const;

    int GetSize() const;

    void SetSize(int newSize, bool ifCopy = true);

    bool AllUnique (const DynamicArray& arr) const;

    int RemoveAll (int toRemove);

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
    static char delimiter_; // (for separator used by <<)
};
