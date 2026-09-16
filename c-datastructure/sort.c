#include "sort.h"

void quick_sort(int nums[], int start, int end)
{
    if (start >= end)
    {
        return;
    }
    int pivot = nums[start];
    int pivot_i = start;
    int i = start;
    int j = end;
    while (i < j)
    {
        while (i < j && pivot <= nums[j])
        {
            j--;
        }
        if (i == j)
        {
            break;
        }
        // find smaller one
        nums[pivot_i] = nums[j];
        nums[j] = pivot;
        pivot_i = j;

        while (i < j && nums[i] < pivot)
        {
            i++;
        }
        if (i == j)
        {
            break;
        }
        // find bigger one
        nums[pivot_i] = nums[i];
        nums[i] = pivot;
        pivot_i = i;
    }
    quick_sort(nums, start, pivot_i - 1);
    quick_sort(nums, pivot_i + 1, end);
}