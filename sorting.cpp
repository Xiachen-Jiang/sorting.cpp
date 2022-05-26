#include <cstdlib>
#include <getopt.h>
#include <iostream>
#include <string>

using namespace std;

static long comparisons = 0;
static long swaps = 0;

void swap(int* a, int* b)
{
    // add code here
    int temp = *a;
    *a = *b;
    *b = temp;
    swaps += 1;
}

void selectionSort(int* first, int* last)
{
    // add code here
    for(int *i = first; i < last - 1; ++i)
    {
        int *index = i;
        for(int *j = i + 1; j <= last; ++j)
        {
            if(*j < *index)
            {
                index = j;
                comparisons += 1;
            }
        }
        swap(index, i);
    }
}

void insertionSort(int* first, int* last)
{
    // add code here
    for(int *i = first; i < last - 1; i++)
    {
        for(int *j = i + 1; j > first; j--)
        {
            if(*j < *(j - 1))
            {
                swap(j,j - 1);
            }
            comparisons += 1;
        }
    }
}

int* partition(int* first, int* last)
{
    int* index = last - 1;
    int* i = first;
    int* j = last - 1;

    while (true)
    {
        while (*i < *index && i < last){
            i += 1;
            comparisons += 1;
        }
        while (*j >= *index && j > first){
            j -= 1;
            comparisons += 1;
        }

        if (i >= j) {
            comparisons += 1;
            break;
        }

        swap (i,j);
    }
    swap(last - 1,i);
    return i;
}

void quickSort(int* first, int* last)
{
    //Optimisation 1: Use insertion sort when sequence length is quite long
    //Optimisation 2: Tail recursive optimisation

    if(first >= last - 1)
    {
        return;
    }

    int* index = partition(first,last);
    quickSort(first,index);
    quickSort(index + 1, last);

}

int main(int argc, char** argv)
{
    string algorithm = "selection";
    string dataset = "random";

    for (int c; (c = getopt(argc, argv, "ravqsin")) != -1;) {
        switch (c) {
        case 'r':
            dataset = "random";
            break;
        case 'a':
            dataset = "sorted";
            break;
        case 'v':
            dataset = "reverse";
            break;
        case 'q':
            algorithm = "quicksort";
            break;
        case 's':
            algorithm = "selection";
            break;
        case 'i':
            algorithm = "insertion";
            break;
        case 'n':
            algorithm = "none";
            break;
        }
    }
    argc -= optind;
    argv += optind;

    const int size = argc > 0 ? atoi(argv[0]) : 10000;
    int* data = new int[size];

    if (dataset == "sorted") {
        for (int i = 0; i < size; ++i) {
            data[i] = i;
        }
    }
    else if (dataset == "reverse") {
        for (int i = 0; i < size; ++i) {
            data[i] = size - i - 1;
        }
    }
    else if (dataset == "random") {
        for (int i = 0; i < size; ++i) {
            data[i] = rand() % size;
        }
    }

    if (algorithm == "quicksort") {
        quickSort(data, data + size);
    }
    else if (algorithm == "selection") {
        selectionSort(data, data + size);
    }
    else if (algorithm == "insertion") {
        insertionSort(data, data + size);
    }

    for (int i = 1; i < size; i++) {
        if (data[i] < data[i - 1]) {
            cout << "Oops!" << '\n';
            exit(1);
        }
    }

    cout << "OK" << '\n';
    cout << "Algorithm:   " << algorithm << '\n';
    cout << "Data set:    " << dataset << '\n';
    cout << "Size:        " << size << '\n';
    // Uncomment for level 3 and 4
    cout << "Comparisons: " << comparisons << '\n';
    cout << "Swaps:       " << swaps << '\n';

    delete[] data;
    return 0;
}
