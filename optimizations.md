# Additional optimizations
### optimizeDuplicates() - use custom searchFirst()
NamesDB::searchFirst() should have a flag or a custom implementation for optimizeDuplicates() that leads it to skipping all DBEntries that have nullptr as the data field, those have already been sorted and do not need to be checked for their name again
### optimizeDuplicates() - use more threads
FileIndex::optimizeDuplicates() can use more threads because this is an asynchronous job, just check if a new thread is not searching for an already searched name
### NamesDB::searchAll() - do not use searchFirst()
NamesDB::searchAll() can use a custom implementation of searchFirst() or a flag to continue searching even if the result has been found, this would minimize calling delays, allocations of memory and checks becaus searchFirst has to generate the optimized c-string of the name every time it gets called and check for errors and so on...