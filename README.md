	Implemented a Treap data structure (combining Binary Search Tree and Heap properties) in C++ using efficient split and merge operations.						
	Algorithms are capable of processing and summing large-scale trees, ensuring type safety and precision within long long range constraints.
	---
	Each item in Treap is described by a unique identifier (id), which is an int, alongside a price which is also an int. 
	The system  supports the following operations:
	case A: id price (Add) - Adds a product with the given id and price. If a product with this ID already exists, it updates it's price.
	case D: id (Delete) - Removes the product with the given id. If the product isn't in the database, the operation is ignored.   
	case S: id_min id_max (Sum) - Calculates the sum of prices of all products whose IDs fall within the closed interval [id_min, id_max].
	case C: (Count) - prints the current number of products in the database. The value returned by the C operation can be buffered (stored in a separate variable) and updated  during addition (A) and deletion (D) operations.
