import java.io.*
import java.util.*

fun main(args:Array<String>) {
    solve()
}

fun roundup(n: Int, t: Int): Int {
    val m = n % t
    if (m >= t / 2) {
        return n / t + 1
    } else {
        return n / t
    }
}

fun solve() {
    val t = readInt()
    repeat(t) {
        val n = readInt()
        when {
            n < 1000 -> System.out.println(n)
            n < 999500 -> System.out.println(roundup(n, 1000).toString() + "K")
            else -> System.out.println(roundup(n, 1000000).toString() + "M")
        }
    }
}

@JvmField val INPUT: InputStream = System.`in`
@JvmField val OUTPUT: PrintStream = System.out
@JvmField val internal_reader = INPUT.bufferedReader()
fun readLine(): String? = internal_reader.readLine()
fun readLn() = internal_reader.readLine()!!
@JvmField var internal_tokenizer: StringTokenizer = StringTokenizer("")
fun read(): String {
    while (internal_tokenizer.hasMoreTokens().not()) internal_tokenizer = StringTokenizer(internal_reader.readLine() ?: return "", " ")
    return internal_tokenizer.nextToken()
}
fun readInt() = read().toInt()
fun readLong() = read().toLong()
fun readDouble() = read().toDouble()
fun readStrings(n: Int) = List(n) { read() }
fun readLines(n: Int) = List(n) { readLn() }
fun readInts(n: Int) = List(n) { readInt() }
fun readDoubles(n: Int) = List(n) { readDouble() }
fun readLongs(n: Int) = List(n) { readLong() }
@JvmField val internal_writer = PrintWriter(OUTPUT, false)
inline fun output(block: PrintWriter.() -> Unit) { internal_writer.apply(block).flush() }
