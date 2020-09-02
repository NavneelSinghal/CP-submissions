let read_int64 () = Scanf.bscanf Scanf.Scanning.stdin " %s " (fun x -> Big_int.big_int_of_string x);;
let read_int () = Scanf.bscanf Scanf.Scanning.stdin " %d " (fun x -> x);;
let read_pair _ = let x = read_int64 () in let y = read_int64 () in (x, y);;
let comp (a, b) (c, d) = if (Big_int.compare_big_int a c) = 0 then Big_int.compare_big_int b d else Big_int.compare_big_int a c;; 
let main () = 
    let n = read_int () in
    let d = read_int64 () in
    let a = Array.init n read_pair in
    let _ = Array.sort comp a in
    let (i, j, k, c) = (ref 0, ref 0, ref (Big_int.big_int_of_int 0), ref (Big_int.big_int_of_int 0)) in (
        while !i < n do (
            match (a.(!i), a.(!j)) with
            | ((x, y), (z, w)) -> (
                if Big_int.compare_big_int (Big_int.sub_big_int x z) d < 0 then
                    (k := (Big_int.add_big_int !k y); c := (Big_int.max_big_int (!c) (!k)); incr i)
                else 
                    (k := (Big_int.sub_big_int !k w); incr j)
            )
        )
        done;
        Printf.printf "%s\n" (Big_int.string_of_big_int !c)
    )
;;

main ();;