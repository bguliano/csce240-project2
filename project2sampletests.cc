// Copyright 2026 bhipp
// run some tests on the DynamicArray class written for CSCE240H
#include<iostream>
using std::cout;
using std::endl;
using std::cin;
#include"dynamicarray.h"

int main() {
  int s = 10;
  DynamicArray a(s);
  cout << "Initial array of " << s << " elements: " << a << endl;
  DynamicArray::SetDelimeter(',');
  cout << "Here they are with commas between the values " << a << endl;
  DynamicArray::SetDelimeter(' ');
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
