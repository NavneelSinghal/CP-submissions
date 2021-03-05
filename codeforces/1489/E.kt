import java.io.*
import java.util.*

fun main(args:Array<String>) {
    solve()
}

fun solve() {
    val q = nextInt()
    var left = 0
    var right = 0
    var started = false
    val loc = MutableList<Int>(200001){0}
    for (query in 0 until q) {
        val type = read()
        val id = nextInt()
        if (type == "L") {
            if (!started) {
                started = true
                loc[id] = 0
            } else {
                --left
                loc[id] = left
            }
        } else if (type == "R") {
            if (!started) {
                started = true
                loc[id] = 0
            } else {
                ++right
                loc[id] = right
            }
        } else {
            System.out.println(Math.min(loc[id] - left, right - loc[id]))
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

