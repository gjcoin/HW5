#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

void BubbleSort(string *algorithm, const vector <int> vInput, vector <int> &vSort,
	int &nComparisons, int &nExchanges)
{
	nComparisons = 0;
	nExchanges = 0;
	*algorithm = "Bubble Sort";
	vSort = vInput;

	int num_elements = vSort.size();
	int i, j, temp;
	for (i = 1; i < num_elements; i++) // Number of passes
	{
		for (j = 0; j < num_elements - 1; j++)
		{
			nComparisons++;
			if (vSort[j] > vSort[j + 1]) //Compare successive elements
			{
				temp =vSort[j];
				vSort[j] = vSort[j + 1]; //Swap data[j] with data[j+1]
				vSort[j + 1] = temp;
				nExchanges++;
			}
		}
	}
}

void InsertionSort(string *algorithm, const vector <int> vInput, vector <int> &vSort,
	int &nComparisons, int &nExchanges)
{
	nComparisons = 0;
	nExchanges = 0;
	*algorithm = "Insertion Sort";
	vSort = vInput;

	int num_elements = vSort.size();
	int i, j, element;
	for (i = 1; i < num_elements; i++)
	{
		element = vSort[i];
		j = i;
		while ((j > 0) && (vSort[j - 1] > element)) //Compare
		{
			nComparisons++;
			vSort[j] = vSort[j - 1];
			j = j - 1;
			nExchanges++;
		}
		vSort[j] = element;
	}
}

int partition(vector<int>& A, int left, int right, int who) {
	for (int i = left; i<right; ++i) {
		if (A[i] <= who) {
			swap(A[i], A[left]);
			left++;
		}
	}
	return left - 1;
}

void QuickSortB( vector <int> &vSort,int left, int right, int &nComparisons, int &nExchanges)
{
	int i = left, j = right;
	int tmp;
	int pivot = vSort[(left + right) / 2];
	
	/* partition */
	while (i <= j) {
		//Comparing sorts to pivots
		while (vSort[i] < pivot)
		{
			i++;
			nComparisons++;
		}	
		while (vSort[j] > pivot)
		{
			j--;
			nComparisons++;
		}
			
		if (i <= j) {
			tmp = vSort[i];
			vSort[i] = vSort[j]; //Exchange
			vSort[j] = tmp;
			i++;
			j--;
			nExchanges++;
		}
	};
	/* recursion */
	if (left < j)
		//Quick Sort left to j
		QuickSortB(vSort, left, j, nComparisons,nExchanges);

	if (i < right)
		//Quick Sort i to right
		QuickSortB(vSort, i, right, nComparisons, nExchanges);
}

void QuickSort(string *algorithm, const vector <int> vInput, vector <int> &vSort,
	int &nComparisons, int &nExchanges)
{
	nComparisons = 0;
	nExchanges = 0;
	*algorithm = "Quick Sort";
	vSort = vInput;
	QuickSortB(vSort, 0, vSort.size() - 1, nComparisons, nExchanges);
}

void ShellSort(string *algorithm, const vector <int> vInput, vector <int> &vSort,
	int &nComparisons, int &nExchanges)
{
	nComparisons = 0;
	nExchanges = 0;
	*algorithm = "Shell Sort";
	vSort = vInput;

	int gap = vSort.size() / 2;
	int swapped, temp;
	unsigned int i;
	do
	{
		do
		{
			swapped = 0;
			for (i = 0; i < (vSort.size() - gap); i++) {
				nComparisons++;
				if (vSort[i] > vSort[i + gap])
				{
					temp = vSort[i];
					vSort[i] = vSort[i + gap];
					vSort[i + gap] = temp;
					swapped = 1;
					nExchanges++;
				}
			}
		} while (swapped == 1);
	} while ((gap = gap / 2) >= 1);
}


