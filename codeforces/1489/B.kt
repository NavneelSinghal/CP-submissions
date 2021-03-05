import java.io.*
import java.util.*

fun main(args:Array<String>) {
    solve()
}

fun solve() {
    val q = nextInt()
    for (iter in 1..q) {
        var n = nextLong()
        var a = nextLong()
        var b = nextLong()
        if (2 * a < b)
            b = 2 * a
        if (n % 2 == 1L) {
            System.out.println(b * (n - 1) / 2 + a)
        } else {
            System.out.println(b * n / 2)
        }
    }
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
