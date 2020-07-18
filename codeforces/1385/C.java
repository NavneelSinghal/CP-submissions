import java.awt.Point;
import java.io.*;
import java.math.BigInteger;
import java.util.*;
import static java.lang.Math.*;

public class Solution implements Runnable {

    BufferedReader in;
    PrintWriter out;
    StringTokenizer tok = new StringTokenizer("");

    public static void main(String[] args) {
        new Thread(null, new Solution(), "", 256 * (1L << 20)).start();
    }

    public void run() {
        try {
            long t1 = System.currentTimeMillis();
            //if (System.getProperty("ONLINE_JUDGE") != null) {
            in = new BufferedReader(new InputStreamReader(System.in));
            out = new PrintWriter(System.out);
            //} else {
            //	in = new BufferedReader(new FileReader("input.txt"));
            //	out = new PrintWriter("output.txt");
            //}
            Locale.setDefault(Locale.US);
            solve();
            in.close();
            out.close();
            long t2 = System.currentTimeMillis();
            System.err.println("Time = " + (t2 - t1));
        } catch (Throwable t) {
            t.printStackTrace(System.err);
            System.exit(-1);
        }
    }

    String readString() throws IOException {
        while (!tok.hasMoreTokens()) {
            tok = new StringTokenizer(in.readLine());
        }
        return tok.nextToken();
    }

    int readInt() throws IOException {
        return Integer.parseInt(readString());
    }

    long readLong() throws IOException {
        return Long.parseLong(readString());
    }

    double readDouble() throws IOException {
        return Double.parseDouble(readString());
    }

    // solution

    void solve() throws IOException {
        int t;
        t = readInt();
        for (int _t = 0; _t < t; ++_t) {
            int n = readInt();
            int[] a = new int[n];
            for (int i = 0; i < n; ++i) {
                a[i] = readInt();
            }
            int last = n - 1;
            while (last > 0 && a[last] <= a[last - 1]) --last;
            while (last > 0 && a[last] >= a[last - 1]) --last;
            out.println(last);
        }
    }

}
