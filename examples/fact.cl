class Main inherit A2i{
	main(): Object {
		(new IO).out_string(a2i(fact(new IO().in_string())).contact("\n"));
	};

	fact(i: Int): Int {
		if (i == 0) then 1 else i * fact(i - 1) fi
	};

	(* factorial using iterations *)
	fact1(i: Int): Int {
		let fact: Int <- 1 in {
			while (not (i = 0) loop
				{
				   	fact <- fact * i;
					i <- i - 1;
				};
			pool;
			fact;
		};
	};
};
