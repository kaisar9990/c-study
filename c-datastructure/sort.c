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

void merge(int nums[], int start, int mid, int end)
{
    int size = end - start + 1;
    int tmp_arr[size];
    int arr_i = 0;
    int i = start;
    int j = mid + 1;
    while (i <= mid && j <= end)
    {
        if (nums[i] < nums[j])
        {
            tmp_arr[arr_i] = nums[i];
            arr_i++;
            i++;
        }
        else
        {
            tmp_arr[arr_i] = nums[j];
            arr_i++;
            j++;
        }
    }
    while (i <= mid)
    {
        tmp_arr[arr_i] = nums[i];
        arr_i++;
        i++;
    }
    while (j <= end)
    {
        tmp_arr[arr_i] = nums[j];
        arr_i++;
        j++;
    }
    int tmp_i = 0;
    int start_i = start;
    while (start_i <= end)
    {
        nums[start_i] = tmp_arr[tmp_i];
        start_i++;
        tmp_i++;
    }
}

void merge_sort(int nums[], int start, int end)
{
    if (start >= end)
    {
        return;
    }
    int mid = start + (end - start) / 2;
    merge_sort(nums, start, mid);
    merge_sort(nums, mid + 1, end);
    merge(nums, start, mid, end);
}