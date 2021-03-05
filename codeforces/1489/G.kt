import java.io.*
import java.util.*

fun main(args:Array<String>) {
    solve()
}

class Edge(U: Int, V: Int, W: Long) {
    public var u: Int
    public var v: Int
    public var w: Long
    init {
        u = U
        v = V
        w = W
    }
}

class DSU(var n: Int) {
    private val par = IntArray(n){ i -> i }
    private val rank = IntArray(n){ 1 }
    fun find(i: Int): Int {
        if (par[i] != i) {
            par[i] = find(par[i])
        }
        return par[i];
    }
    fun union(u: Int, v: Int) {
        var U = find(u)
        var V = find(v)
        if (U == V) return
        if (rank[U] < rank[V]) {
            var t = U
            U = V
            V = t
        }
        par[V] = U
        if (rank[U] == rank[V]) {
            ++rank[U]
        }
    }
}

fun solve() {
    
    
    val n = nextInt()
    val m = nextInt()
    
    var minCost = 2000000000000L
    var minIndex = -1
    val a = MutableList<Long>(n){0}
    for (i in 0 until n) {
        a[i] = nextLong()
        if (a[i] < minCost) {
            minIndex = i
            minCost = a[i]
        }
    }
   
    val edgeList = MutableList<Edge>(0){Edge(-1, -1, 0)}
    
    for (i in 0 until n) {
        if (i != minIndex) {
            edgeList.add(Edge(i, minIndex, a[i] + minCost))
        }
    }

    for (i in 0 until m) {
        val u = nextInt() - 1
        val v = nextInt() - 1
        val w = nextLong()
        edgeList.add(Edge(u, v, w))
    }

    edgeList.sortWith(Comparator<Edge> {
        a, b -> 
            var ans = 0
            if (a.w < b.w) ans = -1
            else if (a.w > b.w) ans = 1
            ans
    })

    var answerEdges = MutableList<Edge>(0){Edge(-1, -1, 0)}
    var curEdgeIndex = 0

    var dsu = DSU(n)

    var ans = 0L

    while (answerEdges.size < n - 1 && curEdgeIndex < edgeList.size) {
        var curEdge = edgeList[curEdgeIndex]
        curEdgeIndex++
        var u = dsu.find(curEdge.u)
        var v = dsu.find(curEdge.v)
        if (u != v) {
            answerEdges.add(curEdge)
            ans += curEdge.w
            dsu.union(u, v)
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
