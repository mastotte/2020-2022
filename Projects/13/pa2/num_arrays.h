#pragma once

int maximum(int *nums, int len);

int sum_positive(int *nums, int len);

int reduce(int *nums, int len, int (*f)(int,int), int initial);

int maximum_with_reduce(int *nums, int size);

int sum_positive_with_reduce(int *nums, int size);

int count_negative_with_reduce(int *nums, int size);
