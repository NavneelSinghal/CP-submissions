import java.io.*
import java.util.*

fun main(args:Array<String>) {
    solve()
}

fun solve() {
    val n = nextInt()
    val s = read()
    var state = 0
    var ans = 0
    for (c in s) {
        if (state == 0) {
            if (c == 'x') {
                state = 1
            }
        } else if (state == 1) {
            if (c == 'x') {
                state = 2
            } else {
                state = 0
            }
        } else {
            if (c == 'x') {
                state = 2
                ans++
            } else {
                state = 0
            }
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
