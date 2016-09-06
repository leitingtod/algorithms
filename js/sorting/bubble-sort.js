/**
 * Created by lWX351071 on 2016/8/31.
 */
'use strict';

// O(n^2)

var bubble_sort = {
    'leiAA': function(a, compare_fn) {
        var i, j, x, flag = true, bound, newbound, iter = 0, swap= 0, n= a.length;
        //最坏情况下，T(n) = O(n^2)；平均情况下，T(n) = O(n^2)
        bound = n-1;
        while(flag) {
            flag = false;
            newbound = 0;
            // newbound表示此次遍历发生交换的元素位置，进一步减少扫描范围，
            // 若无交换，说明整个序列已经有序，无须再进行一下次扫描。
            for(j=0;j<bound;j++) {
                if(a[j]>a[j+1]) {
                    x = a[j];
                    a[j] = a[j+1];
                    a[j+1] = x;
                    swap++;
                    flag = true;
                    newbound = j;
                }
                iter++;
            }
            bound = newbound;
        }
        return {'answer': a, 'swap': swap, 'iter': iter, 'O(n^2)': n * n}
    },

    'leiA': function(a, compare_fn) {
        var i, j, x, flag = true, iter = 0, swap= 0, n= a.length;
        //最坏情况下，T(n) = O(n^2)；平均情况下，T(n) = O(n^2)
        i = n-2;
        while(flag) {
            flag = false;
            //flag表示此次遍历是否发生交换，若无交换，说明整个序列已经有序，无须再进行一下次扫描。
            for(j=0;j<=i;j++) {
                if(a[j]>a[j+1]) {
                    x = a[j];
                    a[j] = a[j+1];
                    a[j+1] = x;
                    swap++;
                    flag = true;
                }
                iter++;
            }
            i--;
        }
        return {'answer': a, 'swap': swap, 'iter': iter, 'O(n^2)': n * n}
    },

    'lei': function(a, compare_fn) {
        var i, j, x, iter = 0, swap= 0, n= a.length;
        for(i=0; i<n-1; i++) {
            for(j=n-2; j>=i; j--) {
                if(a[j]>a[j+1]) {
                    x = a[j];
                    a[j] = a[j+1];
                    a[j+1] = x;
                    swap++;
                }
                iter++;
            }
        }
        return {'answer': a, 'swap': swap, 'iter': iter, 'O(n^2)': n * n}
    },

    'leiError': function (a, comparator_fn) {
        var n = a.length;
        var iter = 0;
        var swap = 0;
        //这样写算得上冒泡吗？好像不是啊:-(，但结果正确，比较、移动次数较多，效率较差。
        for (var i = 0; i < n; i++) {
            for (var j = i + 1; j < n; j++) {
                if (comparator_fn(a[i], a[j]) > 0) {
                    var tmp = a[i];
                    a[i] = a[j];
                    a[j] = tmp;
                    swap++;
                }
                iter++;
                //console.log(i, a);
            }
        }
        return {'answer': a, 'swap': swap, 'iter': iter, 'O(n^2)': n * n}
    },

    'nzakas': function (items, comparator_fn) {
        function swap(items, firstIndex, secondIndex) {
            var temp = items[firstIndex];
            items[firstIndex] = items[secondIndex];
            items[secondIndex] = temp;
        }

        var iter = 0;
        var sw = 0;
        var len = items.length,
            i, j, stop;

        for (i = 0; i < len; i++) {
            for (j = 0, stop = len - i; j < stop; j++) {
                if (comparator_fn(items[j], items[j + 1]) > 0) {
                    swap(items, j, j + 1);
                    sw++
                }
                iter++
            }
        }

        return {'answer': items, 'swap': sw, 'iter': iter, 'O(n^2)': len * len}
    },

    'felipernb': function (a, comparatorFn) {
        var n = a.length;
        var bound = n - 1;
        var check = false;
        var iter = 0;
        var swap = 0;
        for (var i = 0; i < n - 1; i++) {
            var newbound = 0;
            for (var j = 0; j < bound; j++) {
                if (comparatorFn(a[j], a[j + 1]) > 0) {
                    var tmp = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = tmp;
                    newbound = j;
                    check = true;
                    swap++;
                }
                iter++;
                //console.debug(bound, newbound, a)
            }
            //console.warn(i);
            if (!check)
                break;
            bound = newbound;
        }
        return {'answer': a, 'swap': swap, 'iter': iter, 'O(n^2)': n * n}
    },

    'mgechev': function (array, cmp) {
        function comparator(a, b) {
            return a - b;
        }

        cmp = cmp || comparator;
        var temp;
        var iter = 0;
        var swap = 0;
        var n = array.length;
        for (var i = 0; i < array.length; i += 1) {
            for (var j = i; j > 0; j -= 1) {
                if (cmp(array[j], array[j - 1]) < 0) {
                    temp = array[j];
                    array[j] = array[j - 1];
                    array[j - 1] = temp;
                    swap++
                }
                iter++
            }
        }
        return {'answer': array, 'swap': swap, 'iter': iter, 'O(n^2)': n * n}
    }
};

var test = function () {
    console.warn('felipernb is the best\n');

    var filter = ['felipernb'];

    function sort(b) {
        for (var v in bubble_sort) {
            var a = b.concat();
            //console.log(filter.indexOf(v), v, a);
            if (filter.indexOf(v) >= 0) {
                console.log(v, bubble_sort[v](a, function (x, y) {
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
