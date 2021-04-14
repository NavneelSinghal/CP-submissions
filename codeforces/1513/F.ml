let read_int64 () = Scanf.bscanf Scanf.Scanning.stdin " %d " (fun x -> Int64.of_int x);;
let read_int () = Scanf.bscanf Scanf.Scanning.stdin " %d " (fun x -> x);;
let read_pair _ = let x = read_int64 () in let y = read_int64 () in (x, y);;
let comp (a, b) (c, d) = if (Int64.compare a c) = 0 then Int64.compare b d else Int64.compare a c;; 

let min x y = if Int64.compare x y < 0 then x else y

let max x y = if Int64.compare x y > 0 then x else y

let empty_read x = read_int64 ();;

let n = read_int ();;
let a = Array.init n empty_read;;
let b = Array.init n empty_read;;
let c = (Array.init n (fun i ->
    if Int64.compare a.(i) b.(i) <= 0
    then (a.(i), b.(i), 0)
    else (b.(i), a.(i), 1)));;

let _ = Array.stable_sort (fun (x, y, z) (u, v, w) ->
    if Int64.compare x u != 0
    then Int64.compare x u
    else
        if Int64.compare y v != 0
        then Int64.compare y v
        else compare z w) c;;

let mx = Array.make 2 Int64.zero;;

let ans = Array.fold_left Int64.add Int64.zero (
    Array.map (fun (a, b, c) -> Int64.sub b a) c);;

let diff = ref Int64.zero;;

for i = 0 to n - 1 do
    match c.(i) with (a, b, x) ->
        diff := max !diff (Int64.sub (min b mx.(1 - x)) a);
        mx.(x) <- max mx.(x) b
done;;

Printf.printf "%s\n" (Int64.to_string (Int64.sub ans (Int64.mul 2L !diff)))

