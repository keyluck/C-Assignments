#include<iostream>
using namespace std;


//----------------------------------------
//CS311 HW2P2 Partition
//Name: Nick Luckey
//Compiler: g++
//-----------------------------------------

// partitions the array a into smaller than pivot and others.
// f is the beginning of the section to be partitioned
// r is the end of the section to be partitioned
// return the first slot of the Large section
int partition(int pivot, int a[], int f, int r)
{
  int beg = f; // elements starting from the left
  int end = r; // elements starting from the right 

  //while loop until beg reaches end
  while(beg<end)
    {
      //if beg's element is on correct side, go to next element
      while(a[beg]<pivot && beg <= end)
	beg+=1;
      //if end's element is on correct side, go to next element
      while(a[end]>=pivot && end>beg)
	end-=1;
      //if beg is still less than end, then beg and end need to swap
      if(beg<end)
	{
	  f=a[beg];
	  a[beg++]=a[end];
	  a[end--]=f;
	}

    }
  // return the partition point where
  // those smaller than pivot are before what is returned
  if(a[f]==pivot) //if f==pivot then pivot never moves from index 0, no elements were swapped, and there is no small section
    return 1;
  else
    return beg; //beg has partition point where values to the left are smaller than pivot
}

int main()
{
  int x;  // number of elements
  int nums[10];
  cout << "How many elements? (must be less than 10) "; 
  cin >> x;
  cout << "Enter elements one per line.." << endl;
  for (int i = 0; i < x; i++)
    { cin >> nums[i]; }

  // the pivot is always the first element
  cout << "Ok the pivot is " << nums[0] << endl;

  int part = partition(nums[0], nums, 0, x-1);

  cout << "Results..." << endl;
  // display up to the partition without endl
  for (int i = 0; i < part; i++)
    cout << nums[i];

  cout << "|";
  // display from the partition on.. without endl
  for (int i = part; i < x; i++)
    cout << nums[i];

  cout << endl;

}
