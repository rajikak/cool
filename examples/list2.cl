class List{
	item: Object;
	next: List;

	init(i: String, n: List){
		{
			item <- i;
			next <- n;
			self;
		}
	};

	flattern(): String {
		let string: String <- 
			case item of 
				i: Int -> i2a(i);
				a: String -> s;
				o: Object -> { abort(); "";}
			case 

		in	
		if (isvoid next) then 
			string	
		else
			string.concat(flattern(next))
	};
};

class Main:inherit IO {
	main(): Object {
		let hello: String <- "hello ",
			world: String <- "world",
			i: Int <- 42,
			newline : String <- "\n",
			nil: List, 
			list: List <- (new List).init(hello, 
								  	(new List).init(world, (new List).init(newline, nil)))
		in
			out_string(hello.concat(world).concat(newline));
			out_string(list.flattern())
		
	};
};
