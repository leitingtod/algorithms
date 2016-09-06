/**
 * Created by lWX351071 on 2016/9/6.
 */
'use strict';
var quick_sort = {
    // 快速排序也叫划分交换排序，因其排序速度特别快，故称快速排序。
    // 其基本原理是划分：
    // 划分元素的选取是影响性能的关键
    // 输入数据越乱，所选划分元素值的随机性越好，排序速度越快。
    // 相反，输入越有序，所有划分元素为最大或最小值的可能性越大，排序越慢。可见其不是自然排序方法。
    // 无法保证划分所产生的子问题大小完全平衡。即改变划分元素的选取方法，至多只能改变算法平均情况下的时间
    // 性能，无法改变最坏情况下的时间性能。
    // 快速排序不属于原地排序，无论是否使用递归或迭代，都需要一定的辅助空间
    // 最坏：T(n) = O(n^2), S(n) = O(n)；平均：T(n) = O(nLogn), S(n) = O(nLogn)

    'lei': function (a) {
        var sw = 0, iter = 0;
        function partion(a, s, t) {
            var i= s, j= t, x=a[s];

            do {
                while (a[j] >= x && i < j) {
                    j--;
                    iter++;
                }
                if (i < j) {
                    a[i++] = a[j];
                    sw++;
                }
                while (a[i] < x && i < j) {
                    i++;
                    iter++;
                }
                if (i < j) {
                    a[j--] = a[i];
                    sw++;
                }
            } while(i<j);
            a[i] = x;
            return i
        }

        function quicksort(a, s, t) {
            if(s<t) {
                var k = partion(a, s, t);
                quicksort(a, s, k-1);
                quicksort(a, k+1, t);
            }
        }
        quicksort(a, 0, a.length)
        return {'answer': a, 'swap': sw, 'iter': iter, 'O(nlogn)': ''}
    },

    'nzakas': function (a) {
        var iter = 0, sw = 0;

        function swap(items, firstIndex, secondIndex) {
            var temp = items[firstIndex];
            items[firstIndex] = items[secondIndex];
            items[secondIndex] = temp;
            sw++;
        }

        function partition(items, left, right) {
            var pivot = items[Math.floor((right + left) / 2)],  // pivot value is middle item
                i = left,     // starts from left and goes right to pivot index
                j = right;    // starts from right and goes left to pivot index


            // while the two indices don't match
            while (i <= j) {

                // if the item on the left is less than the pivot, continue right
                while (items[i] < pivot) {
                    i++;
                    iter++;
                }

                // if the item on the right is greater than the pivot, continue left
                while (items[j] > pivot) {
                    j--;
                    iter++;
                }

                // if the two indices still don't match, swap the values
                if (i <= j) {
                    swap(items, i, j);

                    // change indices to continue loop
                    i++;
                    j--;
                }
            }

            // this value is necessary for recursion
            return i;
        }

        /**
         * A quicksort implementation in JavaScript. The array
         * is sorted in place.
         * @param {Array} items An array of items to sort.
         * @return {Array} The sorted array.
         */
        function quickSort(items, left, right) {

            var index;

            // performance - don't sort an array with zero or one items
            if (items.length > 1) {

                // fix left and right values - might not be provided
                left = typeof left != "number" ? 0 : left;
                right = typeof right != "number" ? items.length - 1 : right;

                // split up the entire array
                index = partition(items, left, right);

                // if the returned index
                if (left < index - 1) {
                    quickSort(items, left, index - 1);
                }

                if (index < right) {
                    quickSort(items, index, right);
                }

            }

            return items;
        }

        var ret = quickSort(a, 0, a.length);
        return {'answer': ret, 'swap': sw, 'iter': iter, 'O(nlogn)': ''}
    },

    'felipernb': function (a) {
        /**
         * Swaps two elements in the array
         */
        var iter = 0, sw = 0;
        var swap = function (array, x, y) {
            var tmp = array[y];
            array[y] = array[x];
            array[x] = tmp;
            sw++;
        };
        /**
         * Chooses a pivot and makes every element that is
         * lower than the pivot move to its left, and every
         * greater element moves to its right
         *
         * @return Number the positon of the pivot
         */
        var partition = function (a, comparator, lo, hi) {
            // pick a random element, swap with the rightmost and
            // use it as pivot
            swap(a, Math.floor(Math.random() * (hi - lo)) + lo, hi);
            var pivot = hi;

            // dividerPosition keeps track of the position
            // where the pivot should be inserted
            var dividerPosition = lo;

            for (var i = lo; i < hi; i++) {
                if (comparator(a[i], a[pivot]) < 0) {
                    swap(a, i, dividerPosition);
                    dividerPosition++;
                }
                iter++;
            }
            swap(a, dividerPosition, pivot);
            return dividerPosition;
        };

        /**
         * Quicksort recursively sorts parts of the array in
         * O(n.lg n)
         */

        var comparator = function comparator(a, b) {
            return a - b;
        };

        var ret = (function quicksort(array, lo, hi) {
            while (lo < hi) {
                var p = partition(array, comparator, lo, hi);
                // Chooses only the smallest partition to use recursion on and
                // tail-optimize the other. This guarantees O(log n) space in worst case.
                if (p - lo < hi - p) {
                    quicksort(array, lo, p - 1);
                    lo = p + 1;
                } else {
                    quicksort(array, p + 1, hi);
                    hi = p - 1;
                }
            }

            return array;
        })(a, 0, a.length - 1);
        return {'answer': ret, 'swap': sw, 'iter': iter, 'O(nlogn)': ''}
    },

    'mgechev': function (array) {
        function compare(a, b) {
            return a - b;
        }

        /**
         * Swap the places of two elements
         *
         * @private
         * @param {array} array The array which contains the elements
         * @param {number} i The index of the first element
         * @param {number} j The index of the second element
         * @returns {array} array The array with swaped elements
         */
        var iter = 0, sw = 0;

        function swap(array, i, j) {
            var temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            sw++;
            return array;
        }

        /**
         * Partitions given subarray using Lomuto's partitioning algorithm.
         *
         * @private
         * @param {array} array Input array
         * @param {number} left The start of the subarray
         * @param {number} right The end of the subarray
         */
        function partition(array, left, right, compare) {
            var cmp = array[right - 1];
            var minEnd = left;
            var maxEnd;
            for (maxEnd = left; maxEnd < right - 1; maxEnd += 1) {
                if (compare(array[maxEnd], cmp) < 0) {
                    swap(array, maxEnd, minEnd);
                    minEnd += 1;
                }
                iter++;
            }
            swap(array, minEnd, right - 1);
            return minEnd;
        }

        /**
         * Sorts given array.
         *
         * @private
         * @param {array} array Array which should be sorted
         * @param {number} left The start of the subarray which should be handled
         * @param {number} right The end of the subarray which should be handled
         * @returns {array} array Sorted array
         */
        function quickSort(array, left, right, cmp) {
            if (left < right) {
                var p = partition(array, left, right, cmp);
                quickSort(array, left, p, cmp);
                quickSort(array, p + 1, right, cmp);
            }
            return array;
        }

        /**
         * Calls the quicksort function with it's initial values.
         *
         * @public
         * @param {array} array The input array which should be sorted
         * @returns {array} array Sorted array
         */

        var cmp = compare;
        var ret = quickSort(array, 0, array.length, cmp);
        return {'answer': ret, 'swap': sw, 'iter': iter, 'O(nlogn)': ''}
    },

    'mgechev1': function (array) {
        var sw= 0, iter = 0;
        function compare(a, b) {
            return a - b;
        }


        /**
         * Partitions the array in two parts by the middle elements.
         * All elemnts which are less than the chosen one goes left from it
         * all which are greater goes right from it.
         * Uses Hoare's partitioning algorithm.
         *
         * @param {array} array Array which should be partitioned
         * @param {number} left Left part of the array
         * @param {number} right Right part of the array
         * @return {number}
         */
        function partition(array, left, right, cmp) {
            var pivot = array[Math.floor((left + right) / 2)];
            var temp;
            while (left <= right) {
                while (cmp(array[left], pivot) < 0) {
                    left += 1;
                    iter++;
                }
                while (cmp(array[right], pivot) > 0) {
                    right -= 1;
                    iter++
                }
                if (left <= right) {
                    temp = array[left];
                    array[left] = array[right];
                    array[right] = temp;
                    sw++;
                    left += 1;
                    right -= 1;
                }
            }
            return left;
        }

        /**
         * Recursively calls itself with different values for
         * left/right part of the array which should be processed
         *
         * @private
         * @param {array} array Array which should be processed
         * @param {number} left Left part of the array which should be processed
         * @param {number} right Right part of the array which should be processed
         */
        function quicksort(array, left, right, cmp) {
            var mid = partition(array, left, right, cmp);
            if (left < mid - 1) {
                quicksort(array, left, mid - 1, cmp);
            }
            if (right > mid) {
                quicksort(array, mid, right, cmp);
            }
        }

        /**
         * Quicksort algorithm. In this version of quicksort used
         * middle element of array for the pivot.<br><br>
         * Time complexity: O(N log(N)).
         *
         * @example
         *
         * var sort = require('path-to-algorithms/src' +
         * '/sorting/quicksort-middle').quickSort;
         * console.log(sort([2, 5, 1, 0, 4])); // [ 0, 1, 2, 4, 5 ]
         *
         * @public
         * @module sorting/quicksort-middle
         * @param {Array} array Input array.
         * @param {Function} cmp Optional. A function that defines an
         * alternative sort order. The function should return a negative,
         * zero, or positive value, depending on the arguments.
         * @return {Array} Sorted array.
         */

        var cmp = compare;
        quicksort(array, 0, array.length, cmp);
        return {'answer': array, 'swap': sw, 'iter': iter, 'O(nlogn)': ''}
    },

    'duereg': function (array) {
        var iter = 0, sw = 0;

        function swap(arrayToSort, low, high) {
            const lowValue = arrayToSort[low];
            arrayToSort[low] = arrayToSort[high];
            arrayToSort[high] = lowValue;
            sw++;
        }

        function partition(arrayToSort, low, high) {
            const pivot = arrayToSort[Math.floor((low + high) / 2)];

            while (low <= high) {
                while (arrayToSort[low] < pivot) {
                    low++;
                    iter++
                }
                while (arrayToSort[high] > pivot) {
                    high--;
                    iter++
                }

                if (low <= high) {
                    swap(arrayToSort, low, high);
                    low++;
                    high--;
                }
            }
            return low;
        }

        function quickSort(arrayToSort, low, high) {
            const index = partition(arrayToSort, low, high);

            if (low < index - 1) {
                quickSort(arrayToSort, low, index - 1);
            }
            if (index < high) {
                quickSort(arrayToSort, index, high);
            }
        }

        quickSort(array, 0, array.length);
        return {'answer': array, 'swap': sw, 'iter': iter, 'O(nlogn)': ''}
    }
};

var test = function () {
    console.warn('Shell Insert Sort is the Best\n');
    var filter = ['lei', 'nzakas', 'felipernb', 'mgechev', 'mgechev1', 'duereg'];

    function sort(b) {
        for (var v in quick_sort) {
            var a = b.concat();
            //console.log(filter.indexOf(v), v, a);
            if (filter.indexOf(v) >= 0) {
                console.log(v, quick_sort[v](a, function (x, y) {
                    return x - y
                }));
            }
        }
    }

    sort([22, 33, 11, 5, 9, 100, 40]);
    console.log('');
    sort([11, 22, 33, 44, 55, 66, 77]);
    console.log('');
    sort([11, 22, 33, 44, 55, 66, 77].reverse())

};

test();
