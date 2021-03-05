import java.io.*
import java.util.*

fun main(args:Array<String>) {
    solve()
}

fun solve() {
    val n = nextInt()
    var a = IntArray(n)
    var answer: MutableList<Int> = mutableListOf()
    for (i in 0 until n) {
        a[i] = nextInt()
    }
    for (i in 0 until n) {
        var found = false
        for (j in i + 1 until n) {
            if (a[i] == a[j]) {
                found = true
                break
            }
        }
        if (found) continue
        answer.add(a[i])
    }
    System.out.println(answer.size)
    for (i in answer) {
        System.out.print(i)
        System.out.print(" ")
    }
    System.out.println("")
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
