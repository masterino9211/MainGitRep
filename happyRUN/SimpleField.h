#ifndef SIMPLEFIELD_H
#define SIMPLEFIELD_H

class SimpleField
{
public:
    SimpleField();
	bool visited;
	int weight;
	bool passable;
	bool operator < (SimpleField& arg);
	bool operator > (SimpleField& arg);
	bool operator >= (SimpleField& arg);
	bool operator <= (SimpleField& arg);
	bool operator == (SimpleField& arg);
	
	
	
};

#endif // SIMPLEFIELD_H
