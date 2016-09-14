# Remove equal adjacent elements
#
# Example input: [1, 2, 2, 3]
# Example output: [1, 2, 3]
def remove_adjacent(lst):
    if len(lst) == 0:
        return lst
    
    ans_lst = [lst[0]]
    for pos in range(1, len(lst)):
        if lst[pos] != lst[pos - 1]:
            ans_lst.append(lst[pos])

    return ans_lst
 
# Merge two sorted lists in one sorted list in linear time
#
# Example input: [2, 4, 6], [1, 3, 5]
# Example output: [1, 2, 3, 4, 5, 6]
def linear_merge(lst1, lst2):

    lst = []
    i = j = 0
    
    while (i < len(lst1) and j < len(lst2)):
        if lst1[i] < lst2[j]:
            lst += [lst1[i]]
            i += 1
        else:
            lst += [lst2[j]]
            j += 1
    
    if i < len(lst1):
        lst += lst1[i:]
    else:
        lst += lst2[j:]
        
    return lst
lst1 = [1,3,5]
lst2 = [2,4,6]
print(linear_merge(lst1, lst2))
