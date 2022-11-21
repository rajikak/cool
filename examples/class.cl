class B {
	s : String <- "hello";
	
	g (y:String) : Int {
		y.concat(s)
	};
	f (x:Int) : Int {
		x+1
	};	 

};
