#[allow(unused_imports)]
use std::cmp::{max, min};
use std::io::{stdin, stdout, BufWriter, Write};

#[derive(Default)]
struct Scanner {
    buffer: Vec<String>,
}
impl Scanner {
    fn next<T: std::str::FromStr>(&mut self) -> T {
        loop {
            if let Some(token) = self.buffer.pop() {
                return token.parse().ok().expect("Failed parse");
            }
            let mut input = String::new();
            stdin().read_line(&mut input).expect("Failed read");
            self.buffer = input.split_whitespace().rev().map(String::from).collect();
        }
    }
}

#[derive(Clone)]
struct Edge(usize, usize, i64);

#[derive(Clone, Copy)]
struct Node(i64, i64, i64, i64, i64);

struct LazySegTree {
    t: Vec<Node>,
    lazy: Vec<i64>,
    size: usize,
    log: usize,
}

impl LazySegTree {
    fn combine(n1: Node, n2: Node) -> Node {
        if n1.0 == i64::MIN {
            n2
        } else if n2.0 == i64::MIN {
            n1
        } else {
            Node(
                max(n1.0, n2.0),
                max(n1.1, n2.1),
                max(max(n1.2, n2.2), n1.0 + n2.1),
                max(max(n1.3, n2.3), n1.1 + n2.0),
                max(max(n1.4, n2.4), max(n1.0 + n2.3, n1.2 + n2.0)),
            )
        }
    }

    fn make_node(val: i64) -> Node {
        Node(val, -2 * val, -val, -val, 0i64)
    }

    fn id_node() -> Node {
        Node(i64::MIN, 0i64, 0i64, 0i64, 0i64)
    }

    fn apply_update(u: i64, nd: Node) -> Node {
        if nd.0 == i64::MIN {
            nd
        } else {
            Node(nd.0 + u, nd.1 - 2 * u, nd.2 - u, nd.3 - u, nd.4)
        }
    }

    fn compose_updates(u: i64, v: i64) -> i64 {
        u + v
    }

    fn id_update() -> i64 {
        0i64
    }

    fn id_base() -> i64 {
        0i64
    }

    fn new(n: usize) -> LazySegTree {
        let mut log = 0;
        while (1 << log) < n {
            log += 1usize;
        }
        let size = 1 << log;
        let mut ret = LazySegTree {
            t: vec![LazySegTree::id_node(); 2 * size],
            lazy: vec![LazySegTree::id_update(); size],
            size: size,
            log: log,
        };
        for i in 0..n {
            ret.t[size + i] = LazySegTree::make_node(LazySegTree::id_base())
        }
        for i in (1usize..size).rev() {
            ret.pull(i);
        }
        ret
    }

    fn query(&mut self, l: usize, r: usize) -> Node {
        if l == r {
            LazySegTree::id_node()
        } else {
            let mut l = l + self.size;
            let mut r = r + self.size;
            for i in (1usize..self.log + 1).rev() {
                if ((l >> i) << i) != l {
                    self.push(l >> i);
                }
                if ((r >> i) << i) != r {
                    self.push((r - 1) >> i);
                }
            }
            let mut left = LazySegTree::id_node();
            let mut right = LazySegTree::id_node();
            while l < r {
                if (l & 1usize) == 1usize {
                    left = LazySegTree::combine(left, self.t[l]);
                    l += 1usize
                }
                if (r & 1usize) == 1usize {
                    r -= 1usize;
                    right = LazySegTree::combine(self.t[r], right);
                }
                l >>= 1;
                r >>= 1;
            }
            LazySegTree::combine(left, right)
        }
    }

