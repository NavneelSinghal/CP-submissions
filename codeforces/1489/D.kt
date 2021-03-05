import java.io.*
import java.util.*

fun main(args:Array<String>) {
    solve()
}

fun solve() {
    
    val n = nextInt()
    val a = MutableList<String>(n) { "" }
    
    for (i in 0 until n) {
        a[i] = read()
    }

    val unique = MutableList<String>(0) { "" }
    val frequencyMap = HashMap<String, Int>(n)
    
    for (s in a) {
        if (s in frequencyMap) {
            frequencyMap.put(s, frequencyMap.get(s)!! + 1)
        } else {
            frequencyMap.put(s, 1)
            unique.add(s)
        }
    }

    fun substring(a : String, b : String) : Boolean {
        if (a.length <= b.length) {
            for (i in 0..b.length - a.length) {
                if (b.slice(IntRange(i, i + a.length - 1)) == a) {
                    return true
                }
            }
        }
        return false
    }

    val m = unique.size
    val g = MutableList<MutableList<Int>>(m) { MutableList<Int>(0){0} }
    for (i in 0 until m) {
        for (j in i + 1 until m) {
            if (substring(unique[i], unique[j])) {
                g[i].add(j)
            } else if (substring(unique[j], unique[i])) {
                g[j].add(i)
            }
        }
    }

    // won't use recursive toposort since stack size

    val indeg = MutableList<Int>(n){0}
    val outdeg = MutableList<Int>(n){0}
    for (i in 0 until m) {
        for (j in g[i]) {
            indeg[j]++
            outdeg[i]++
        }
    }

    var cnt_src = 0
    var index = -1

    for (i in 0 until m) {
        if (indeg[i] == 0) {
            cnt_src++
            index = i
        }
    }

    if (cnt_src != 1) {
        System.out.println("NO")
        return
    }

    val answer = MutableList<Int>(1){index}

    while (g[index].size > 0) {
        var smallestIndex = 0
        for ((i, v) in g[index].withIndex()) {
            if (unique[v].length < unique[g[index][smallestIndex]].length) {
                smallestIndex = i
            }
        }
        index = g[index][smallestIndex]
        answer.add(index)
    }

    if (answer.size == m) {
        System.out.println("YES")
        for (i in answer) {
            val times = frequencyMap.getOrPut(unique[i]){0}
            for (j in 0 until times) {
                System.out.println(unique[i])
            }
        }
    } else {
        System.out.println("NO")
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
