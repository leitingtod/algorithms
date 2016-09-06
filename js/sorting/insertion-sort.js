/**
 * Created by lWX351071 on 2016/8/31.
 */
/*
 插入排序就是每一步都将一个待排数据按其大小插入到已经排序的数据中的适当位置，直到全部插入完毕。
 插入排序方法分直接插入排序和折半插入排序两种。
 时间复杂度：插入排序对随即顺序的序列的时间复杂度也为O(N^2)，但是对于基本有序的序列进行排序时间复杂度为O(N)
 */

var insertion_sort = {
    'binary': function (a, comparator_fn) {
        var n = a.length;
        var swap = 0, iter = 0, x, i, j, left, right, mid;
        for(i=1; i<n; i++) {
            x = a[i];

            //二分插入排序一般适宜数据量大的情况，其比较时间复杂度为O(nlogn)，
            //元素移动次数没变，所有并无实质改进，最坏情况下总时间复杂度仍为O(n^2)。
            //当二分查找带来的提升大于直接插入排序的查找时，适宜使用二分插入排序，

            //binary search insert position
            left=0;
            right=i-1;
            while (left<=right) {
                mid = parseInt((left+right)/2);
                if(x<a[mid]) {
                    right = mid - 1
                } else {
                    left = mid + 1
                }
                iter++
            }
            //console.log(left, parseInt(left));
            // insert elem and move some other elements
            for(j=i-1;j>=left;j--) {
                a[j+1] = a[j];
                iter++;
                swap++;
            }
            a[left] = x
        }

        return {'answer': a, 'swap': swap, 'iter': iter, 'O(n^2/n)': '' + n * n + '/' + n}
    },

    'leiLA': function (a, comparator_fn) {
        //书上的这个哨兵算法需要额外的n次移动，其他与leiA算法无异，有毛用
        a.unshift(0);
        var n = a.length;
        var iter = 0, x, i, j;
        for(i=2; i<n; i++) {
            x = a[i];
            j = i -1;
            while(x<a[j]) {
                a[j+1] = a[j--];
                iter++;
            }
            a[j+1] = x
        }

        return {'answer': a, 'swap': iter, 'iter': iter, 'O(n^2/n)': '' + n * n + '/' + n}
    },

    'leiA': function (a, comparator_fn) {
        var n = a.length;
        var iter_cnt = 0, x, i, j;
        for(i=1; i<n; i++) {
            x = a[i];
            //for(var j=i-1; j>-1 && comparator_fn(x,a[j]) < 0; j--) {
            for(j=i-1; j>-1 && a[j] > x; j--) {
                a[j+1] = a[j];
                iter_cnt++;
            }
            a[j+1] = x
        }

        return {'answer': a, 'swap': iter_cnt, 'iter': iter_cnt, 'O(n^2/n)': '' + n * n + '/' + n}
    },

    'lei': function (a, comparator_fn) {
        var n = a.length;
        var iter = 0;
        var swap = 0;
        for(var i=1; i<n; i++) {
            var x = a[i];
            for(var j=0; j<i; j++) {
                if(comparator_fn(x, a[j]) < 0) {
                    //console.log('swap', i, j)
                    for(var k=i; k>j; k--) {
                        var tmp = a[k];
                        a[k] = a[k-1];
                        a[k-1] = tmp;
                        swap++;
                        iter++;
                    }
                }
                iter++
            }
        }

        return {'answer': a, 'swap': swap, 'iter': iter, 'O(n^2/n)': '' + n * n + '/' + n}
    },

    'nzakas': function insertionSort(items) {

        var len     = items.length,     // number of items in the array
            value,                      // the value currently being compared
            i,                          // index into unsorted section
            j,                          // index into sorted section
            iter = 0;


        for (i=0; i < len; i++) {

            // store the current value because it may shift later
            value = items[i];

            /*
             * Whenever the value in the sorted section is greater than the value
             * in the unsorted section, shift all items in the sorted section over
             * by one. This creates space in which to insert the value.
             */
            for (j=i-1; j > -1 && items[j] > value; j--) {
                items[j+1] = items[j];
                iter++;
            }

            items[j+1] = value;
        }

        return {'answer': items, 'swap': iter, 'iter': iter, 'O(n^2)': '' + len * len + '/' + len}
    },

    'felipernb': function (vector, comparatorFn) {
        var n = vector.length;
        var iter = 0;
        var comparator = function (a, b) {
            return a - b;
        };

        for (var i = 1, len = vector.length; i < len; i++) {
            var aux = vector[i];
            var j = i;

            while (j > 0 && comparator(aux, vector[j - 1]) < 0) {
                vector[j] = vector[j - 1];
                j--;
                iter++
            }

            vector[j] = aux;
        }
        return {'answer': vector, 'swap': iter, 'iter': iter, 'O(n^2)': ''+n * n+'/'+n}
    },

    'mgechev': function (array, cmp) {
        function comparator(a, b) {
            return a - b;
        }

        cmp = cmp || comparator;
        var current;
        var j;
        var iter = 0;
        var n = array.length;
        for (var i = 1; i < array.length; i += 1) {
            current = array[i];
            j = i - 1;
            while (j >= 0 && cmp(array[j], current) > 0) {
                array[j + 1] = array[j];
                j -= 1;
                iter++
            }
            array[j + 1] = current;
        }
        return {'answer': array, 'swap': iter, 'iter': iter, 'O(n^2)': ''+n * n+'/'+n}
    }
};

var test = function () {
    console.warn('Shell Insert Sort is the Best\n');
    //var filter = ['binary', 'leiA', 'nzakas', 'felipernb', 'mgechev'];
    var filter = ['binary', 'Shell', 'nzakas'];

    function sort(b) {
        for (var v in insertion_sort) {
            var a = b.concat();
            //console.log(filter.indexOf(v), v, a);
            if (filter.indexOf(v) >= 0) {
                console.log(v, insertion_sort[v](a, function (x, y) {
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
