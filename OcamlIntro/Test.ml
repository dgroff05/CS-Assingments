




let rec count_origin lst = 
  match lst with
  [] -> 0
  | p::t -> count_origin t + if p = (0.0, 0.0) then 1 else 0


  let list = [(0.0, 0.0); (-0.0, -0.0); (9.7, 0.1); (0.0, -0.0)];;

  count_origin list;;