void merge(vector <int> &vSort, const int low, const int mid, const int high, int &nComparisons, int &nExchanges)
{
	// Variables declaration. 
	int * b = new int[high + 1 - low];
	int h, i, j, k;
	h = low;
	i = 0;
	j = mid + 1;
	// Merges the two array's into b[] until the first one is finish
	while ((h <= mid) && (j <= high))
	{
		nComparisons++;
		//comparisons
		if (vSort[h] <= vSort[j])
		{
			b[i] = vSort[h];
			h++;
		}
		else
		{
			b[i] = vSort[j];
			j++;
		}
		i++;
	}
	// Completes the array filling in it the missing values
	if (h>mid)
	{
		for (k = j; k <= high; k++)
		{
			b[i] = vSort[k];
			i++;
		}
	}
	else
	{
		for (k = h; k <= mid; k++)
		{
			b[i] = vSort[k];
			i++;
		}
	}
	// Prints into the original array
	for (k = 0; k <= high - low; k++)
	{
		vSort[k + low] = b[k]; //exchange
		nExchanges++;
	}
	delete[] b;
}

void MergeSortB(vector <int> &vSort, const int low, const int high, int &nComparisons, int &nExchanges)		// Recursive sort ...
{
	int mid;
	if (low < high)
	{
		mid = (low + high) / 2;
		MergeSortB(vSort, low, mid, nComparisons, nExchanges);
		MergeSortB(vSort, mid + 1, high, nComparisons, nExchanges);
		merge(vSort, low, mid, high, nComparisons, nExchanges);
	}
}
void MergeSort(string *algorithm, const vector <int> vInput, vector <int> &vSort,
	int &nComparisons, int &nExchanges)
{
	nComparisons = 0;
	nExchanges = 0;
	*algorithm = "Merge Sort";
	vSort = vInput;
	MergeSortB(vSort, 0, vSort.size() - 1, nComparisons, nExchanges);
}

bool write_out_the_vector_to_file(vector<int> my_vector, string * my_file_name)
{
	ofstream out;
	out.open(*my_file_name);
	unsigned int i;
	for (i = 0; i<my_vector.size(); i++)
		out << my_vector[i] << endl;
	out.clear();
	out.close();
	return true;
}

typedef void(*sorter_function)(string *algorithm, const vector <int> input_table, vector <int> &sorted_table, 
	int &comparison_count, int &swap_count);


sorter_function sort_function_list[] = { BubbleSort, InsertionSort, QuickSort, ShellSort, MergeSort, NULL}; // sort_bubble, sort_insertion, sort_quick, sort_shell, sort_merge 


int main()
{
	int curInputNum = 0;
	string curOutputName;
	const string input_files[] = { "FewUnique.txt","NearlySorted.txt","Random.txt","Reversed.txt", "" };
	for (curInputNum=0; input_files[curInputNum].length() > 0; curInputNum++) {
		ifstream in;
		string line = "";
		int sortFuncNum = 0;
		vector<int> dataSet;
		in.open(input_files[curInputNum]);
		if (!in.is_open())
		{
			cout << "The read file " << input_files[curInputNum] << " could not be opened.\nCheck the location.\n";
			return false;
		}
		dataSet.clear();
		while (getline(in, line))
		{
			istringstream iss(line);
			int n;

			while (iss >> n) //Removes white space from integers
			{
				dataSet.push_back(n);
			}
		}
		in.clear(), in.close();
		for (sortFuncNum = 0; sort_function_list[sortFuncNum] != 0x0; sortFuncNum++) {
			string sortFuncName; 
			int nComparisons = 0; 
			int nSwaps = 0;
			vector<int> resultSet;
			(sort_function_list[sortFuncNum])(&sortFuncName, dataSet, resultSet, nComparisons, nSwaps);
			cout << input_files[curInputNum] << " " << sortFuncName << " results: " << "Comparisons = " << nComparisons << ", Swaps = " << nSwaps << endl;
			curOutputName = "Result_" + sortFuncName + "_" + input_files[curInputNum];
			write_out_the_vector_to_file(resultSet, &curOutputName);
			 
		}

	}
	system("PAUSE"); //Pause to view output
	return 0;
}