    fn update(&mut self, l: usize, r: usize, w: i64) {
        if l == r {
            ()
        } else {
            let mut l = l + self.size;
            let mut r = r + self.size;
            for i in (1usize..self.log + 1).rev() {
                if ((l >> i) << i) != l {
                    self.push(l >> i);
                }
                if ((r >> i) << i) != r {
                    self.push((r - 1) >> i);
                }
            }
            let l2 = l;
            let r2 = r;
            while l < r {
                if (l & 1) == 1 {
                    self.all_apply(l, w);
                    l += 1;
                }
                if (r & 1) == 1 {
                    r -= 1;
                    self.all_apply(r, w);
                }
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
            for i in 1usize..self.log + 1 {
                if ((l >> i) << i) != l {
                    self.pull(l >> i);
                }
                if ((r >> i) << i) != r {
                    self.pull((r - 1) >> i);
                }
            }
        }
    }

    fn pull(&mut self, k: usize) {
        self.t[k] = LazySegTree::combine(self.t[2 * k], self.t[2 * k + 1]);
    }

    fn all_apply(&mut self, k: usize, w: i64) {
        self.t[k] = LazySegTree::apply_update(w, self.t[k]);
        if k < self.size {
            self.lazy[k] = LazySegTree::compose_updates(w, self.lazy[k]);
        }
    }

    fn push(&mut self, k: usize) {
        self.all_apply(2 * k, self.lazy[k]);
        self.all_apply(2 * k + 1, self.lazy[k]);
        if k < self.size {
            self.lazy[k] = LazySegTree::id_update();
        }
    }
}

fn main() {
    let mut scan = Scanner::default();
    let out = &mut BufWriter::new(stdout());

    let n = scan.next::<usize>();
    let q = scan.next::<usize>();
    let w = scan.next::<i64>();

    let mut g = vec![vec![0; 0usize]; n];

    let mut edges = vec![Edge(0usize, 0usize, 0i64); n];
    for i in 1..n {
        let u = scan.next::<usize>() - 1usize;
        let v = scan.next::<usize>() - 1usize;
        let c = scan.next::<i64>();
        g[u].push(i - 1);
        g[v].push(i - 1);
        edges[i - 1] = Edge(u, v, c);
    }

    let mut in_time = vec![0usize; n];
    let mut out_time = vec![0usize; n];
    let mut par = vec![0usize; n];

    fn dfs_time_dist(
        u: usize,
        p: usize,
        timer: usize,
        in_time: &mut Vec<usize>,
        out_time: &mut Vec<usize>,
        par: &mut Vec<usize>,
        g: &Vec<Vec<usize>>,
        edges: &mut Vec<Edge>,
    ) -> usize {
        let mut timer = timer;
        in_time[u] = timer;
        timer = timer + 1;
        par[u] = p;
        for i in &g[u] {
            let Edge(uu, vv, _ww) = edges[*i];
            let v;
            if uu == u {
                v = vv;
            } else {
                v = uu;
            }
            if v == p {
                continue;
            }
            timer = dfs_time_dist(v, u, timer, in_time, out_time, par, g, edges) + 1;
        }
        out_time[u] = timer;
        timer
    }

    let _final_timer = dfs_time_dist(
        0usize,
        0usize,
        0usize,
        &mut in_time,
        &mut out_time,
        &mut par,
        &g,
        &mut edges,
    );

    let mut seg = LazySegTree::new(2 * n - 1);
    for i in 1..n {
        let Edge(u, mut v, w) = edges[i - 1];
        if v == par[u] {
            v = u
        }
        seg.update(in_time[v], out_time[v], w);
    }

    let mut last = 0i64;
    for _ in 0..q {
        let d = scan.next::<usize>();
        let e = scan.next::<i64>();
        let edge_index = ((d as i64 + last) % ((n - 1) as i64)) as usize;
        let new_edge_weight = (e + last) % w;
        let Edge(u, mut v, old_edge_weight) = edges[edge_index];
        edges[edge_index] = Edge(u, v, new_edge_weight);
        if v == par[u] {
            v = u;
        }
        seg.update(in_time[v], out_time[v], new_edge_weight - old_edge_weight);
        last = seg.query(0, 2 * n - 1).4;
        writeln!(out, "{}", last);
    }
}
