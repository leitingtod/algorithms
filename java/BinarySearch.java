import java.util.Arrays;

public class BinarySearch {
    public static int rank(int k, int[] a) {
        int lo = 0;
        int hi = a.length - 1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (k < a[mid])
                hi = mid - 1;
            else if (k > a[mid])
                lo = mid + 1;
            else
                return mid;
        }
        return -1;
    }

    public static void main(String[] args) {
        int[] a = {1, 3, 5, 6, 7, 8, 9, 11};
        System.out.println(rank(16, a));
    }
}
