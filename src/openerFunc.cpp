Move AI::Opener(int seed)
{
	vector<Move> one;
	vector<Move> two;
	vector<Move> three;
	vector<Move> four;
	vector<Move> five;
	
	Move temp;
	
	switch(seed)
	{
		case 1:
			temp = one.back();
			one.pop_back();
			return temp;
		case 2:
			temp = two.back();
			one.two_back();
			return temp;
		case 3:
			temp = three.back();
			three.pop_back();
			return temp;
		case 4:
			temp = four.back();
			four.pop_back();
			return temp;
		case 5:
			temp = five.back();
			five.pop_back();
			return temp;
		default:
			cout << "Error invalid seed" << endl;
	}
}