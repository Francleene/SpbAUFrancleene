# Remove equal adjacent elements
#
# Example input: [1, 2, 2, 3]
# Example output: [1, 2, 3]
def remove_adjacent(lst):
    pos = 1
    while (pos < len(lst)):
        if (lst[pos] == lst[pos - 1]):
            del lst[pos - 1]
        else:
            pos += 1
            
    return lst
 
# Merge two sorted lists in one sorted list in linear time
#
# Example input: [2, 4, 6], [1, 3, 5]
# Example output: [1, 2, 3, 4, 5, 6]
def linear_merge(lst1, lst2):

    lst = []
    i = j = 0
    
    while (i < len(lst1) and j < len(lst2)):
        if (lst1[i] < lst2[j]):
            lst += [lst1[i]]
            i += 1
        else:
            lst += [lst2[j]]
            j += 1
    
    if (i < len(lst1)):
        lst += lst1
    else:
        lst += lst2
        
    return lst
