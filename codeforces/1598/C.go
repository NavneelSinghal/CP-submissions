// not my own submission
// original submission: https://codeforces.com/contest/1598/submission/131503323

package main

import (
	"bufio"
	"fmt"
	"os"
)

var (
	input  = bufio.NewReaderSize(os.Stdin, 55000)
	output = bufio.NewWriterSize(os.Stdout, 55000)
)

func assert(test bool) {
	if !test {
		panic("assertion!")
	}
}

// (c) Dmitriy Blokhin (sv.dblokhin@gmail.com)
// TODO***
// - read the statement carefully
// - get solution before coding
// - check the boundaries (int/int64)

func main() {
    var t int
    fmt.Fscan(input, &t)
    for t > 0 {
        solve()
        t-- 
    }
	output.Flush()
}

func solve() {
    var n uint64
    fmt.Fscan(input, &n)
    a := make([]uint64, n)
    sum := uint64(0)
    digs := map[uint64]int{}
    for i := uint64(0); i < n; i++ {
        fmt.Fscan(input, &a[i])
        sum += a[i]
        digs[a[i]]++
    }

    if 2 * sum % n != 0 {
        fmt.Println(0)
        return
    }
    x := 2 * sum / n // 2x
    // a[i] - x == x - a[j]
    // a[i] == 2x - a[j]
    // a[i] + a[j] == 2x
    // sum / n == sum' / (n - 2)
    // sum - sum' = ?
    cnt := uint64(0)
    for _, k := range a {
        digs[k]--
        cnt += uint64(digs[x - k])
        assert(digs[x - k] >= 0)
    }
    fmt.Println(cnt)
}
