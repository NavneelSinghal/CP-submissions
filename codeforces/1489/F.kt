import java.io.*
import java.util.*

fun main(args:Array<String>) {
    solve()
}

fun solve() {
    
    val n = nextInt()
    val m = nextInt()
    val k = nextInt()

    val a = MutableList<Int>(n){0}
    for (i in 0 until n) {
        a[i] = nextInt()
    }
    
    // binary search on number of things thrown out
    
    var l = n
    while (l - 1 >= 0 && a[l - 1] <= k) l--
    var r = n
    var ans = n
    
    while (l <= r) {
    
        val mid = (l + r) / 2
        var totalBoxes = 1
        var curSize = k
        
        for (i in mid until n) {
            if (curSize < a[i]) {
                totalBoxes++
                curSize = k
            }
            curSize -= a[i]
        }

        if (totalBoxes > m) {
            l = mid + 1
            ans = n - l
        } else {
            r = mid - 1
        }
    }

    System.out.println(ans)
}

@JvmField val INPUT = System.`in`
@JvmField val OUTPUT = System.out
@JvmField val _reader = INPUT.bufferedReader()
fun readLine(): String? = _reader.readLine()
fun readLn() = _reader.readLine()!!
@JvmField var _tokenizer: StringTokenizer = StringTokenizer("")
fun read(): String {
    while (_tokenizer.hasMoreTokens().not()) _tokenizer = StringTokenizer(_reader.readLine() ?: return "", " ")
    return _tokenizer.nextToken()
}
fun nextInt() = read().toInt()
fun nextLong() = read().toLong()
@JvmField val _writer = PrintWriter(OUTPUT, false)
inline fun output(block: PrintWriter.() -> Unit) { _writer.apply(block).flush() }

