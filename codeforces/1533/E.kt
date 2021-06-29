@file:Suppress("NOTHING_TO_INLINE", "EXPERIMENTAL_FEATURE_WARNING", "OVERRIDE_BY_INLINE")

import java.io.PrintStream
import java.io.PrintWriter
import java.lang.StringBuilder
import java.util.StringTokenizer
import java.util.TreeMap
import kotlin.math.*
import kotlin.random.*
import kotlin.collections.sort as internalSort
import kotlin.collections.sortDescending as internalSortDescending
import kotlin.io.println as iprintln

fun main() {
    internal_writer.work()
    internal_writer.flush()
}

fun PrintWriter.work() {
    // val t = readInt()
    val t = 1
    for (i in 1..t) {
        solve()
    }
}

fun PrintWriter.solve() {
    val n = readInt()
    val a = readIntArray(n)
    val b = readIntArray(n + 1)
    a.sort()
    b.sort()
    val m = readInt()
    val c = readIntArray(m)
    val id = MutableList(m) { i -> i }
    id.sortBy { i -> c[i] }
    val diffahead = IntArray(n)
    val diffsync = IntArray(n)
    for (i in 0 until n) {
        diffahead[i] = b[i + 1] - a[i]
        diffsync[i] = b[i] - a[i]
    }
    val inf = 1_000_000_000
    val prediffahead = IntArray(n + 1) { _ -> -inf}
    val prediffsync = IntArray(n + 1) { _ -> -inf}
    val sufdiffahead = IntArray(n + 1) { _ -> -inf}
    val sufdiffsync = IntArray(n + 1) { _ -> -inf}
    for (i in 0 until n) {
        prediffahead[i + 1] = max(prediffahead[i], diffahead[i])
        prediffsync[i + 1] = max(prediffsync[i], diffsync[i])
    }
    for (i in n - 1 downTo 0) {
        sufdiffahead[i] = max(sufdiffahead[i + 1], diffahead[i])
        sufdiffsync[i] = max(sufdiffsync[i + 1], diffsync[i])
    }
    val ans = MutableList(m) { _ -> 0}
    for (i in 0 until m) {
        val x = c[id[i]]
        var l = -1
        var r = n
        while (r - l > 1) {
            val mid = (l + r) / 2
            if (a[mid] >= x) {
                r = mid
            } else {
                l = mid
            }
        }
        // new location is l
        ans[id[i]] = max(max(prediffsync[l + 1], sufdiffahead[r]), b[r] - x)
    }
    for (i in ans) {
        print(i)
        print(" ")
    }
    println("")
}

@JvmField
val INPUT = System.`in`

@JvmField
val OUTPUT = System.out

@JvmField
val internal_reader = INPUT.bufferedReader()
fun readLine(): String? = internal_reader.readLine()
fun readLn() = internal_reader.readLine()!!

@JvmField
var internal_tokenizer: StringTokenizer = StringTokenizer("")
fun read(): String {
    while (internal_tokenizer.hasMoreTokens().not()) internal_tokenizer = StringTokenizer(internal_reader.readLine() ?: return "", " ")
    return internal_tokenizer.nextToken()
}

fun readInt() = read().toInt()
fun readDouble() = read().toDouble()
fun readLong() = read().toLong()
fun readStrings(n: Int) = List(n) { read() }
fun readLines(n: Int) = List(n) { readLn() }
fun readInts(n: Int) = List(n) { read().toInt() }
fun readIntArray(n: Int) = IntArray(n) { read().toInt() }
fun readDoubles(n: Int) = List(n) { read().toDouble() }
fun readDoubleArray(n: Int) = DoubleArray(n) { read().toDouble() }
fun readLongs(n: Int) = List(n) { read().toLong() }
fun readLongArray(n: Int) = LongArray(n) { read().toLong() }

@JvmField
val internal_writer = PrintWriter(OUTPUT, false)

/** shuffles and sort overrides to avoid quicksort attacks */
private inline fun <T> internalShuffle(rnd: Random, get: (Int) -> T, set: (Int, T) -> Unit, size: Int) {
    // Fisher-Yates shuffle algorithm
    for (i in size - 1 downTo 1) {
        val j = rnd.nextInt(i + 1)
        val temp = get(i)
        set(i, get(j))
        set(j, temp)
    }
}

@JvmField
var internal_random: Random? = null
val random get() = internal_random ?: Random(0x564E235C123 * System.nanoTime()).also { internal_random = it }

fun IntArray.shuffle(rnd: Random = random) = internalShuffle(rnd, ::get, ::set, size)
fun IntArray.sort() {
    shuffle(); internalSort()
}

fun IntArray.sortDescending() {
    shuffle(); internalSortDescending()
}

fun LongArray.shuffle(rnd: Random = random) = internalShuffle(rnd, ::get, ::set, size)
fun LongArray.sort() {
    shuffle(); internalSort()
}

fun LongArray.sortDescending() {
    shuffle(); internalSortDescending()
}

fun DoubleArray.shuffle(rnd: Random = random) = internalShuffle(rnd, ::get, ::set, size)
fun DoubleArray.sort() {
    shuffle(); internalSort()
}

fun DoubleArray.sortDescending() {
    shuffle(); internalSortDescending()
}

fun CharArray.shuffle(rnd: Random = random) = internalShuffle(rnd, ::get, ::set, size)
inline fun CharArray.sort() {
    internalSort()
}

inline fun CharArray.sortDescending() {
    internalSortDescending()
}

inline fun <T : Comparable<T>> Array<out T>.sort() = internalSort()
inline fun <T : Comparable<T>> Array<out T>.sortDescending() = internalSortDescending()
inline fun <T : Comparable<T>> MutableList<out T>.sort() = internalSort()
inline fun <T : Comparable<T>> MutableList<out T>.sortDescending() = internalSortDescending()

fun `prevent import removal`() {
    iprintln(max(1, 2))
}

const val MOD = 1000000007
const val SZ = 1 shl 18
const val INF = (1e18).toLong()

fun add(a: Int, b: Int) = (a + b) % MOD
fun sub(a: Int, b: Int) = (a - b + MOD) % MOD
fun mul(a: Int, b: Int) = ((a.toLong() * b) % MOD).toInt()
fun YN(b: Boolean): String {
    return if (b) "YES" else "NO"
}