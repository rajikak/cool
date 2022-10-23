class List{
	item: String;
	next: List;

	init(i: String, n: List){
		{
			item <- i;
			next <- n;
			self;
		}
	};

	flattern(): String {
		
	
		if (isvoid next) then 
			item
		else
			item.concat(flattern(next))
	};
};

class Main:inherit IO {
	main(): Object {
		let hello: String <- "hello ",
			world: String <- "world",
			newline : String <- "\n",
			nil: List, 
			list: List <- (new List).init(hello, 
								  	(new List).init(world, (new List).init(newline, nil)))
		in
			out_string(hello.concat(world).concat(newline));
			out_string(list.flattern())
		
	};
};
