/**
 * Created by lWX351071 on 2016/9/6.
 */

var shell_sort = {
    'lei': function (a) {
        //希尔排序将直接插入排序中的一次只能移动一个位置，改进为可跳跃式移动，即由原来的a[j+1] = a[j]，
        //改进为a[j+k] = a[j]。但在每趟排序中k不能恒定，存在经验性的序列，且最后一次排序的增量k必须为1：
        // ...9,5,3,1    所有形如 2^k + 1 的数       T(n) = O(n^(3/2)
        // ...12,6,3,2,1 所有形如 2^p * 3^p的数      T(n) = O(n * (logN)^2)
        // ...15,7,3,1   2^k - 1
        // ...11,5,3,1   (2^k - (-1)^k) / 3
        // ...40,13,4,1  3^k - 1 / 2
        var d = [9, 5, 3, 1];
        var i, j, k, h, x, iter = 0, swap = 0, n = a.length;

        for (h = 0; h < d.length; h++) {
            k = d[h];
            for (i = k; i < n; i++) {
                x = a[i];
                for (j = i - k; j > -1 && x < a[j]; j = j - k) {
                    a[j + k] = a[j];
                    swap++;
                    iter++;
                }
                a[j + k] = x;
            }
        }
        return {'answer': a, 'swap': swap, 'iter': iter, 'O(n^2/n)': '' + n * n + '/' + n}
    },

    'felipernb': function(array) {
        var comparator =  function (a, b) {
            return a - b;
        };

        var begin = 0;
        var end = array.length - 1;
        var gap = parseInt((end - begin + 1) / 2, 10);
        var i = 0;
        var j = 0;
        var temp = 0;
        var iter = 0, swap = 0, n=array.length;

        while (gap >= 1) {
            for (i = begin + gap; i <= end; i += 1) {
                temp = array[i];
                j = i - gap;
                while (j >= begin && comparator(array[j], temp) > 0) {
                    array[j + gap] = array[j];
                    j -= gap;
                    iter++;
                    swap++;
                }
                array[j + gap] = temp;
            }
            gap = parseInt(gap / 2, 10);
        }

        return {'answer': array, 'swap': swap, 'iter': iter, 'O(n^2/n)': '' + n * n + '/' + n}
    },

    'mgechev': function (array) {
        function compare(a, b) {
            return a - b;
        }

        var gaps = [701, 301, 132, 57, 23, 10, 4, 1];

        /**
         * Shellsort which uses the gaps 701, 301, 132, 57, 23, 10, 4, 1 and
         * insertion sort to sort sub-arrays which match for the different gaps.
         *
         * @example
         *
         * var sort = require('path-to-algorithms/src/' +
         * 'sorting/shellsort').shellSort;
         * console.log(sort([2, 5, 1, 0, 4])); // [ 0, 1, 2, 4, 5 ]
         *
         * @public
         * @module sorting/shellsort
         * @param {Array} array Input array.
         * @param {Function} cmp Optional. A function that defines an
         * alternative sort order. The function should return a negative,
         * zero, or positive value, depending on the arguments.
         * @return {Array} Sorted array.
         */

        cmp = compare;

        var gap;
        var current;
        var iter = 0, swap = 0, n=array.length;
        for (var k = 0; k < gaps.length; k += 1) {
            gap = gaps[k];
            for (var i = gap; i < array.length; i += gap) {
                current = array[i];
                for (var j = i;
                     j >= gap && cmp(array[j - gap], current) > 0; j -= gap) {
                    array[j] = array[j - gap];
                    iter++;
                    swap++;
                }
                array[j] = current;
            }
        }
        return {'answer': array, 'swap': swap, 'iter': iter, 'O(n^2/n)': '' + n * n + '/' + n}

    }
};

var test = function () {
    console.warn('Shell Insert Sort is the Best\n');
    var filter = ['lei', 'felipernb', 'mgechev'];

    function sort(b) {
        for (var v in shell_sort) {
            var a = b.concat();
            //console.log(filter.indexOf(v), v, a);
            if (filter.indexOf(v) >= 0) {
                console.log(v, shell_sort[v](a, function (x, y) {
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
