// Copyright 2026 bguliano and erin-owens

#include<iostream>
#include"dynamicarray.h"
using std::ostream;
using std::cout;
using std::cin;
using std::endl;

char DynamicArray::delimiter_ = ' ';

/* The << operator (not a member of the class, can be a friend). Should output all of
the values in the array. The operator should output the static delimiter character
between each pair of values in the array. */

ostream& operator << (ostream& whereto, const DynamicArray& arr) {
    for (int i = 0; i <= arr.GetSize() - 1; ++i) {
        whereto << arr.values_[i];

        if (i != arr.GetSize() - 1) {
            whereto << arr.GetDelimiter();
        }
    }
    return whereto;
}

/* The == operator that returns true if the operands are the same size and contain
exactly the same values in the same positions. */

bool DynamicArray::operator == (const DynamicArray& right) const {
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

/* An AllUnique function that returns true if all of the values in the array are
unique, and false if any value in the array is duplicated. */
bool DynamicArray::AllUnique() const {
    for (int i = 0; i < size_; ++i) {
        for (int j = i+1; j < size_; ++j) {
            if (values_[i] == values_[j]) {
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
    if (copyCount == size_) {
        SetSize(1, false);
    }
    int * temp = new int[newSize];
    for (int i = 0; i < newSize; ++i) {
        if (values_[i] != toRemove) {
            temp[i] = values_[i];
        }
    }
    delete[] values_;
    values_ = temp;
    size_ = newSize;
    return copyCount;
}

void DynamicArray::Insert(int toAdd, int index) {
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
    CopyHelper(0, index - 1, temp);

    temp[index] = toAdd;
    CopyHelper(index + 1, size_, temp);
    delete[] values_;
    values_ = temp;
    }
    size_++;
}

void DynamicArray::CopyHelper(int start, int end, int * ptr) {
    for (int i = start; i < end; ++i) {
        ptr[i] = values_[i];
    }
}



int main() {
  int s = 10;
  DynamicArray a(s);
  cout << "Initial array of " << s << " elements: " << a << endl;
  DynamicArray::SetDelimiter(',');
  cout << "Here they are with commas between the values " << a << endl;
  DynamicArray::SetDelimiter(' ');

  // My test for insert
  int toAdd, index;
  cout << "Enter a value you would like to insert: " << endl;
  cin >> toAdd;
  cout << "At what index does this value belong?: " << endl;
  cin >> index;

  a.Insert(toAdd, index);
  cout << toAdd << " was added to index " << index
  << ". Updated array: " << a << endl;



  cout << "Enter " << s << " new values to hold in the array: ";
  for ( int i = 0; i < a.GetSize(); ++i )
    cin >> a[i];
  cout << "Updated array: " << a << endl;
  if ( a.AllUnique() )
    cout << "All the values in the array are unique" << endl;
  else
    cout << "The array contains duplicate values" << endl;
  const DynamicArray kOriginal(a);  // keeping a copy to use later

  int added_positions;
  cout << "How many elements do you want to add to the end of the array? ";
  cin >> added_positions;
  a.SetSize(a.GetSize() + added_positions);
  cout << "Updated array: " << a << endl;
  int new_size;
  cout << "Enter a new size for the array: ";
  cin >> new_size;
  char keep_vals;
  cout << "Do you want to keep the currently values in the array? "
       << "(enter y or n) ";
  cin >> keep_vals;
  a.SetSize(new_size, keep_vals == 'y');
  cout << "Updated array: " << a << endl;
  int find, replace;
  cout << "Enter a value to find in the array ";
  cin >> find;
  cout << "What do you want to replace this value with? ";
  cin >> replace;
  int how_many = a.FindAndReplace(find, replace);
  cout << "Replaced " << how_many << " " << find << "s with "
       << replace << "s" << endl;
  cout << "Updated array: " << a << endl;
  cout << "Enter a value to remove from the array ";
  cin >> find;
  how_many = a.RemoveAll(find);
  cout << "Removed " << how_many << " values." << endl;
  cout << "Updated array: " << a << endl;
  a.RemoveDuplicates();
  cout << "Here's the array with all duplicates removed: " << a << endl;

  cout << "\n\nEnter y (actually any non-whitespace character will do) "
       << "when you're ready to see some copy and change tests. " << endl;
  cin >> keep_vals;

  DynamicArray acopy(a);
  cout << "Here's a copy of the array " << acopy << endl;
  cout << (acopy == a ? "the copy matches the original\n" :
           "OH NO!! They don't match!!!\n") << endl;
  cout << "Now I'm going to cut the size of the original array in half\n";
  a.SetSize(a.GetSize() / 2);
  cout << "Here's the array that's been cut in half " << a << endl;
  cout << "And here's the copy that was made before cutting it in half: "
       << acopy << endl;
  cout << "Now I'll reset the original to the copy." << endl;
  a = acopy;
  cout << "a = " << a << "\nacopy = " << acopy << endl;
  cout << (acopy == a ? "the copy matches the original\n" :
           "OH NO!! They don't match!!!\n") << endl;
  cout << "And now I'll add a couple values to the end of the copy ";
  acopy.SetSize(acopy.GetSize() + 2);
  acopy[acopy.GetSize() - 1] = acopy[acopy.GetSize() - 2] = 99;
  cout << "Here's the changed array " << acopy << endl;
  cout << "And here's the original " << a << endl;

  acopy = kOriginal;
  cout << "\n\nHere's a copy of the array with the values you entered at the "
       << "very beginning: " << acopy << endl;
  acopy.Sort();
  cout << "Here is the array after sorting the values in ascending order: "
       << acopy << endl;
  acopy.Sort(true);
  cout << "Here is the arry after sorting the values in descending order: "
       << acopy << endl;

  return 0;
}
