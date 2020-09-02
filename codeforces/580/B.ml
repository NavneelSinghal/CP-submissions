let read_int64 () = Scanf.bscanf Scanf.Scanning.stdin " %d " (fun x -> Int64.of_int x);;
let read_int () = Scanf.bscanf Scanf.Scanning.stdin " %d " (fun x -> x);;
let read_pair _ = let x = read_int64 () in let y = read_int64 () in (x, y);;
let comp (a, b) (c, d) = if (Int64.compare a c) = 0 then Int64.compare b d else Int64.compare a c;; 
let main () = 
    let n = read_int () in
    let d = read_int64 () in
    let a = Array.init n read_pair in
    let _ = Array.sort comp a in
    let (i, j, k, c) = (ref 0, ref 0, ref 0L, ref 0L) in (
        while !i < n do (
            match (a.(!i), a.(!j)) with
            | ((x, y), (z, w)) -> (
                if Int64.compare (Int64.sub x z) d < 0 then
                    (k := (Int64.add !k y); c := (max (!c) (!k)); incr i)
                else 
                    (k := (Int64.sub !k w); incr j)
            )
        )
        done;
        Printf.printf "%s\n" (Int64.to_string !c)
    )
;;
main ();;
